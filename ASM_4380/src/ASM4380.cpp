#include "../include/ASM4380.h"

//Passes instantiation ****************************************************************
#include "../include/PassOne.h"
#include "../include/PassTwo.h"
#include "../include/PassThree.h"

PassOne _passOne;
PassTwo _passTwo;
PassThree _passThree;
//*************************************************************************************

//Workpiece instantiation *************************************************************
#include <Workpiece.h>

Workpiece _workpiece;
//*************************************************************************************

//LanguageDefinition instantiation ****************************************************
#include "../include/LanguageDefinition_4380.h"

LanguageDefinition_4380 _languageDef;
//*************************************************************************************

ASM4380::ASM4380(): 
	Assembler(_workpiece, _languageDef, _passOne, _passTwo, _passThree)
{}

ASM4380::~ASM4380()
{}