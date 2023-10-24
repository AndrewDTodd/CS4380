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
		BLUE_TERMINAL
			std::cout << "Assembling program at >> " << assemblyPath << std::endl;
		RESET_TERMINAL

		m_filePath = std::filesystem::path(assemblyPath);

		if (!std::filesystem::exists(m_filePath))
		{
			throw std::invalid_argument("No file at path provided: " + std::string(assemblyPath));
		}

		for (auto& pass : m_passes)
		{
			pass->Execute(m_workpiece, m_filePath, _languageSpec);
		}
	}
}