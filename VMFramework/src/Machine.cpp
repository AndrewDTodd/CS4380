#include "../include/Machine.h"

namespace VMFramework
{
	template <typename Derived, typename GPRegisterType, typename RegisterType, typename ProcessType, typename ISA>
	Machine<Derived, GPRegisterType, RegisterType, ProcessType, ISA>* Machine<Derived, GPRegisterType, RegisterType, ProcessType, ISA>::s_instance = nullptr;
}