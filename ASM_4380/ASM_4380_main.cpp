#include "include/ASM4380.h"

#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include <ASMFramework_GetVersion.h>

#include "rootConfig.h"

constexpr size_t maxPathLength = 256;

int main(int argc, char* argv[])
{
	std::cout << "ASM4380: assembler for ISA_4380 architecture" << std::endl;
	DIMB_TEXT
		std::cout << " version " << VERSION_MAJOR << '.' << VERSION_MINOR << '.' << VERSION_PATCH << '_' << TARGET_OS << " (" <<
		ASMFramework::GetFrameworkVersion() << ')' << std::endl;
	RESET_TERMINAL

	std::shared_ptr<ASM4380> ASM;

	ASM = ASM4380::GetInstance();

	if (argc > 1)
	{
		try
		{
			ASM->ProcessASM(argv[1]);
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
	}
	else
	{
		std::cout << std::endl << "Specify a path to a valid assembly program (.asm) to assemble" << std::endl << " path << ";

		char filePath[maxPathLength];
		std::cin.getline(filePath, maxPathLength);

		CLEAR_TERMINAL

		std::cout << "ASM4380: assembler for ISA_4380 architecture" << std::endl;
		DIMB_TEXT
			std::cout << " version " << VERSION_MAJOR << '.' << VERSION_MINOR << '.' << VERSION_PATCH << '_' << TARGET_OS << " (" <<
			ASMFramework::GetFrameworkVersion() << ')' << std::endl;
		RESET_TERMINAL

		try
		{
			ASM->ProcessASM(filePath);
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
	}

	ASM->ShutDown();

	return 0;
}