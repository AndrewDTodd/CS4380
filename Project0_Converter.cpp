#include "Project0_Converter.h"

#include <cmath>
#include <bitset>
#include <iostream>
#include <limits>

std::string B10ToB2Convert(std::istream& input)
{
	int64_t baseTenNum;

	if (!(input >> baseTenNum))
	{
		throw std::invalid_argument("Invalid input. Please enter a valid unsigned integer.");
	}
	else if (baseTenNum > std::numeric_limits<uint32_t>::max())
	{
		throw std::invalid_argument("Input is out of range, it's too big. Please enter a valid integer within the specified range.");
	}
	else if (baseTenNum < std::numeric_limits<uint32_t>::min())
	{
		throw std::invalid_argument("Input is out of range, no negative numbers. Please enter a valid integer within the specified range.");
	}

	std::bitset<32> binary(baseTenNum);

	std::string baseTwo = binary.to_string();

	return baseTwo.erase(0, baseTwo.find_first_of('1') == std::string::npos ? 31 : baseTwo.find_first_of('1'));
}