#ifndef LANGUAGE_DEFINITION_4380_H
#define LANGUAGE_DEFINITION_4380_H

#include <LanguageDefinition.h>

#include <gtest/gtest_prod.h>

#include "Directives/BYT_DIR.h"
#include "Directives/CSTR_DIR.h"
#include "Directives/INT_DIR.h"
#include "Directives/STR_DIR.h"

#include "Instructions/ASM_Instructions.h"

class LanguageDefinition_4380 : public ASMFramework::LanguageDefinition
{
private:
	//Directives instantiation ************************************************************
	BYT_DIR BYTE;
	CSTR_DIR CSTRING;
	INT_DIR INTEGER;
	STR_DIR STRING;
	//*************************************************************************************

	//Instructions instantiation **********************************************************

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

public:
	LanguageDefinition_4380();
};
#endif // !LANGUAGE_DEFINITION_4380_H
