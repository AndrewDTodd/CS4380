#include <gtest/gtest.h>

#include "Project0_Converter.h"

//Tests that the B10ToB2Convert funtion will produce the string "0" when the number 0 is input
TEST(Project0Tests, ValidateLowestBound)
{
	std::istringstream input(std::string("0"));
	ASSERT_EQ(std::string("0"), B10ToB2Convert(input)) << "Inputting 0 did not produce the binary string 0";
}

//Test that the B10ToB2Converter function will throw invalid_argument if a negative number is passed in
TEST(Project0Tests, ThrowsExeptionOnNegative)
{
	std::istringstream input(std::string("-1"));
	ASSERT_THROW(B10ToB2Convert(input), std::invalid_argument) << "Inputting -1 did not throw an invalid_argument exeption";
}

//Test that the B10ToB2Convert function will throw invalid argument if a value greater than 4294967295 is passed in
TEST(Project0Tests, ThrowsExeptionOnTooBig)
{
	std::istringstream input(std::string("4294967296"));
	ASSERT_THROW(B10ToB2Convert(input), std::invalid_argument) << "Inputting 4294967296 (which is too big for uint32_t) did not throw an invalid_argument exeption";
}

//Test that the B10ToB2Convert function will produce the string "11111111111111111111111111111111" (32 set bits) when number 4294967295 is input
TEST(Project0Tests, ValidateBigestBound)
{
	std::istringstream input(std::string("4294967295"));
	ASSERT_EQ(std::string("11111111111111111111111111111111"), B10ToB2Convert(input)) << "Inputting 4294967295 did not produce the binary string 11111111111111111111111111111111 (32 set bits)";
}

//Test that the B10ToB2Convert function will throw invalid argument if a non numeric value is passsed in
TEST(Project0Tests, ThrowsExeptionOnNonNumber)
{
	std::istringstream input(std::string("test"));
	ASSERT_THROW(B10ToB2Convert(input), std::invalid_argument) << "Inputting test (which is not valid input, only numbers accepted) did not throw an invalid_argument exeption";
}