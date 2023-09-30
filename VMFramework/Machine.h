#ifndef MACHINE_H
#define MACHINE_H

#include <concepts>
#include <type_traits>

#include <thread>
#include <shared_mutex>
#include <vector>

#include "MemoryManager.h"
#include "Process.h"
#include "ISA.h"

namespace VMFramework
{
	template<typename GPRegisterType, typename RegisterType, typename OpCodeType, typename ISA>
	requires std::integral<RegisterType> && std::integral<OpCodeType> && std::derived_from<ISA, VMFramework::ISA<OpCodeType>>
	class Machine
	{
	private:
		/// <summary>
		/// After GetInstance is called this pointer will point to the singleton's instance
		/// </summary>
		static Machine* s_instance = nullptr;

		/// <summary>
		/// After StartUp will point to the machine's memory manager that is used to control dynamic memory allocation for stack and heaps as well as program segment
		/// </summary>
		MemoryManager* m_memoryManager = nullptr;

		ISA m_ISA;

		/// <summary>
		/// List of the processes/threads executing in the machine
		/// </summary>
		std::vector<VMFramework::Process<GPRegisterType, RegisterType>> m_processes = std::vector<VMFramework::Process<GPRegisterType, RegisterType>>();

		//Machine is singleton, do not attempt to make instance. Constructor is private for internal use only
		Machine();
		~Machine();

		/// <summary>
		/// Create a new process to execute starting at the specified program location
		/// </summary>
		/// <param name="startInstruction">Pointer to the location in the program where this process should begin execution</param>
		void SpawnProcess(void* startInstruction);
	public:
		/// <summary>
		/// Get pointer to the singleton's instance
		/// </summary>
		/// <returns>Pointer to Machine instance</returns>
		static Machine* GetInstance();

		/// <summary>
		/// Will launch the machine and initialize the system
		/// </summary>
		void StartUp();

		/// <summary>
		/// Will launch the machine and initialize the system then attempt to launch a program from the specified binaries path
		/// </summary>
		/// <param name="programBinary">Path to a valid program binary to run</param>
		void StartUp(char* programBinary);

		/// <summary>
		/// Will safely shut down the system and free resources
		/// </summary>
		void ShutDown();

		/// <summary>
		/// Will attempt to load the binary at the specified path and run the program
		/// </summary>
		/// <param name="programBinary">Path to a valid program binary to run</param>
		void LaunchProgram(char* programBinary);
	};
}
#endif //!MACHINE_H
