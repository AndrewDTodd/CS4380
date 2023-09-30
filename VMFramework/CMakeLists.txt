# CMakeList.txt : CMake project for VMFramework, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.14)

#add _DEBUG macro based on build type for code that should compile differently in Debug vs Release
if(CMAKE_BUILD_TYPE MATCHES "Debug")
	add_definitions(-D_DEBUG)
endif()

#Google tests require mimimum c++ version 14
#setting minimum c++ version to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(VMFramework STATIC "Machine.cpp" "Machine.h" "Process.h" "Process.cpp" "MemoryManager.h" "MemoryManager.cpp" "Allocator.h" "Allocator.cpp" "StackAllocator.h" "StackAllocator.cpp" "PointerMath.h" "PointerMath.cpp" "ISA.h" "ISA.cpp" "Instruction.h" "Instruction.cpp")