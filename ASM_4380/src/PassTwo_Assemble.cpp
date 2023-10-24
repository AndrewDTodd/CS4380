#include "../include/PassTwo_Assemble.h"

#include <memory>
#include <fstream>
#include <iostream>

#include "rootConfig.h"

void PassTwo_Assemble::ProcessDataSegment(size_t& byteNum, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef) const
{
	for (const auto& item : workpiece->_dataSegmentItems)
	{
		if (!item.first.empty())
		{
#ifdef _DEBUG
			try
			{
				uint64_t& address = workpiece->_symbolTable.at(item.first);
				address = byteNum;
			}
			//Continue processing to inform user of all errors, though operation will fail
			catch (const std::out_of_range& rangeEx)
			{
				RED_TERMINAL
				std::cerr << "Error: **Debug** When trying to get the address in the symbol table associated with \"" + item.first + "\" out_of_range exception was thrown" +
					"\nThere must be something wrong with pass one's capturing of labels" << std::endl;
				RESET_TERMINAL

				_fail = true;
			}
#else
			uint64_t& address = workpiece->_symbolTable.at(item.first);
			address = byteNum;
#endif // _DEBUG
		}

		const ASMFramework::DataSegmentItem& dataItem = item.second;

		try
		{
			byteNum += dataItem._directive->Implementation(workpiece, dataItem._dirArgs);
		}
		//Continue processing to inform user of all errors, though operation will fail
		catch (const std::runtime_error& rtEx)
		{
			RED_TERMINAL
			std::cerr << "At line " + std::to_string(dataItem._lineNum) + " when processing directive with mnemonic \"" + 
				dataItem._directive->_mnemonic + "\"\nError: " + rtEx.what() << std::endl;
			RESET_TERMINAL

			_fail = true;
		}
		//Continue processing to inform user of all unsupported mnemonics, though operation will fail
		catch (const ASMFramework::ASMDirective::NotImplemented& ex)
		{
			RED_TERMINAL
			std::cerr << "At line " + std::to_string(dataItem._lineNum) + " when processing directive with mnemonic \"" +
				dataItem._directive->_mnemonic + "\"\nError: " + ex.what() << std::endl;
			RESET_TERMINAL

			_fail = true;
		}
	}
}

void PassTwo_Assemble::ProcessCodeSegment(size_t& byteNum, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef) const
{
	for (const auto& segment : workpiece->_codeSegmentItems)
	{
		workpiece->_codeSegmentBins.emplace_back(segment.first, std::vector<uint8_t>(segment.second.size() * 3 * sizeof(int32_t)));
		std::vector<uint8_t>& segmentBin = workpiece->_codeSegmentBins.back().second;
		segmentBin.clear();

		if (!segment.first.empty())
		{
#ifdef _DEBUG
			try
			{
				uint64_t& address = workpiece->_symbolTable.at(segment.first);
				address = byteNum;
			}
			//Continue processing to inform user of all errors, though operation will fail
			catch (const std::out_of_range& rangeEx)
			{
				RED_TERMINAL
				std::cerr << "Error: **Debug** When trying to get the address in the symbol table associated with \"" + segment.first + "\" out_of_range exception was thrown" +
					"\nThere must be something wrong with pass one's capturing of labels" << std::endl;
				RESET_TERMINAL

				_fail = true;
			}
#else
			uint64_t& address = workpiece->_symbolTable.at(segment.first);
			address = byteNum;
#endif // _DEBUG
		}

		for (const auto& instructionItem : segment.second)
		{
			try
			{
				byteNum += instructionItem._instruction->Implementation(segmentBin, workpiece, instructionItem._instrArgs);
			}
			//Continue processing to inform user of all errors, though operation will fail
			catch (const std::runtime_error& rtEx)
			{
				RED_TERMINAL
				std::cerr << "At line " + std::to_string(instructionItem._lineNum) + " when processing instruction with mnemonic \"" +
					instructionItem._instruction->_mnemonic + "\"\nError: " + rtEx.what() << std::endl;
				RESET_TERMINAL
				
				_fail = true;
			}
			//Continue processing to inform user of all unsupported mnemonics, though operation will fail
			catch (const ASMFramework::ASMInstruction::NotImplemented& ex)
			{
				RED_TERMINAL
				std::cerr << "At line " + std::to_string(instructionItem._lineNum) + " when processing instruction with mnemonic \"" +
					instructionItem._instruction->_mnemonic + "\"\nError: " + ex.what() << std::endl;
				RESET_TERMINAL

				_fail = true;
			}
		}
	}
}

void PassTwo_Assemble::ProcessUnresolvedLabels(ASMFramework::Workpiece* const& workpiece) const
{
	for (auto& label : workpiece->_unresolvedLabels)
	{
		uint64_t labelOffset;
#ifdef _DEBUG
		try
		{
			labelOffset = workpiece->_symbolTable.at(label.first);
		}
		catch (const std::out_of_range& rngEx)
		{
			throw std::logic_error("**Debug logic_error** When trying to resolve a deferred label reference \"" + label.first +
				"\", found that the label isn't in the symbol table!!! This should be impossible at this stage of execution. Good luck figuring this one out");
		}
#endif // _DEBUG

#ifdef _DEBUG
			if (labelOffset == 0)
				throw std::logic_error("**Debug logic_error** When trying to resolve a deferred label reference \""+ label.first + 
					"\", found that the label has no assigned offset!!!This should be impossible at this stage of execution. Good luck figuring this one out");
#endif // _DEBUG
		for (auto& voidPtr : label.second)
		{
			int32_t* labelInBuffer;
			if constexpr (is_little_endian)
			{
				labelInBuffer = reinterpret_cast<int32_t*>(voidPtr);
				*labelInBuffer = static_cast<int32_t>(labelOffset);
			}
			else
			{
				int32_t offset = static_cast<int32_t>(labelOffset);
				offset = ((offset & 0xFF) << 24) | ((offset & 0xFF00) << 8) |
					((offset & 0xFF0000) >> 8) | ((offset >> 24) & 0xFF);

				labelInBuffer = reinterpret_cast<int32_t*>(voidPtr);
				*labelInBuffer = offset;
			}
		}
	}
}

void PassTwo_Assemble::Execute(ASMFramework::Workpiece* const& workpiece, const std::filesystem::path& filePath, const ASMFramework::LanguageDefinition* const& langDef) const
{
	//offset of first byte generated will be 4 because the initial PC value is stored in 4 bytes at beginning of binary
	size_t byteNum = 4;

	//Process _dataSegmentItems first
	ProcessDataSegment(byteNum, workpiece, langDef);

	//Process _codeSegmentItems next
	ProcessCodeSegment(byteNum, workpiece, langDef);

	//Process the _unresolvedLabels if there are any
	if (!workpiece->_unresolvedLabels.empty())
	{
		ProcessUnresolvedLabels(workpiece);
	}

	if (_fail)
		throw std::runtime_error("Was unable to assemble the program. See above for list of errors");

	GREEN_TERMINAL
		std::cout << " >>> Assembling Complete" << std::endl;
	RESET_TERMINAL
}