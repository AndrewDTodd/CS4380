#include "../include/Assembler.h"

#include <stdexcept>
#include <cstdint>
#include <shared_mutex>
#include <mutex>
#include <memory>
#include <vector>
#include <iostream>
#include <utility>


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
		std::ifstream fileStream(assemblyPath);

		if (!fileStream.is_open())
		{
			throw std::invalid_argument("Unable to open file at path: " + std::string(assemblyPath));
		}

		const_cast<std::unique_ptr<std::ifstream>&>(m_fileStream) = std::make_unique<std::ifstream>(std::move(fileStream));

		for (auto& pass : m_passes)
		{
			pass->Execute(m_workpiece, m_fileStream, _languageSpec);
		}

		fileStream.close();
	}
}