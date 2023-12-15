#ifndef PROCESS_H
#define PROCESS_H

#include <concepts>

#include <thread>
#include <shared_mutex>
#include <mutex>

#include <stdexcept>

#include <sstream>
#include <string>

#include "Allocator.h"
#include "MemoryManager.h"
#include "ISA.h"

extern const size_t registerCount;

namespace VMFramework
{
	class stack_overflow : public std::exception
	{
	public:
		const char* what() const noexcept override
		{
			return "Stack Overflow detected: Not enough memory remaining for requested allocation";
		}
	};

	class stack_underflow : public std::exception
	{
	public:
		const char* what() const noexcept override
		{
			return "Stack Underflow detected: Calling Pop when there isn't anything on the stack";
		}
	};

	class protection_fault : public std::exception
	{
	private:
		const std::string _msg;
	public:
		explicit protection_fault(std::string&& message) : _msg(message)
		{}

		const char* what() const noexcept override
		{
			return _msg.c_str();
		}
	};

	template<typename RegisterType>
	struct Registers
	{
	public:
		RegisterType registers[registerCount];

		virtual RegisterType& operator[](const size_t& reg)
		{
#ifdef _DEBUG
			if (reg >= registerCount)
			{
				throw std::out_of_range("There is no register " + reg);
			}
#endif // _DEBUG

			return registers[reg];
		}
	};

	template<typename Derived, typename RegisterType, typename ISAType>
	class Process : public Allocator
	{
		//friend class Instruction<RegisterType, Process>;
	protected:
		using ProcessRegisters = Registers<RegisterType>;

		/// <summary>
		/// Register state of this thread of execution
		/// </summary>
		ProcessRegisters& m_registers;

		/// <summary>
		/// Stack for this thread of execution
		/// </summary>
		//StackAllocator* m_stack = nullptr;

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
		const uint8_t* const _programEnd = nullptr;

		/// <summary>
		/// Reference to the Machine instances mutex. Used for concurrent read access and exclusive write access
		/// </summary>
		//const std::shared_mutex& _machineMutex;

		/// <summary>
		/// Pointer to the machines MemoryManager sub-system
		/// </summary>
		MemoryManager<RegisterType>* _memoryManager;

		bool _run = true;

		/// <summary>
		/// Called by Stop
		/// </summary>
		~Process()
		{

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

		//****************************************************************
		//Process's Stack

#ifdef _DEBUG
		void* m_prev_stack_pointer = nullptr;
		void* m_previouse_frame_pointer = nullptr;
#endif // _DEBUG

		void* Allocate(const size_t& size, const uint8_t& alignment) override
		{
			assert(size != 0);

			void* currentPos = _memoryManager->Virtual_To_Physical(m_registers[19]);

			uint8_t adjustment = PointerMath::AlignBackwardAdjustment(currentPos, alignment);

			if (m_usedMemory + adjustment + size > m_size)
				throw stack_overflow();

			void* aligned_address = PointerMath::Subtract(currentPos, adjustment);

#ifdef _DEBUG
			m_prev_stack_pointer = currentPos;
#endif // _DEBUG

			currentPos = PointerMath::Subtract(aligned_address, size);
			m_registers[19] = _memoryManager->Physical_To_Virtual(currentPos);

			m_usedMemory += size + adjustment;

			m_numOfAllocations++;

			return aligned_address;
		}

		void Deallocate(void* p) override
		{
		}

		void ClearAllocator() override
		{
			Allocator::ClearAllocator();

			uint8_t* stackBegin = reinterpret_cast<uint8_t*>(m_start);
			stackBegin += m_size;

			m_registers[18] = m_registers[19] = m_registers[20] = _memoryManager->Physical_To_Virtual(stackBegin);
			m_registers[17] = _memoryManager->Physical_To_Virtual(m_start);

#ifdef _DEBUG
			m_prev_stack_pointer = nullptr;
			m_previouse_frame_pointer = nullptr;
#endif // _DEBUG
		}

		template<typename TypeToPush>
		void* Push(const TypeToPush& itemToPush)
		{
			TypeToPush* stackInstance = static_cast<TypeToPush*>(Allocate(sizeof(TypeToPush), alignof(TypeToPush)));
			*stackInstance = itemToPush;

			return stackInstance;
		}

		template<typename TypeToPop>
		void Pop(TypeToPop& receiver)
		{
			void* currentPos = _memoryManager->Virtual_To_Physical(m_registers[19]);

			uint8_t adjustment = PointerMath::AlignForwardAdjustment(currentPos, alignof(TypeToPop));

			void* prevPos = PointerMath::Add(currentPos, adjustment);

			m_numOfAllocations--;

			receiver = *reinterpret_cast<TypeToPop*>(currentPos);

			m_registers[19] = _memoryManager->Physical_To_Virtual(prevPos);
		}

		template<typename TypeToPeek>
		void Peek(TypeToPeek& receiver)
		{
			void* currentPos = _memoryManager->Virtual_To_Physical(m_registers[19]);

			uint8_t adjustment = PointerMath::AlignForwardAdjustment(currentPos, alignof(TypeToPeek));

			void* prevPos = PointerMath::Add(currentPos, adjustment);

			m_numOfAllocations--;

			receiver = *reinterpret_cast<TypeToPeek*>(currentPos);
		}

		void AdvanceFrame()
		{
#ifdef _DEBUG
			void* currentFramePointer = _memoryManager->Virtual_To_Physical(m_registers[20]);
			m_previouse_frame_pointer = currentFramePointer;
#endif // _DEBUG

			Push<RegisterType>(m_registers[20]);

			m_registers[20] = m_registers[19];
		}
		void RollBackFrame()
		{
			RegisterType* framePointer = static_cast<RegisterType*>(_memoryManager->Virtual_To_Physical(m_registers[20]));
			framePointer++;
			m_registers[20] = *framePointer;
			framePointer++;
			m_registers[19] = _memoryManager->Physical_To_Virtual(framePointer);

#ifdef _DEBUG
			framePointer = static_cast<RegisterType*>(_memoryManager->Virtual_To_Physical(m_registers[20]));

			if (static_cast<RegisterType*>(m_previouse_frame_pointer) != framePointer)
				throw std::logic_error("There is something wrong with the logic of the rolling back of frames, or frame advancement and rollback have not all been handled by the internal functions");
#endif // _DEBUG
		}

		void AdvanceAndLink()
		{
#ifdef _DEBUG
			void* currentFramePointer = _memoryManager->Virtual_To_Physical(m_registers[20]);
			m_previouse_frame_pointer = currentFramePointer;
#endif // _DEBUG

			Push<RegisterType>(m_registers[20]);

			m_registers[20] = m_registers[19];

			Push<RegisterType>(m_registers[16]);
		}
		RegisterType RollBackWithLink()
		{
			RegisterType* framePointer = static_cast<RegisterType*>(_memoryManager->Virtual_To_Physical(m_registers[20]));

			RegisterType& link = *framePointer;

			framePointer++;
			m_registers[20] = *framePointer;
			framePointer++;
			m_registers[19] = _memoryManager->Physical_To_Virtual(framePointer);

#ifdef _DEBUG
			framePointer = static_cast<RegisterType*>(_memoryManager->Virtual_To_Physical(m_registers[20]));

			if (static_cast<RegisterType*>(m_previouse_frame_pointer) != framePointer)
				throw std::logic_error("There is something wrong with the logic of the rolling back of frames, or frame advancement and rollback have not all been handled by the internal functions");
#endif // _DEBUG
		}
		//****************************************************************

		/// <summary>
		/// Used to check if a register id provided as an instruction operand is invalid in the calling context. It is compared to the values provided in the InvalidRegisterIDs and a protection_fault is thrown if it matches any
		/// </summary>
		/// <typeparam name="...InvalidRegisterIDs">A collection of the register IDs that are not valid for the calling context</typeparam>
		/// <param name="id">The register id to validate</param>
		template<uint8_t... InvalidRegisterIDs>
		inline void CheckRegisterIDInvalid(const RegisterType& id)
		{
			((id == InvalidRegisterIDs ? throw protection_fault(std::string(typeid(*this).name()) + " used to modify R" + std::to_string(InvalidRegisterIDs)) : void()), ...);
		}

		inline RegisterType INCREMENT_POINTER(const RegisterType& virtualAddress, const RegisterType& bytesToIncrement)
		{
			uint8_t* physicalAddress = static_cast<uint8_t*>(_memoryManager->Virtual_To_Physical(virtualAddress));
			physicalAddress += bytesToIncrement;
			return _memoryManager->Physical_To_Virtual(physicalAddress);
		}

		inline RegisterType DECREMENT_POINTER(const RegisterType& virtualAddress, const RegisterType& bytesToIncrement)
		{
			uint8_t* physicalAddress = static_cast<uint8_t*>(_memoryManager->Virtual_To_Physical(virtualAddress));
			physicalAddress -= bytesToIncrement;
			return _memoryManager->Physical_To_Virtual(physicalAddress);
		}

		inline RegisterType MULTIPLY_POINTER(const RegisterType& virtualAddress, const RegisterType& multiple)
		{
			uint8_t* physicalAddress = static_cast<uint8_t*>(_memoryManager->Virtual_To_Physical(virtualAddress));
			physicalAddress *= multiple;
			return _memoryManager->Physical_To_Virtual(physicalAddress);
		}

		inline RegisterType DIVIDE_POINTER(const RegisterType& virtualAddress, const RegisterType& divisor)
		{
			uint8_t* physicalAddress = static_cast<uint8_t*>(_memoryManager->Virtual_To_Physical(virtualAddress));
			physicalAddress /= divisor;
			return _memoryManager->Physical_To_Virtual(physicalAddress);
		}

	public:
		/// <summary>
		/// Create Process specifying where in the program it will begin execution
		/// </summary>
		/// <param name="initialPC">Virtual address to the offset in the program to begin execution at</param>
		/// <param name="programStart">Pointer to the beginning of the program in memory</param>
		/// <param name="codeSegmentStart">Pointer to the beginning of the code section of the program in memory</param>
		/// <param name="programEnd">Pointer to the end of the program in memory</param>
		/// <param name="isa">Pointer to the ISA instance to use</param>
		/// <param name="machineMutex">The shared_mutex in the spawning Machine</param>
		/// <param name="memoryManager">Pointer to the machines MemoryManger sub-system</param>
		/// <param name="stackBytes">The number of bytes alloted to this process's stack</param>
		/// <param name="stackStart">The address where the stack begins in memory</param>
		/// <exception cref="std::runtime_error Thrown if the Process cannot be created due to issues with the program pointers supplied"/>
		Process(const void* initialPC, 
			const uint8_t* programStart, const uint8_t* codeSegmentStart, const uint8_t* programEnd, 
			ISAType* isa, Registers<RegisterType>& processRegisters, MemoryManager<RegisterType>* memoryManager,
			const size_t& stackBytes, void* stackStart): Allocator(stackBytes, stackStart),
			_programStart(programStart), _codeSegment(codeSegmentStart), _programEnd(programEnd), 
			_ISA(isa), m_registers(processRegisters), _memoryManager(memoryManager)
		{
			if (initialPC < _programStart || initialPC == nullptr)
			{
				std::stringstream stream;
				stream << "The initial PC cannot be less than the beginning address of the program. Initial PC: 0x"
					<< std::hex
					<< reinterpret_cast<std::uintptr_t>(initialPC)
					<< ". Program start address: 0x"
					<< reinterpret_cast<std::uintptr_t>(_programStart);

				throw std::runtime_error(stream.str());
			}

			this->m_registers[16] = _memoryManager->Physical_To_Virtual(initialPC);

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

			if (initialPC < _codeSegment)
			{
				std::stringstream stream;
				stream << "The initial PC cannot be less than the beginning address of the code segment of the program. Initial PC: 0x"
					<< std::hex
					<< reinterpret_cast<std::uintptr_t>(initialPC)
					<< ". Code start address: 0x"
					<< reinterpret_cast<std::uintptr_t>(_codeSegment);

				throw std::runtime_error(stream.str());
			}

			uint8_t* stackBegin = reinterpret_cast<uint8_t*>(m_start);
			stackBegin += m_size - 1;

			m_registers[18] = m_registers[19] = m_registers[20] = _memoryManager->Physical_To_Virtual(stackBegin);
			m_registers[17] = _memoryManager->Physical_To_Virtual(m_start);
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
			if (_run)
			{
				_run = false;

				delete this;
			}
		}
	};
}
#endif // !PROCESS_H
