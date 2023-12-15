#ifndef MACHINE_H
#define MACHINE_H

#include <iostream>
#include <string>

#include <concepts>
#include <type_traits>

#include <new>
#include <thread>
#include <shared_mutex>
//#include <mutex>
#include <stdexcept>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

#include "MemoryManager.h"
#include "Process.h"
#include "ISA.h"

#include "rootConfig.h"

namespace VMFramework
{
	class segmentation_fault : public std::exception
	{
	private:
		const std::string _msg;
	public:
		explicit segmentation_fault(std::string&& message) : _msg(message)
		{}

		const char* what() const noexcept override
		{
			return _msg.c_str();
		}
	};

	template<typename Derived, typename RegisterType, typename ProcessType, typename ISA>
	requires std::derived_from<ProcessType, VMFramework::Process<ProcessType, RegisterType, ISA>> && std::derived_from<ISA, VMFramework::ISA<RegisterType, ProcessType>>
	class Machine
	{
		//friend class Instruction<RegisterType, ProcessType>;
	protected:
		using MachineType = Machine<Derived, RegisterType, ProcessType, ISA>;

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
		MemoryManager<RegisterType>* m_memoryManager = nullptr;

		ISA m_ISA;

		/// <summary>
		/// List of the processes/threads executing in the machine
		/// </summary>
		std::vector<ProcessType*> m_processes = std::vector<ProcessType*>();
		std::vector<std::thread> m_processThreads = std::vector<std::thread>();

		/// <summary>
		/// Pointer to the begining (first byte) of the program's data in memory
		/// </summary>
		const uint8_t* m_programSegment = nullptr;

		/// <summary>
		/// Pointer to the start of the code segment
		/// </summary>
		const uint8_t* m_codeSegment = nullptr;

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
		virtual void LoadProgram(const std::filesystem::path& binPath)
		{
			if (!std::filesystem::exists(binPath))
			{
				throw std::invalid_argument("No file at path provided: " + binPath.string());
			}

			if (binPath.extension() != ".bin")
			{
				YELLOW_TERMINAL
					std::cerr << "**Warning** >> The extension for the provided file is " << binPath.extension() << ", expected .bin. Is this a valid program?" << std::endl;
					std::cout << std::endl;
				RESET_TERMINAL
			}

			std::ifstream file(binPath.string(), std::ios::binary | std::ios::ate);

			if (!file.is_open())
			{
				throw std::invalid_argument("Unable to open file at path: " + binPath.string());
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
			
			m_programSegment = static_cast<uint8_t*>(m_memoryManager->AllocateUserPagesFor(m_programSize));

			if (!m_programSegment)
			{
				// Allocation failed
				file.close();
				throw std::runtime_error("Memory allocation failed");
			}

			// Read file into m_programSegment byte array
			file.seekg(0, std::ios::beg); // Move file cursor to the beginning
			if (!file.read(reinterpret_cast<char*>(const_cast<uint8_t*>(m_programSegment)), m_programSize))
			{
				// Read failed
				file.close();
				throw std::runtime_error("Failed to read program into memory");
			}

			file.close();
		}

		/// <summary>
		/// Used to deturmine the initial PC for the first process spawned by the machine when launching a program. 
		/// Logic for how to do this is dependent of architecture and therefore must be implemented by realizing class
		/// </summary>
		/// <returns>Pouinter to the byte in the program segment to start execution at</returns>
		virtual const void* CalculatePrimaryThreadInitPC() = 0;

		/// <summary>
		/// Will attempt to load the binary at the specified path and run the program. Used by StartUp(char*) to launch program
		/// </summary>
		/// <param name="programBinary">Path to a valid program binary to run</param>
		/// <exception cref="rumtime_error Thrown if initial PC specified in loaded binary is invalid"/>
		virtual inline void LaunchProgram_INTERNAL(const std::filesystem::path& binPath)
		{
			//Lock has already been obtained by the calling StartUp(char*) method
			BLUE_TERMINAL
				std::cout << "Executing program at >> " << binPath.string() << std::endl;
			RESET_TERMINAL

			try
			{
				LoadProgram(binPath);
			}
			//invalid_argument: could not find file at path given
			catch (const std::invalid_argument& invalidArgEx)
			{
				RED_TERMINAL
					std::cerr << "Error: " << invalidArgEx.what() << std::endl;
				RESET_TERMINAL
				return;
			}
			//Program too big to load into VM
			catch (const stack_overflow& overflowEx)
			{
				RED_TERMINAL
					std::cerr << "Error: Could not load program into VM, not enough memory in system" << std::endl;
				RESET_TERMINAL
				return;
			}
			//Could not deturmine program size, memory allocation failed, or could not load program into memory
			catch (const std::runtime_error& loadEx)
			{
				RED_TERMINAL
					std::cerr << "Error: " << loadEx.what() << std::endl;
				RESET_TERMINAL
				return;
			}
			//This probably means the LaunchProgram method was called before VM initialization
			catch (const std::exception& ex)
			{
				RED_TERMINAL
					std::cerr << "Error: " << ex.what() << std::endl;
				RESET_TERMINAL
				return;
			}

			const void* offset = CalculatePrimaryThreadInitPC();
			m_codeSegment = static_cast<const uint8_t*>(offset);

			SpawnProcess(offset);
		}

		/// <summary>
		/// Create a new process to execute starting at the specified program location
		/// </summary>
		/// <param name="initialPC">Pointer to the location in the program where this process should begin execution</param>
		virtual void SpawnProcess(const void* initialPC) = 0;

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
		void StartUp(const size_t& systemBytes, MemoryMap<RegisterType>& memoryMap)
		{
			//Lock the Machine for a write
			std::unique_lock<std::shared_mutex> writeLock(_sharedMutex);
#ifdef _DEBUG
			if (this->m_memoryManager)
				throw std::runtime_error("Calling StartUp on an already active VM is invalid");
#endif // _DEBUG

			//Aquire pointer to MemoryManager instance and initialize the subsystem
			this->m_memoryManager = MemoryManager<RegisterType>::GetInstance();
			this->m_memoryManager->StartUp(systemBytes, memoryMap);
		}

		/// <summary>
		/// Will launch the machine and initialize the system then attempt to launch a program from the specified binaries path
		/// </summary>
		/// <param name="programBinary">Path to a valid program binary to run</param>
		void StartUp(const size_t& systemBytes, MemoryMap<RegisterType>& memoryMap, const char* programBinary)
		{
			//Lock the Machine for a write
			std::unique_lock<std::shared_mutex> writeLock(_sharedMutex);
#ifdef _DEBUG
			if (this->m_memoryManager)
				throw std::runtime_error("Calling StartUp on an already active VM is invalid");
#endif // _DEBUG


			//Aquire pointer to MemoryManager instance and initialize the subsystem
			this->m_memoryManager = MemoryManager<RegisterType>::GetInstance();
			this->m_memoryManager->StartUp(systemBytes, memoryMap);

			std::filesystem::path filePath(programBinary);

			//lauch the provided program
			try
			{
				LaunchProgram_INTERNAL(programBinary);
			}
			catch (std::runtime_error runtimeEx)
			{
				RED_TERMINAL
					std::cerr << "Error: " << runtimeEx.what() << std::endl;
				RESET_TERMINAL
			}
		}

		/// <summary>
		/// Will launch the machine and initialize the system then attempt to launch a program from the specified binaries path
		/// </summary>
		/// <param name="programBinary">Path to a valid program binary to run</param>
		void StartUp(const size_t& systemBytes, MemoryMap<RegisterType>& memoryMap, const std::filesystem::path& programBinary)
		{
			//Lock the Machine for a write
			std::unique_lock<std::shared_mutex> writeLock(_sharedMutex);
#ifdef _DEBUG
			if (this->m_memoryManager)
				throw std::runtime_error("Calling StartUp on an already active VM is invalid");
#endif // _DEBUG


			//Aquire pointer to MemoryManager instance and initialize the subsystem
			this->m_memoryManager = MemoryManager<RegisterType>::GetInstance();
			this->m_memoryManager->StartUp(systemBytes, memoryMap);

			//lauch the provided program
			try
			{
				LaunchProgram_INTERNAL(programBinary);
			}
			catch (std::runtime_error runtimeEx)
			{
				RED_TERMINAL
					std::cerr << "Error: " << runtimeEx.what() << std::endl;
				RESET_TERMINAL
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

#ifdef _DEBUG
			if (!this->m_memoryManager)
				throw std::runtime_error("Calling ShutDown on an inactive (uninitialized) VM is invalid");
#endif // _DEBUG


			//Shut down the running processes
			for (ProcessType* process : m_processes)
			{
				process->Stop();
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
		virtual void LaunchProgram(const char* programBinary)
		{
			//Lock the Machine for a write
			std::unique_lock<std::shared_mutex> writeLock(_sharedMutex);

			std::filesystem::path filePath(programBinary);

			BLUE_TERMINAL
				std::cout << "Executing program at >> " << filePath.string() << std::endl;
			RESET_TERMINAL

			try
			{
				LoadProgram(programBinary);
			}
			//invalid_argument: could not find file at path given
			catch (const std::invalid_argument& invalidArgEx)
			{
				RED_TERMINAL
					std::cerr << "Error: " << invalidArgEx.what() << std::endl;
				RESET_TERMINAL
				return;
			}
			//Program too big to load into VM
			catch (const stack_overflow& overflowEx)
			{
				RED_TERMINAL
					std::cerr << "Error: Could not load program into VM, not enough memory in system" << std::endl;
				RESET_TERMINAL
				return;
			}
			//Could not deturmine program size, memory allocation failed, or could not load program into memory
			catch (const std::runtime_error& loadEx)
			{
				RED_TERMINAL
					std::cerr << "Error: " << loadEx.what() << std::endl;
				RESET_TERMINAL
				return;
			}
			//This probably means the LaunchProgram method was called before VM initialization
			catch (const std::exception& ex)
			{
				RED_TERMINAL
					std::cerr << "Error: " << ex.what() << std::endl;
				RESET_TERMINAL
				return;
			}

			const void* offset = CalculatePrimaryThreadInitPC();
			m_codeSegment = static_cast<const uint8_t*>(offset);

			SpawnProcess(offset);
		}

		/// <summary>
		/// Will attempt to load the binary at the specified path and run the program
		/// </summary>
		/// <param name="programBinary">Path to a valid program binary to run</param>
		/// <exeption cref="rumtime_error">Thrown if initial PC specified in loaded binary is invalid</exeption>
		virtual void LaunchProgram(const std::filesystem::path& programBinary)
		{
			//Lock the Machine for a write
			std::unique_lock<std::shared_mutex> writeLock(_sharedMutex);

			BLUE_TERMINAL
				std::cout << "Executing program at >> " << programBinary.string() << std::endl;
			RESET_TERMINAL

			try
			{
				LoadProgram(programBinary);
			}
			//invalid_argument: could not find file at path given
			catch (const std::invalid_argument& invalidArgEx)
			{
				RED_TERMINAL
					std::cerr << "Error: " << invalidArgEx.what() << std::endl;
				RESET_TERMINAL
					return;
			}
			//Program too big to load into VM
			catch (const stack_overflow& overflowEx)
			{
				RED_TERMINAL
					std::cerr << "Error: Could not load program into VM, not enough memory in system" << std::endl;
				RESET_TERMINAL
					return;
			}
			//Could not deturmine program size, memory allocation failed, or could not load program into memory
			catch (const std::runtime_error& loadEx)
			{
				RED_TERMINAL
					std::cerr << "Error: " << loadEx.what() << std::endl;
				RESET_TERMINAL
					return;
			}
			//This probably means the LaunchProgram method was called before VM initialization
			catch (const std::exception& ex)
			{
				RED_TERMINAL
					std::cerr << "Error: " << ex.what() << std::endl;
				RESET_TERMINAL
					return;
			}

			const void* offset = CalculatePrimaryThreadInitPC();
			m_codeSegment = static_cast<const uint8_t*>(offset);

			SpawnProcess(offset);
		}

		Machine(const Machine&) = delete;
		Machine& operator=(const Machine&) = delete;
		Machine(Machine&&) = delete;
		Machine& operator=(Machine&&) = delete;
	};
}
#endif //!MACHINE_H
