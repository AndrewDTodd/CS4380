#include "../include/SingletonWrapper.h"

#include <concepts>

#include <shared_mutex>

#include <memory>

namespace ASMFramework
{
	template<class Derived>
	requires std::derived_from<Derived, SingletonWrapper<Derived>>
	std::shared_ptr<Derived> SingletonWrapper<Derived>::s_instance = nullptr;

	template<class Derived>
	requires std::derived_from<Derived, SingletonWrapper<Derived>>
	std::shared_mutex SingletonWrapper<Derived>::_sharedMutex;
}