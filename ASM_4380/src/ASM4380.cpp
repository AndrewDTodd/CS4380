#include "../include/ASM4380.h"

#include <filesystem>
#include <iostream>

#include "rootConfig.h"

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

void ASM4380::ProcessASM(const char* assemblyPath)
{
	BLUE_TERMINAL
		std::cout << "Assembling program at >> " << assemblyPath << std::endl;
	RESET_TERMINAL

	m_filePath = std::filesystem::path(assemblyPath);
	
	if (!std::filesystem::exists(m_filePath))
	{
		throw std::invalid_argument("No file at path provided: " + std::string(assemblyPath));
	}

	_passOne.Execute(m_workpiece, m_filePath, _languageSpec);

	_passTwo.Execute(m_workpiece, m_filePath, _languageSpec);

	_passThree.Execute(m_workpiece, m_filePath, _languageSpec);
}