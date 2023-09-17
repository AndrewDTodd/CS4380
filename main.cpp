/*
	Entry point for the project0 program

	Created by Andrew Todd
*/

#include <iostream>
#include <cstdint>

#include "Project0_Converter.h"

int main()
{
	try
	{
		std::cout << "Enter an integer between 0 and 4294967295 (inclusive): " << std::endl;
		std::string baseTwo = B10ToB2Convert(std::cin);
		std::cout << "The number you entered in base 2 is: " << baseTwo << std::endl;
	}
	catch (const std::invalid_argument& invalidArgEx)
	{
		std::cerr << "Error: " << invalidArgEx.what() << std::endl;
	}
	
	return 0;
}