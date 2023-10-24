#include "../include/PassThree_Serialize.h"

#include <filesystem>
#include <iostream>
#include "rootConfig.h"

size_t PassThree_Serialize::SerializeInitialPC(std::ofstream& fileStream, ASMFramework::Workpiece* const& workpiece) const
{
	std::streampos beforeWrite = fileStream.tellp();

	int32_t initialPC = workpiece->_dataSegmentBin.size() + sizeof(int32_t);
	fileStream.write(reinterpret_cast<const char*>(&initialPC), sizeof(int32_t));

	std::streampos afterWrite = fileStream.tellp();

	return static_cast<size_t>(afterWrite - beforeWrite);
}

size_t PassThree_Serialize::SerializeDataSegment(std::ofstream& fileStream, ASMFramework::Workpiece* const& workpiece) const
{
	std::streampos beforeWrite = fileStream.tellp();

	fileStream.write(reinterpret_cast<const char*>(workpiece->_dataSegmentBin.data()), workpiece->_dataSegmentBin.size());

	std::streampos afterWrite = fileStream.tellp();

	return static_cast<size_t>(afterWrite - beforeWrite);
}

size_t PassThree_Serialize::SerializeCodeSegment(std::ofstream& fileStream, ASMFramework::Workpiece* const& workpiece) const
{
	size_t codeSegmentSize = 0;
	for (auto& section : workpiece->_codeSegmentBins)
	{
		std::streampos beforeWrite = fileStream.tellp();

		fileStream.write(reinterpret_cast<const char*>(section.second.data()), section.second.size());

		std::streampos afterWrite = fileStream.tellp();

		codeSegmentSize += static_cast<size_t>(afterWrite - beforeWrite);
	}

	return codeSegmentSize;
}

void PassThree_Serialize::Execute(ASMFramework::Workpiece* const& workpiece, const std::filesystem::path& filePath, const ASMFramework::LanguageDefinition* const& langDef) const
{
	std::filesystem::path binaryPath = filePath;
	binaryPath.replace_extension(".bin");

	std::ofstream binFile(binaryPath.string(), std::ios::binary);

	if (!binFile.is_open())
		throw std::runtime_error("Was unable to create the binary file at path: " + binaryPath.string());

	size_t totalBytesWritten = 0;

	totalBytesWritten += SerializeInitialPC(binFile, workpiece);

	totalBytesWritten += SerializeDataSegment(binFile, workpiece);

	totalBytesWritten += SerializeCodeSegment(binFile, workpiece);

	binFile.close();

	GREEN_TERMINAL
		std::cout << " >>> Serialization Complete" << std::endl <<
		"Successfully serialized " << totalBytesWritten << " bytes creating " << binaryPath.filename() << " at >> " << binaryPath << std::endl;
	RESET_TERMINAL
}