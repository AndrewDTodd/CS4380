#ifndef PROJECT0_CONVERTER_H
#define PROJECT0_CONVERTER_H

#include <string>
#include <cstdint>

/// <summary>
/// Function that takes an integer in the range of 0 and 4294967295 (inclusive) and returns the binary (base 2) representation of that input as a string
/// </summary>
/// <param name="input">input stream with user input. Should contain 32 bit unsigned integer containig the number we are to convert from base 10 to base 2</param>
/// <returns>string containing the big endian representation of the number in base 2</returns>
/// <throws>std::invalid_argument exeption if input is invalid or out of the range of accepted numbers for input</throws>
std::string B10ToB2Convert(std::istream& input);
#endif // !PROJECT0_CONVERTER_H
