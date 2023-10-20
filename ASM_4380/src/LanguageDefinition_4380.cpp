#include "../include/LanguageDefinition_4380.h"

#include <string>

//Directives instantiation ************************************************************
#include "../include/Directives/BYT_DIR.h"
#include "../include/Directives/CSTR_DIR.h"
#include "../include/Directives/INT_DIR.h"
#include "../include/Directives/STR_DIR.h"

BYT_DIR BYTE;
CSTR_DIR CSTRING;
INT_DIR INTEGER;
STR_DIR STRING;
//*************************************************************************************

//Instructions instantiation **********************************************************
#include "../include/Instructions/Instructions.h"

//Arithmetic
ADD_INS ADD;
ADI_INS ADI;
DIVI_INS DIVI;
DIV_INS DIV;
MULI_INS MULI;
MUL_INS MUL;
SUB_INS SUB;

//Compare
CMPI_INS CMPI;
CMP_INS CMP;

//Heap
ALCI_INS ALCI;
ALLC_INS ALLC;
FREE_INS FREE;

//Jump
BGT_INS BGT;
BLT_INS BLT;
BNZ_INS BNZ;
BRZ_INS BRZ;
JMP_INS JMP;
JMR_INS JMR;

//Logical
AND_INS AND;
NOT_INS NOT;
OR_INS OR;

//Move
LDA_INS LDA;
LDB_INS LDB;
LDR_INS LDR;
MOVI_INS MOVI;
MOV_INS MOV;
STB_INS STB;
STR_INS STR;

//Multi_Thread
BLK_INS BLK;
END_INS END;
LCK_INS LCK;
RUN_INS RUN;
ULK_INS ULK;

//TRP
TRP_INS TRP;

//*************************************************************************************
LanguageDefinition_4380::LanguageDefinition_4380() :
	LanguageDefinition()
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
	SetKeywords(
		std::string("R0"), std::string("R1"), std::string("R2"), std::string("R3"), std::string("R4"), std::string("R5"),
		std::string("R6"), std::string("R7"), std::string("R8"), std::string("R9"), std::string("R10"), std::string("R11"),
		std::string("R12"), std::string("R13"), std::string("R14"), std::string("R15"),
		std::string("PC"), std::string("SL"), std::string("SB"), std::string("SP"), std::string("FP"), std::string("HP")
	);
}