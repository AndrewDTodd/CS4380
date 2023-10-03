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
	requires std::integral<RegisterType> && std::derived_from<ProcessType, VMFramework::Process<ProcessType, GPRegisterType, RegisterType, ISA>> && std::derived_from<ISA, VMFramework::ISA<GPRegisterType, RegisterType, ProcessType>>
	class Machine
	{
		friend class Instruction<GPRegisterType, RegisterType, ProcessType>;
	protected:
		using MachineType = Machine<Derived, GPRegisterType, RegisterType, ProcessType, ISA>;

		/// <summary>
		/// SharedMutex for concurrent read access and exclusive write access
		/// </summary>
		inline static std::shared_mutex _sharedMutex;

		/// <summary>
		/// After GetInstance is called this pointer will point to the singleton's instance
		/// </summary>
		inline static Derived* s_instance = nullptr;

		/// <summary>
		/// After StartUp will point to the machine's memory manager that is used to control dynamic memory allocation for stack and heaps as well as program segment
		/// </summary>
		MemoryManager* m_memoryManager = nullptr;

		ISA m_ISA;

		/// <summary>
		/// List of the processes/threads executing in the machine
		/// </summary>
		std::vector<ProcessType*> m_processes = std::vector<ProcessType*>();
		std::vector<std::thread> m_processThreads = std::vector<std::thread>();

		/// <summary>
		/// Pointer to the begining (first byte) of the program's data in memory
		/// </summary>
		uint8_t* m_programSegment = nullptr;

		/// <summary>
		/// Pointer to the start of the code segment
		/// </summary>
		uint8_t* m_codeSegment = nullptr;

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
			//std::ifstream file(programBinary, std::ios::binary | std::ios::ate);
			//if (file.is_open())
			//{
			//	std::streampos size = file.tellg();
			//	m_programSize = file.tellg();
			//}
			//else
			//	throw std::invalid_argument("Unable to open file at path: " + std::string(programBinary));

			////May throw stack_overflow exeption if system memory insufficient for program. Handled in caller LaunchProgram
			//m_programSegment = AllocateArray<uint8_t>(m_memoryManager->m_systemAllocator, m_programSize);

			////Read file into m_programSegment byte array
			//if (!file.read(static_cast<char*>(m_programSegment), m_programSize))
			//{
			//	file.close();
			//	//Failed to read program into memory
			//	throw std::runtime_error("Unknown error occured resulting in failure to load program");
			//}

			//file.close();

			std::ifstream file(programBinary, std::ios::binary | std::ios::ate);

			if (!file.is_open())
			{
				throw std::invalid_argument("Unable to open file at path: " + std::string(programBinary));
			}

			// Get the file size
			std::streampos size = file.tellg();
			if (size < 0)
			{
				// Failed to determine file size
				file.close();
				throw std::runtime_error("Failed to determine file size");
			}

			// Allocate memory
			m_programSize = static_cast<size_t>(size);
			m_programSegment = AllocateArray<uint8_t>(m_memoryManager->m_systemAllocator, m_programSize);

			if (!m_programSegment)
			{
				// Allocation failed
				file.close();
				throw std::runtime_error("Memory allocation failed");
			}

			// Read file into m_programSegment byte array
			file.seekg(0, std::ios::beg); // Move file cursor to the beginning
			if (!file.read(reinterpret_cast<char*>(m_programSegment), m_programSize))
			{
				// Read failed
				file.close();
				throw std::runtime_error("Failed to read program into memory");
			}

			file.close();
		}

		/// <summary>
		/// Will attempt to load the binary at the specified path and run the program. Used by StartUp(char*) to launch program
		/// </summary>
		/// <param name="programBinary">Path to a valid program binary to run</param>
		/// <exeption cref="rumtime_error">Thrown if initial PC specified in loaded binary is invalid</exeption>
		virtual inline void LaunchProgram_INTERNAL(char* programBinary)
		{
			//Lock has already been obtained by the calling StartUp(char*) method
			try
			{
				LoadProgram(programBinary);
			}
			//invalid_argument: could not find file at path given
			catch (const std::invalid_argument& invalidArgEx)
			{
				std::cerr << "Error: " << invalidArgEx.what() << std::endl;
				return;
			}
			//Program too big to load into VM
			catch (const stack_overflow& overflowEx)
			{
				std::cerr << "Error: Could not load program into VM, not enough memory in system" << std::endl;
				return;
			}
			//Could not deturmine program size, memory allocation failed, or could not load program into memory
			catch (const std::runtime_error& loadEx)
			{
				std::cerr << "Error: " << loadEx.what() << std::endl;
				return;
			}

			//Get the offset to the initial PC from the first 4 bytes in program
			//!!REMEMBER ITS IN LITTLE-ENDIAN!!!:(
			int32_t offset = static_cast<int32_t>(m_programSegment[0]);
			/*offset |= static_cast<int32_t>(m_programSegment[1]) << 8;
			offset |= static_cast<int32_t>(m_programSegment[2]) << 16;
			offset |= static_cast<int32_t>(m_programSegment[3]) << 24;*/

			if (offset < 0 || offset >= m_programSize)
				throw std::runtime_error("Offset to initial PC at begining of program is invalid. Offset is to byte " + std::to_string(offset) + ". Program size is " + std::to_string(m_programSize) + " bytes.");

			m_codeSegment = static_cast<uint8_t*>(m_programSegment) + offset;

			SpawnProcess(m_codeSegment);
		}

		/// <summary>
		/// Create a new process to execute starting at the specified program location
		/// </summary>
		/// <param name="startInstruction">Pointer to the location in the program where this process should begin execution</param>
		virtual void SpawnProcess(void* initialPC) = 0;

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
				readLock.unlock();
				//Lock the Machine for write
				std::unique_lock<std::shared_mutex> writeLock(_sharedMutex);

				if (!s_instance)
				{
					s_instance = new Derived();
					return s_instance;
				}
			}
				return s_instance;
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
				LaunchProgram_INTERNAL(programBinary);
			}
			catch (std::runtime_error runtimeEx)
			{
				std::cerr << "Error: " << runtimeEx.what() << std::endl;
			}
		}

		/// <summary>
		/// Called after startup to cause the primary thread to wait for all spawned processes to finish their execution
		/// </summary>
		void WaitForProcess()
		{
			for (auto& thread : m_processThreads)
			{
				if (thread.joinable())
					thread.join();
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
			for (ProcessType* process : m_processes)
			{
				process->Stop();
			}

			//Deallocate the memory that was retrieved to load the program binary
			if(m_programSegment)
				DeallocateArray<uint8_t>(m_memoryManager->m_systemAllocator, m_programSegment);

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
			//Lock the Machine for a write
			std::unique_lock<std::shared_mutex> writeLock(_sharedMutex);

			try
			{
				LoadProgram(programBinary);
			}
			//invalid_argument: could not find file at path given
			catch (const std::invalid_argument& invalidArgEx)
			{
				std::cerr << "Error: " << invalidArgEx.what() << std::endl;
				return;
			}
			//Program too big to load into VM
			catch (const stack_overflow& overflowEx)
			{
				std::cerr << "Error: Could not load program into VM, not enough memory in system" << std::endl;
				return;
			}
			//Could not deturmine program size, memory allocation failed, or could not load program into memory
			catch (const std::runtime_error& loadEx)
			{
				std::cerr << "Error: " << loadEx.what() << std::endl;
				return;
			}

			//Get the offset to the initial PC from the first 4 bytes in program
			//!!REMEMBER ITS IN LITTLE-ENDIAN!!!:(
			int32_t offset = static_cast<int32_t>(m_programSegment[0]);
			/*offset |= static_cast<int32_t>(m_programSegment[1]) << 8;
			offset |= static_cast<int32_t>(m_programSegment[2]) << 16;
			offset |= static_cast<int32_t>(m_programSegment[3]) << 24;*/

			if (offset < 0 || offset >= m_programSize)
				throw std::runtime_error("Offset to initial PC at begining of program is invalid. Offset is to byte " + std::to_string(offset) + ". Program size is " + std::to_string(m_programSize) + " bytes.");

			m_codeSegment = static_cast<uint8_t*>(m_programSegment) + offset;

			SpawnProcess(m_codeSegment);
		}
	};
}
#endif //!MACHINE_H
