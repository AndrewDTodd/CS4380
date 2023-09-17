# CMakeList.txt : CMake project for Project0_BinaryConversion, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.14)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

#setting project scope
project ("Project0_BinaryConversion")

#Google tests require mimimum c++ version 14
#setting minimum c++ version to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable for the execution of the project
add_executable (B10ToB2 "main.cpp" "Project0_Converter.cpp" "Project0_Converter.h")

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

#Create executable for the execution of the project's tests
add_executable(runTests "tests.cpp" "Project0_Converter.cpp" "Project0_Converter.h")
#include the gtest_main function from the gtest library to automatically run all tests from its provided main
target_link_libraries(runTests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(runTests)