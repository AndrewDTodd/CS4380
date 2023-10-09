#ifndef SINGLETON_WRAPPER_H
#define SINGLETON_WRAPPER_H

#include <concepts>

#include <shared_mutex>
#include <mutex>

#include <memory>

template<class T>
class SingletonWrapper;

namespace ASMFramework
{
	template<class Derived>
	requires std::derived_from<Derived, SingletonWrapper<Derived>>
	class SingletonWrapper
	{
	protected:
		static std::shared_ptr<Derived> s_instance;

		static std::shared_mutex _sharedMutex;

	public:
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
					s_instance = new Derived();
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
