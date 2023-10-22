#include "include/ASM4380.h"

#include <iostream>
#include <stdexcept>
#include <memory>

constexpr size_t maxPathLength = 256;

int main(int argc, char* argv[])
{
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
			std::cerr << "Error: " << programError.what() << std::endl;
		}
		catch (const std::exception& ex)
		{
			std::cerr << "Unhandled exeption caught by root catch. Error: " << ex.what() << std::endl;
		}
	}
	else
	{
		std::cout << "Specify a path to a valid assembly program (.asm) to assemble\nAssembly program path: ";

		char filePath[maxPathLength];
		std::cin.getline(filePath, maxPathLength);

		try
		{
			ASM->ProcessASM(filePath);
		}
		catch (const std::runtime_error& programError)
		{
			std::cerr << "Error: " << programError.what() << std::endl;
		}
		catch (const std::exception& ex)
		{
			std::cerr << "Unhandled exeption caught by root catch. Error: " << ex.what() << std::endl;
		}
	}

	ASM->ShutDown();

	return 0;
}