#ifndef PROCESS_H
#define PROCESS_H

#include <concepts>

#include "StackAllocator.h"

namespace VMFramework
{
	template<typename GPRegisterType, typename RegisterType>
	requires std::integral<RegisterType>
	struct Registers
	{
	public:
		GPRegisterType R0 = 0;
		GPRegisterType R1 = 0;
		GPRegisterType R2 = 0;
		GPRegisterType R3 = 0;
		GPRegisterType R4 = 0;
		GPRegisterType R5 = 0;
		GPRegisterType R6 = 0;
		GPRegisterType R7 = 0;
		GPRegisterType R8 = 0;
		GPRegisterType R9 = 0;
		GPRegisterType R10 = 0;
		GPRegisterType R11 = 0;
		GPRegisterType R12 = 0;
		GPRegisterType R13 = 0;
		GPRegisterType R14 = 0;
		GPRegisterType R15 = 0;

		RegisterType PC = 0;
	};

	template<typename GPRegisterType, typename RegisterType>
	requires std::integral<RegisterType>
	class Process
	{
	private:
		/// <summary>
		/// Register state of this thread of execution
		/// </summary>
		Registers<GPRegisterType, RegisterType> m_registers;

		/// <summary>
		/// Stack for this thread of execution
		/// </summary>
		StackAllocator* m_stack = nullptr;
	public:
		/// <summary>
		/// Create Process and specify the starting point for its stack in system memory
		/// </summary>
		/// <param name="stackStart">The address to make the stack at</param>
		Process(void* stackStart);
		~Process();

		/// <summary>
		/// Run this Process
		/// </summary>
		void Execute();

		/// <summary>
		/// Stop this Process
		/// </summary>
		void Stop();
	};
}
#endif // !PROCESS_H
