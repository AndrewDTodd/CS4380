#ifndef MACHINE_H
#define MACHINE_H

#include <iostream>
#include <string>

#include <concepts>
#include <type_traits>

#include <new>
#include <thread>
#include <shared_mutex>
#include <mutex>
#include <stdexcept>
#include <concepts>
#include <type_traits>
#include <fstream>
#include <string>

#include "MemoryManager.h"
#include "Process.h"
#include "ISA.h"

#define PROCESS_STACK_MiB 8
#define PROCESS_STACK_BYTES (MebiByte * PROCESS_STACK_MiB)

namespace VMFramework
{
	template<typename Derived, typename GPRegisterType, typename RegisterType, typename ProcessType, typename ISA>
	requires std::integral<RegisterType> && std::derived_from<ProcessType, VMFramework::Process<GPRegisterType, RegisterType>> && std::derived_from<ISA, VMFramework::ISA<GPRegisterType, RegisterType, ProcessType>>
	class Machine
	{
		friend class Instruction<GPRegisterType, RegisterType, ProcessType>;
	protected:
		using MachineType = Machine<Derived, GPRegisterType, RegisterType, ProcessType, ISA>;

		/// <summary>
		/// SharedMutex for concurrent read access and exclusive write access
		/// </summary>
		static std::shared_mutex _sharedMutex;

		static std::mutex _launchMutex;

		/// <summary>
		/// After GetInstance is called this pointer will point to the singleton's instance
		/// </summary>
		static MachineType* s_instance;

		/// <summary>
		/// After StartUp will point to the machine's memory manager that is used to control dynamic memory allocation for stack and heaps as well as program segment
		/// </summary>
		MemoryManager* m_memoryManager = nullptr;

		ISA m_ISA;

		/// <summary>
		/// List of the processes/threads executing in the machine
		/// </summary>
		std::vector<ProcessType> m_processes = std::vector<ProcessType>();

		/// <summary>
		/// Pointer to the begining (first byte) of the program's data in memory
		/// </summary>
		void* m_programSegment = nullptr;

		/// <summary>
		/// Pointer to the start of the code segment
		/// </summary>
		void* m_beginingCode = nullptr;

		/// <summary>
		/// The total number of bytes in the programSegment
		/// </summary>
		size_t m_programSize = 0;

		/// <summary>
		/// Default constructor is private, Machine is a singleton. Internal use only
		/// </summary>
		Machine()
		{
		}

		/// <summary>
		/// Default destructor is private, Machine is a singleton. Internal use only
		/// </summary>
		~Machine()
		{
		}

		/// <summary>
		/// Loads the program data into the m_programSegment
		/// </summary>
		virtual void LoadProgram(char* programBinary)
		{
			std::ifstream file(programBinary, std::ios::binary | std::ios::ate);
			if (file.is_open())
			{
				std::streampos size = file.tellg();
				m_programSize = file.tellg();
			}
			else
				throw std::invalid_argument("Unable to open file at path: " + std::string(programBinary));

			//May throw stack_overflow exeption if system memory insufficient for program. Handled in caller LaunchProgram
			m_programSegment = AllocateArray<uint8_t>(m_memoryManager->m_systemAllocator, m_programSize);

			//Read file into m_programSegment byte array
			if (!file.read(static_cast<char*>(m_programSegment), m_programSize))
			{
				file.close();
				//Failed to read program into memory
				throw std::runtime_error("Unknown error occured resulting in failure to load program");
			}

			file.close();
		}

		/// <summary>
		/// Create a new process to execute starting at the specified program location
		/// </summary>
		/// <param name="startInstruction">Pointer to the location in the program where this process should begin execution</param>
		virtual void SpawnProcess(void* startInstruction)
		{
			StackAllocator* processStack = AllocateNew<StackAllocator>(PROCESS_STACK_BYTES, this->m_memoryManager->m_systemAllocator);

			ProcessType process(startInstruction, processStack, m_programSegment, m_beginingCode, _sharedMutex, &m_ISA);

			this->m_processes.push_back(std::move(process));

			std::thread thread(&process.Run, &process);

			//wait for the thread to finish (only good for single thread program)
			thread.join();
		}

	public:
		/// <summary>
		/// Get pointer to the singleton's instance
		/// </summary>
		/// <returns>Pointer to Machine instance</returns>
		static Derived* GetInstance()
		{
			//Aquire concurrent lock for read access
			std::shared_lock<std::shared_mutex> readLock(_sharedMutex);

			if (!s_instance)
			{
				//Lock the Machine for write
				std::unique_lock<std::shared_mutex> writeLock(_sharedMutex);

				if (!s_instance)
				{
					s_instance = new Derived();
					return s_instance;
				}
			}
			else
			{
				return s_instance;
			}
		}

		/// <summary>
		/// Will launch the machine and initialize the system
		/// </summary>
		void StartUp()
		{
			//Lock the Machine for a write
			std::unique_lock<std::shared_mutex> writeLock(_sharedMutex);

			//Aquire pointer to MemoryManager instance and initialize the subsystem
			this->m_memoryManager = MemoryManager::GetInstance();
			this->m_memoryManager->StartUp();
		}

		/// <summary>
		/// Will launch the machine and initialize the system then attempt to launch a program from the specified binaries path
		/// </summary>
		/// <param name="programBinary">Path to a valid program binary to run</param>
		void StartUp(char* programBinary)
		{
			//Lock the Machine for a write
			std::unique_lock<std::shared_mutex> writeLock(_sharedMutex);

			//Aquire pointer to MemoryManager instance and initialize the subsystem
			this->m_memoryManager = MemoryManager::GetInstance();
			this->m_memoryManager->StartUp();

			//lauch the provided program
			try
			{
				LaunchProgram(programBinary);
			}
			catch (std::runtime_error runtimeEx)
			{
				std::cerr << "Error: " << runtimeEx.what() << std::endl;
			}
		}

		/// <summary>
		/// Will safely shut down the system and free resources
		/// </summary>
		void ShutDown()
		{
			//Lock the Machine for a write
			std::unique_lock<std::shared_mutex> writeLock(_sharedMutex);

			//Shut down the running processes
			for (ProcessType& process : m_processes)
			{
				process.Stop();
			}

			this->m_memoryManager->ShutDown();
			this->m_memoryManager = nullptr;

			Machine::s_instance = nullptr;

			this->~Machine();
		}

		/// <summary>
		/// Will attempt to load the binary at the specified path and run the program
		/// </summary>
		/// <param name="programBinary">Path to a valid program binary to run</param>
		/// <exeption cref="rumtime_error">Thrown if initial PC specified in loaded binary is invalid</exeption>
		virtual void LaunchProgram(char* programBinary)
		{
			//Lock the Machine for a , use _launchMutex as this method can be called by StartUp which also aquires a lock
			std::unique_lock<std::mutex> writeLock(_launchMutex);

			try
			{
				LoadProgram(programBinary);
			}
			catch (const std::invalid_argument& invalidArgEx)
			{
				std::cerr << "Error: " << invalidArgEx.what() << std::endl;
			}
			catch (const stack_overflow& overflowEx)
			{
				std::cerr << "Error: Could not load program into VM, not enough memory in system" << std::endl;
			}
			catch (const std::runtime_error& loadEx)
			{
				std::cerr << "Error: " << loadEx.what() << std::endl;
			}

			//Get the offset to the initial PC from the first 4 bytes in program
			int32_t offset = *reinterpret_cast<int32_t*>(m_programSegment);

			if (offset < 0 || offset >= m_programSize)
				throw std::runtime_error("Offset to initial PC at begining of program is invalid. Offset is to byte " + std::to_string(offset) + ". Program size is " + std::to_string(m_programSize) + " bytes.");

			m_beginingCode = m_programSegment + offset;

			SpawnProcess(m_beginingCode);
		}
	};
}
#endif //!MACHINE_H
