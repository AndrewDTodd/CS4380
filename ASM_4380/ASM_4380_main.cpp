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

	std::filesystem::path filePath;

	if (argc > 1)
	{
		filePath = std::filesystem::path(argv[1]);
	}
	else
	{
		std::cout << std::endl << "Specify a path to a valid assembly program (.asm) to assemble" << std::endl << " path << ";

		char inputPath[maxPathLength];
		std::cin.getline(inputPath, maxPathLength);

		filePath = std::filesystem::path(inputPath);

		CLEAR_TERMINAL

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
	}

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