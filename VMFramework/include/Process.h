#ifndef PROCESS_H
#define PROCESS_H

#include <concepts>
#include <thread>
#include <shared_mutex>
#include <mutex>

#include "StackAllocator.h"
#include "MemoryManager.h"
#include "ISA.h"

constexpr size_t registerCount = 16;

namespace VMFramework
{
	template<typename GPRegisterType, typename RegisterType>
	//requires std::integral<RegisterType>
	struct Registers
	{
	public:
		GPRegisterType gpRegisters[registerCount];

		RegisterType* PC = 0;

		GPRegisterType& operator[](const size_t& reg)
		{
#ifdef _DEBUG
			if (reg < 0 || reg >= registerCount)
			{
				throw std::out_of_range("There is no register " + reg);
			}
#endif // _DEBUG

			return gpRegisters[reg];
		}
	};

	template<typename Derived, typename GPRegisterType, typename RegisterType, typename ISAType>
	//requires std::integral<RegisterType>
	class Process
	{
		//friend class Instruction<GPRegisterType, RegisterType, Process>;
	protected:
		using ProcessRegisters = Registers<GPRegisterType, RegisterType>;

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
		/// Pointer to the begining of the program segment in memory
		/// </summary>
		void* _programSegment = nullptr;

		/// <summary>
		/// Pointer to the begining of the code in the programSegment
		/// </summary>
		void* _codeSegment = nullptr;

		/// <summary>
		/// Reference to the Machines shared_mutex
		/// </summary>
		//std::shared_mutex& _machineMutex;

		/// <summary>
		/// Concurrent read lock used to lock Process and Instruction reads of Machine. Initialized at Process creation with lock established
		/// </summary>
		const std::shared_lock<std::shared_mutex> m_readLock;

		/// <summary>
		/// Unique write lock used to lock Process and Instruction writes of Machine resources. Initialized at Process creation without lock established. Lock is made by writing Instruction call
		/// </summary>
		const std::unique_lock<std::shared_mutex>* m_writeLock = nullptr;

		bool _run = true;

		/// <summary>
		/// Called by Stop
		/// </summary>
		~Process()
		{
			m_stack->ClearAllocator();
			
			//Free this process stack from tehe system's resources
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
		/// <param name="initialPC">The address in the program to begin execution at</param>
		/// <param name="processStack">Pointer to the StackAllocator for this process</param>
		/// <param name="programStart">Pointer to the begining of the program in memory</param>
		/// <param name="machineMutex">The shared_mutex in the spawning Machine</param>
		/// <param name="isa">Pointer to the ISA instance to use</param>
		Process(void* initialPC, StackAllocator* processStack, void* programStart, void* codeSegmentStart, std::shared_mutex& machineMutex, ISAType* isa): 
			m_stack(processStack), _programSegment(programStart), _codeSegment(codeSegmentStart), m_readLock(machineMutex), _ISA(isa)
		{
			this->m_registers.PC = reinterpret_cast<RegisterType*>(initialPC);

			m_writeLock = new std::unique_lock<std::shared_mutex>(machineMutex, std::defer_lock);
		}

		/// <summary>
		/// Run this Process. Preforms the steps of the execution cyle until Stop called
		/// </summary>
		void Run()
		{
			while (_run)
			{
				Fetch();
				Increment();
				Decode();
				Execute();
			}
		}

		/// <summary>
		/// Stop this Process
		/// </summary>
		void Stop()
		{
			_run = false;

			delete this;
		}
	};
}
#endif // !PROCESS_H
