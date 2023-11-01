#include "../include/LanguageDefinition_4380.h"

#include <string>

//*************************************************************************************
LanguageDefinition_4380::LanguageDefinition_4380() :
	ASMFramework::LanguageDefinition()
{
	SetDirectives(BYTE, CSTRING, INTEGER, STRING);
	SetInstructions(
		ADD, ADI, SUB, MUL, MULI, DIV, DIVI,
		CMP, CMPI,
		ALCI, ALLC, FREE,
		JMP, JMR, BNZ, BGT, BLT, BRZ,
		AND, NOT, OR,
		MOV, MOVI, LDA, STR, LDR, STB, LDB,
		RUN, BLK, END, LCK, ULK,
		TRP);
	SetRegisterMnemonics(
		std::string("R0"), std::string("R1"), std::string("R2"), std::string("R3"), std::string("R4"), std::string("R5"),
		std::string("R6"), std::string("R7"), std::string("R8"), std::string("R9"), std::string("R10"), std::string("R11"),
		std::string("R12"), std::string("R13"), std::string("R14"), std::string("R15"),
		std::string("PC"), std::string("SL"), std::string("SB"), std::string("SP"), std::string("FP"), std::string("HP"));
}