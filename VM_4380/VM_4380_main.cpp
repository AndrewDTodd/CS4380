#include "include/VM4380.h"

#include <iostream>
#include <stdexcept>

#include <VMFramework_GetVersion.h>

#include "rootConfig.h"

constexpr size_t maxPathLength = 256;

int main(int argc, char* argv[])
{
	std::cout << "VM4380: virtual machine for ISA_4380 architecture" << std::endl;
	DIMB_TEXT
		std::cout << " version " << VERSION_MAJOR << '.' << VERSION_MINOR << '.' << VERSION_PATCH << '_' << TARGET_OS << " (" <<
		VMFramework::GetFrameworkVersion() << ')' << std::endl;
	RESET_TERMINAL

	VM4380* VM;

	VM = VM4380::GetInstance();

	VM->StartUp();

	if (argc > 1)
	{
		try
		{
			VM->LaunchProgram(argv[1]);
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
	}
	else
	{
		std::cout << std::endl << "Specify a path to a valid program (.bin) to assemble" << std::endl << " path << ";

		char filePath[maxPathLength];
		std::cin.getline(filePath, maxPathLength);

		CLEAR_TERMINAL

		std::cout << "VM4380: virtual machine for ISA_4380 architecture" << std::endl;
		DIMB_TEXT
			std::cout << " version " << VERSION_MAJOR << '.' << VERSION_MINOR << '.' << VERSION_PATCH << '_' << TARGET_OS << " (" <<
			VMFramework::GetFrameworkVersion() << ')' << std::endl;
		RESET_TERMINAL

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
	}

	VM->WaitForProcess();

	VM->ShutDown();

	return 0;
}