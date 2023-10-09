#include "../include/Assembler.h"

#include <stdexcept>

#include <cstdint>

#include <shared_mutex>
#include <mutex>

#include <memory>

#include <vector>

#include <iostream>

namespace ASMFramework
{
	Assembler::Assembler(const DerivedFromPass auto&... passes, const Workpiece& workpiece): m_workpiece(&workpiece)
	{
		(m_passes.push_back(&passes), ...);
	}
	Assembler::~Assembler()
	{}

	void Assembler::ProcessASM(const char* assemblyPath)
	{
		std::ifstream file(assemblyPath);

		if (!file.is_open())
		{
			throw std::invalid_argument("Unable to open file at path: " + std::string(assemblyPath));
		}
	}
}