#include "include/VM4380.h"

#include <iostream>
#include <stdexcept>

constexpr size_t maxPathLength = 256;

int main(int argc, char* argv[])
{
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
			std::cerr << "Error: " << programError.what() << std::endl;
		}
		catch (const std::exception& ex)
		{
			std::cerr << "Unhandled exeption caught by root catch. Error: " << ex.what() << std::endl;
		}
	}
	else
	{
		std::cout << "Specify a path to a valid program (.bin) to execute\nProgram path: ";

		char filePath[maxPathLength];
		std::cin.getline(filePath, maxPathLength);

		try
		{
			VM->LaunchProgram(filePath);
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

	VM->WaitForProcess();

	VM->ShutDown();

	return 0;
}