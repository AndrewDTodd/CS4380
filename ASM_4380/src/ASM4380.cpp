#include "../include/ASM4380.h"

ASM4380::ASM4380():
	_passOne(),
	_passTwo(),
	_workpiece(),
	_languageDef(),
	Assembler(&_workpiece, &_languageDef, &_passOne, &_passTwo, &_passThree)
{}

ASM4380::~ASM4380()
{}

void ASM4380::ShutDown()
{
	this->~ASM4380();
}