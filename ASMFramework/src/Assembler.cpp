#include "../include/Assembler.h"

#include <stdexcept>
#include <cstdint>
#include <shared_mutex>
#include <mutex>
#include <memory>
#include <vector>
#include <iostream>
#include <utility>

#include "rootConfig.h"


#include "../include/Workpiece.h"
#include "../include/Pass.h"
#include "../include/LanguageDefinition.h"

namespace ASMFramework
{
	Assembler::~Assembler()
	{
	}

	void Assembler::ProcessASM(const char* assemblyPath)
	{
		m_filePath = std::filesystem::path(assemblyPath);

		if (!std::filesystem::exists(m_filePath))
			throw std::invalid_argument("No file at path provided: " + m_filePath.string());

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


		for (auto& pass : m_passes)
		{
			pass->Execute(m_workpiece, m_filePath, _languageSpec);
		}
	}

	void Assembler::ProcessASM(std::filesystem::path&& assemblyPath)
	{
		m_filePath = assemblyPath;

		if (!std::filesystem::exists(m_filePath))
			throw std::invalid_argument("No file at path provided: " + m_filePath.string());

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

		for (auto& pass : m_passes)
		{
			pass->Execute(m_workpiece, m_filePath, _languageSpec);
		}
	}
}