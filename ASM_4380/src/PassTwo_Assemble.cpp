#include "../include/PassTwo_Assemble.h"

#include <memory>
#include <fstream>
#include <iostream>

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
				std::cerr << "Error: **Debug** When trying to get the address in the symbol table associated with \"" + item.first + "\" out_of_range exception was thrown" +
					"\nThere must be something wrong with pass one's capturing of labels" << std::endl;

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
			std::cerr << "At line " + std::to_string(dataItem._lineNum) + " when processing directive with mnemonic \"" + 
				dataItem._directive->_mnemonic + "\"\nError: " + rtEx.what() << std::endl;

			_fail = true;
		}
		//Continue processing to inform user of all unsupported mnemonics, though operation will fail
		catch (const ASMFramework::ASMDirective::NotImplemented& ex)
		{
			std::cerr << "At line " + std::to_string(dataItem._lineNum) + " when processing directive with mnemonic \"" +
				dataItem._directive->_mnemonic + "\"\nError: " + ex.what() << std::endl;

			_fail = true;
		}
	}
}

void PassTwo_Assemble::ProcessCodeSegment(size_t& byteNum, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef) const
{
	for (const auto& segment : workpiece->_codeSegmentItems)
	{
		workpiece->_codeSegmentBins.emplace_back(segment.first, std::vector<uint8_t>());
		std::vector<uint8_t>& segmentBin = workpiece->_codeSegmentBins.back().second;

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
				std::cerr << "Error: **Debug** When trying to get the address in the symbol table associated with \"" + segment.first + "\" out_of_range exception was thrown" +
					"\nThere must be something wrong with pass one's capturing of labels" << std::endl;

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
				std::cerr << "At line " + std::to_string(instructionItem._lineNum) + " when processing instruction with mnemonic \"" +
					instructionItem._instruction->_mnemonic + "\"\nError: " + rtEx.what() << std::endl;
				
				_fail = true;
			}
			//Continue processing to inform user of all unsupported mnemonics, though operation will fail
			catch (const ASMFramework::ASMInstruction::NotImplemented& ex)
			{
				std::cerr << "At line " + std::to_string(instructionItem._lineNum) + " when processing instruction with mnemonic \"" +
					instructionItem._instruction->_mnemonic + "\"\nError: " + ex.what() << std::endl;

				_fail = true;
			}
		}
	}
}

void PassTwo_Assemble::Execute(ASMFramework::Workpiece* const& workpiece, const std::unique_ptr<std::ifstream>& fileStream, const ASMFramework::LanguageDefinition* const& langDef) const
{
	//offset of first byte generated will be 4 because the initial PC value is stored in 4 bytes at beginning of binary
	size_t byteNum = 4;

	//Process _dataSegmentItems first
	ProcessDataSegment(byteNum, workpiece, langDef);

	//Process _codeSegmentItems next
	ProcessCodeSegment(byteNum, workpiece, langDef);

	if (_fail)
		throw std::runtime_error("Was unable to assemble the program. See above for list of errors");
}