# CMakeList.txt : CMakeLists for AssemblerFramework, include source and define
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
	${CMAKE_CURRENT_SOURCE_DIR}/src/Assembler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ASMDirective.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ASMInstruction.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/LanguageDefinition.cpp
	
)

add_library(ASMFramework STATIC ${SOURCE_FILES})
#include the header files in the include directory
target_include_directories(ASMFramework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

#ASMFrameworkTests target section
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

#set source for "ASMFrameworkTests" unit testing executable
set(ASM_FRAMEWORK_UNIT_TESTS
	${CMAKE_CURRENT_SOURCE_DIR}/ASMFramework_UnitTests/SingletonWrapperTests.cpp
)

#Create executable for the execution of the project's tests
add_executable(ASMFrameworkTests ${ASM_FRAMEWORK_UNIT_TESTS})

#include the gtest_main function from the gtest library to automatically run all tests from its provided main
target_link_libraries(ASMFrameworkTests PRIVATE GTest::gtest_main)

#include the AssemblerFramework library
target_link_libraries(ASMFrameworkTests PRIVATE ASMFramework)

include(GoogleTest)
gtest_discover_tests(ASMFrameworkTests)
################################################################################################################################################################