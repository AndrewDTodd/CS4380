#include <ASM_4380/include/ASM4380.h>
#include <VM_4380/include/VM4380.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <filesystem>

#include <ASMFramework_GetVersion.h>
#include <VMFramework_GetVersion.h>

#include "rootConfig.h"

constexpr size_t maxPathLength = 256;

int main(int argc, char* argv[])
{
	std::filesystem::path filePath;
	if (argc > 1)
	{
		filePath = std::filesystem::path(argv[1]);
	}
	else
	{
		std::cout << "Specify a path to a valid assembly program (.asm) to assemble or a valid binary (.bin) to execute" << std::endl << " path << ";

		char inputPath[maxPathLength];
		std::cin.getline(inputPath, maxPathLength);

		filePath = std::filesystem::path(inputPath);

		CLEAR_TERMINAL
	}

	if (filePath.extension() == ".bin" || filePath.extension() == ".BIN")
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

		VM->StartUp();

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
	else
	{
		std::cout << "ASM4380: assembler for ISA_4380 architecture" << std::endl;
		DIMB_TEXT
			std::cout << " version " << ASM4380_VERSION_MAJOR << '.' << ASM4380_VERSION_MINOR << '.' << ASM4380_VERSION_PATCH << 
#ifdef _DEBUG
			'd'
#else
			'r'
#endif // _DEBUG
			<< '_' << TARGET_OS << " (" <<
			ASMFramework::GetFrameworkVersion() << ')' << std::endl;
		RESET_TERMINAL

		std::shared_ptr<ASM4380> ASM;

		ASM = ASM4380::GetInstance();

		try
		{
			ASM->ProcessASM(std::move(filePath));
		}
		catch (const std::runtime_error& programError)
		{
			RED_TERMINAL
				std::cerr << "Error: " << programError.what() << std::endl;
			RESET_TERMINAL
		}
		catch (const std::invalid_argument& argEx)
		{
			RED_TERMINAL
				std::cerr << "Error: " << argEx.what() << std::endl;
			RESET_TERMINAL
		}
		catch (const std::exception& ex)
		{
			RED_TERMINAL
				std::cerr << "Unhandled exeption caught by root catch. Error: " << ex.what() << std::endl;
			RESET_TERMINAL
		}

		ASM->ShutDown();

		return 0;
	}
}