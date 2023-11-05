#ifndef PROCESS_H
#define PROCESS_H

#include <concepts>

#include <thread>
#include <shared_mutex>
#include <mutex>

#include <stdexcept>

#include <sstream>
#include <string>

#include "StackAllocator.h"
#include "MemoryManager.h"
#include "ISA.h"

constexpr size_t registerCount = 22;

namespace VMFramework
{
	template<typename RegisterType>
	struct Registers
	{
	public:
		RegisterType registers[registerCount];

		RegisterType& operator[](const size_t& reg)
		{
#ifdef _DEBUG
			if (reg < 0 || reg >= registerCount)
			{
				throw std::out_of_range("There is no register " + reg);
			}
#endif // _DEBUG

			return registers[reg];
		}
	};

	template<typename Derived, typename RegisterType, typename ISAType>
	class Process
	{
		//friend class Instruction<RegisterType, Process>;
	protected:
		using ProcessRegisters = Registers<RegisterType>;

		/// <summary>
		/// Register state of this thread of execution
		/// </summary>
		ProcessRegisters m_registers;

		/// <summary>
		/// Stack for this thread of execution
		/// </summary>
		StackAllocator* m_stack = nullptr;

		/// <summary>
		/// Pointer to ISA to use
		/// </summary>
		const ISAType* _ISA = nullptr;

		/// <summary>
		/// Pointer to the first byte of the program segment in memory
		/// </summary>
		const uint8_t* const _programStart = nullptr;

		/// <summary>
		/// Pointer to the first byte of the code segment in the program segment in memory
		/// </summary>
		const uint8_t* const _codeSegment = nullptr;

		/// <summary>
		/// Pointer to the last byte in the program segment
		/// </summary>
		const uint8_t* const _programEnd= nullptr;

		/// <summary>
		/// Reference to the Machine instances mutex. Used for concurrent read access and exclusive write access
		/// </summary>
		const std::shared_mutex& _machineMutex;

		bool _run = true;

		/// <summary>
		/// Called by Stop
		/// </summary>
		~Process()
		{
			m_stack->ClearAllocator();
			
			//Free this process stack from the system's resources
			DeallocateDelete<StackAllocator>(*MemoryManager::GetInstance()->m_systemAllocator, *m_stack);
		}

		/// <summary>
		/// Used to preform the fetch step of execution cycle
		/// </summary>
		inline virtual void Fetch() = 0;

		/// <summary>
		/// Used to preform the increment step of the execution cycle
		/// </summary>
		inline virtual void Increment() = 0;

		/// <summary>
		/// Used to preform the decode step of execution cycle
		/// </summary>
		inline virtual void Decode() = 0;

		/// <summary>
		/// Used to preform the execute step of the execution cycle
		/// </summary>
		inline virtual void Execute() = 0;
	public:
		/// <summary>
		/// Create Process specifying where in the program it will begin execution
		/// </summary>
		/// <param name="initialPC">The offset in the program to begin execution at</param>
		/// <param name="processStack">Pointer to the StackAllocator for this process</param>
		/// <param name="programStart">Pointer to the beginning of the program in memory</param>
		/// <param name="codeSegmentStart">Pointer to the beginning of the code section of the program in memory</param>
		/// <param name="programEnd">Pointer to the end of the program in memory</param>
		/// <param name="machineMutex">The shared_mutex in the spawning Machine</param>
		/// <param name="isa">Pointer to the ISA instance to use</param>
		/// <exception cref="std::runtime_error Thrown if the Process cannot be created due to issues with the program pointers supplied"/>
		Process(const RegisterType& initialPC, StackAllocator* processStack, 
			const uint8_t* programStart, const uint8_t* codeSegmentStart, const uint8_t* programEnd, 
			std::shared_mutex& machineMutex, ISAType* isa): 
			m_stack(processStack), _programStart(programStart), _codeSegment(codeSegmentStart), _programEnd(programEnd), _machineMutex(machineMutex), _ISA(isa)
		{
			this->m_registers[16] = initialPC;

			if (_programStart == nullptr || _codeSegment == nullptr || _programEnd == nullptr)
			{
				throw std::runtime_error("Cannot spawn process without a pointer to the start of the program, or a pointer to the start of the code segment in the program, or a pointer to the end of the program");
			}

			if (_codeSegment < _programStart)
			{
				std::stringstream stream;
				stream << "The instruction portion of a program must be within the program space. Code start in program indicated as less than program start. Program start address : 0x" 
					<< std::hex
					<< reinterpret_cast<std::uintptr_t>(_programStart)
					<< ". Code start address: 0x"
					<< reinterpret_cast<std::uintptr_t>(_codeSegment);

				throw std::runtime_error(stream.str());
			}

			if (_programStart + this->m_registers[16] < _codeSegment)
			{
				std::stringstream stream;
				stream << "The initial PC cannot be less than the beginning address of the code segment of the program. Initial PC: 0x"
					<< std::hex
					<< reinterpret_cast<std::uintptr_t>(_programStart + this->m_registers[16])
					<< ". Code start address: 0x"
					<< reinterpret_cast<std::uintptr_t>(_codeSegment);

				throw std::runtime_error(stream.str());
			}

			if (_programStart + this->m_registers[16] < _programStart)
			{
				std::stringstream stream;
				stream << "The initial PC cannot be less than the beginning address of the program. Initial PC: 0x"
					<< std::hex
					<< reinterpret_cast<std::uintptr_t>(_programStart + this->m_registers[16])
					<< ". Program start address: 0x"
					<< reinterpret_cast<std::uintptr_t>(_programStart);

				throw std::runtime_error(stream.str());
			}
		}

		/// <summary>
		/// Run this Process. Preforms the steps of the execution cyle until Stop called
		/// </summary>
		void Run()
		{
			int i = 0;
			while (_run)
			{
				Fetch();
				Increment();
				Decode();
				Execute();
				i++;
			}
		}

		/// <summary>
		/// Stop this Process
		/// </summary>
		void Stop()
		{
			if (_run)
			{
				_run = false;

				delete this;
			}
		}
	};
}
#endif // !PROCESS_H
