#include "include/VM4380.h"

#include <iostream>
#include <stdexcept>

#include <VMFramework_GetVersion.h>

#include <DWORDMemoryMap.h>

#include "rootConfig.h"

constexpr size_t maxPathLength = 256;

int main(int argc, char* argv[])
{
	std::cout << "VM4380: virtual machine for ISA_4380 architecture" << std::endl;
	DIMB_TEXT
		std::cout << " version " << VM4380_VERSION_MAJOR << '.' << VM4380_VERSION_MINOR << '.' << VM4380_VERSION_PATCH << 
#ifdef _DEBUG
		'd'
#else
		'r'
#endif // _DEBUG
		<< '_' << TARGET_OS << " (" <<
		VMFramework::GetFrameworkVersion() << ')' << std::endl;
	RESET_TERMINAL

	VM4380* VM;

	VM = VM4380::GetInstance();

	VMFramework::DWORDMemoryMap memoryMap;

	VM->StartUp(VMFramework::SYSTEM_MEMORY, memoryMap);

	std::filesystem::path filePath;
	if (argc > 1)
	{
		filePath = std::filesystem::path(argv[1]);
	}
	else
	{
		std::cout << std::endl << "Specify a path to a valid program (.bin) to execute" << std::endl << " path << ";

		char inputPath[maxPathLength];
		std::cin.getline(inputPath, maxPathLength);

		filePath = std::filesystem::path(inputPath);

		CLEAR_TERMINAL

		std::cout << "VM4380: virtual machine for ISA_4380 architecture" << std::endl;
		DIMB_TEXT
			std::cout << " version " << VM4380_VERSION_MAJOR << '.' << VM4380_VERSION_MINOR << '.' << VM4380_VERSION_PATCH << 
#ifdef _DEBUG
			'd'
#else
			'r'
#endif // _DEBUG
			<< '_' << TARGET_OS << " (" <<
			VMFramework::GetFrameworkVersion() << ')' << std::endl;
		RESET_TERMINAL
	}

	try
	{
		VM->LaunchProgram(filePath);
	}
	catch (const std::runtime_error& programError)
	{
		RED_TERMINAL
			std::cerr << "Error: " << programError.what() << std::endl;
		RESET_TERMINAL
	}
	catch (const std::exception& ex)
	{
		RED_TERMINAL
			std::cerr << "Unhandled exeption caught by root catch. Error: " << ex.what() << std::endl;
		RESET_TERMINAL
	}

	VM->WaitForProcess();

	VM->ShutDown();

	return 0;
}