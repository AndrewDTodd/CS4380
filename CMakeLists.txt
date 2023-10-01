# CMakeList.txt : CMake project for Project1_VM, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.14)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

#add _DEBUG macro based on build type for code that should compile differently in Debug vs Release
if(CMAKE_BUILD_TYPE MATCHES "Debug")
	add_definitions(-D_DEBUG)
endif()

#setting project scope
project ("Project1_VM")

#Google tests require mimimum c++ version 14
#setting minimum c++ version to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Add the VMFramework subdirectory
add_subdirectory(VMFramework)

#VM_4380 target section
################################################################################################################################################################
# Create executable for the execution of the project
add_executable (VM_4380 main.cpp)
target_link_libraries(VM_4380 PRIVATE VMFramework)

################################################################################################################################################################

#runTests target section
################################################################################################################################################################
#installation and setup of the gTest suite
#build a tests executable for the execution of the projects tests
include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

#set source for "runTests" unit testing executable
set(UNIT_TESTS
	
	${CMAKE_CURRENT_SOURCE_DIR}/VMFramework/VMFramework_UnitTests/InstructionTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VMFramework/VMFramework_UnitTests/ISATests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VMFramework/VMFramework_UnitTests/MachineTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VMFramework/VMFramework_UnitTests/MemoryManagerTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VMFramework/VMFramework_UnitTests/PointerMathTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VMFramework/VMFramework_UnitTests/ProcessTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VMFramework/VMFramework_UnitTests/StackAllocatorTests.cpp
)

#Create executable for the execution of the project's tests
add_executable(runTests ${UNIT_TESTS})

#include the gtest_main function from the gtest library to automatically run all tests from its provided main
target_link_libraries(runTests PRIVATE GTest::gtest_main)

#include the VMFramework library
target_link_libraries(runTests PRIVATE VMFramework)

include(GoogleTest)
gtest_discover_tests(runTests)
################################################################################################################################################################