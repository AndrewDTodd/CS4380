#include "../../include/Instructions/TRP.h"

#include <iostream>

TRP::TRP() : opcode(21)
{}

void TRP::Op(Process_4380* executingProcess)
{
	int32_t trapNum = executingProcess->operandOne;

	switch (trapNum)
	{
	case (0):
		executingProcess->Stop();
		break;

	case (1):
		std::cout << reinterpret_cast<uint32_t>(executingProcess->m_registers[3]);
		break;

	case(3):
		//Extract lowest byte from R3
		uint8_t lowestByte = static_cast<uint8_t>(executingProcess->m_registers[3] & 0xFF);
		std::cout << static_cast<char>(lowestByte);
		break;
	}
}