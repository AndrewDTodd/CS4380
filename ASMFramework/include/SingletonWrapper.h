#ifndef SINGLETON_WRAPPER_H
#define SINGLETON_WRAPPER_H

#include <concepts>

#include <shared_mutex>
#include <mutex>

#include <memory>

namespace ASMFramework
{
	template<class Derived>
	class SingletonWrapper
	{
	protected:
		inline static std::shared_ptr<Derived> s_instance;

		inline static std::shared_mutex _sharedMutex;

		/// <summary>
		/// Default constructor is private, SingletonWrapper is a singleton. Internal use only
		/// </summary>
		SingletonWrapper()
		{}

		/// <summary>
		/// Default destructor is private, SingletonWrapper is a singleton. Internal use only
		/// </summary>
		~SingletonWrapper()
		{}

	public:
		/// <summary>
		/// Get an instance of a shared_ptr to the singleton's instance
		/// </summary>
		/// <returns>shared_ptr to instance</returns>
		static std::shared_ptr<Derived> GetInstance()
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
					s_instance = std::make_shared<Derived>();
					return s_instance;
				}
			}
			return s_instance;
		}

		SingletonWrapper(const SingletonWrapper&) = delete;
		SingletonWrapper& operator=(const SingletonWrapper&) = delete;
		SingletonWrapper(SingletonWrapper&&) = delete;
		SingletonWrapper& operator=(SingletonWrapper&&) = delete;
	};
}
#endif // !SINGLETON_WRAPPER_H
