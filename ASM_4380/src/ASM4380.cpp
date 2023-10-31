#include "../include/ASM4380.h"

#include <filesystem>
#include <iostream>

#include "rootConfig.h"

bool ASM4380::_trapZero = false;

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
	m_filePath = std::filesystem::path(assemblyPath);
	
	if (!std::filesystem::exists(m_filePath))
	{
		throw std::invalid_argument("No file at path provided: " + m_filePath.string());
	}

	if (m_filePath.extension() != ".asm")
	{
		YELLOW_TERMINAL
			std::cerr << "**Warning** >> The extension for the provided file is " << m_filePath.extension() << ", expected .asm. Is this a valid assembly file? Use the .asm extension." << std::endl;
			std::cout << std::endl;
		RESET_TERMINAL
	}

	BLUE_TERMINAL
		std::cout << "Assembling program at >> " << m_filePath.string() << std::endl;
	RESET_TERMINAL

	_passOne.Execute(m_workpiece, m_filePath, _languageSpec);

	_passTwo.Execute(m_workpiece, m_filePath, _languageSpec);

	_passThree.Execute(m_workpiece, m_filePath, _languageSpec);
}

void ASM4380::ProcessASM(std::filesystem::path&& assemblyPath)
{
	m_filePath = assemblyPath;

	if (!std::filesystem::exists(m_filePath))
	{
		throw std::invalid_argument("No file at path provided: " + m_filePath.string());
	}

	if (m_filePath.extension() != ".asm")
	{
		YELLOW_TERMINAL
			std::cerr << "**Warning** >> The extension for the provided file is " << m_filePath.extension() << ", expected .asm. Is this a valid assembly file? Use the .asm extension." << std::endl;
			std::cout << std::endl;
		RESET_TERMINAL
	}

	BLUE_TERMINAL
		std::cout << "Assembling program at >> " << m_filePath.string() << std::endl;
	RESET_TERMINAL

	_passOne.Execute(m_workpiece, m_filePath, _languageSpec);

	_passTwo.Execute(m_workpiece, m_filePath, _languageSpec);

	_passThree.Execute(m_workpiece, m_filePath, _languageSpec);
}