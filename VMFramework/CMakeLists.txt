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

set(SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/src/Allocator.cpp
	
	${CMAKE_CURRENT_SOURCE_DIR}/src/MemoryManager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/StackAllocator.cpp
)

add_library(VMFramework STATIC ${SOURCE_FILES})
#include the header files in the include directory
target_include_directories(VMFramework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)