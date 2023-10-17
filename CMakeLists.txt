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

#Add the AssemblerFramework subdirectory
add_subdirectory(ASMFramework)

#VM_4380 target section
################################################################################################################################################################

#set source for VM_4380 executable
set(VM_4380_SOURCE
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/ISA_4380.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/Process_4380.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/VM4380.cpp
)

set(VM_4380_INSTRUCTIONS
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/Instructions/ADD.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/Instructions/DIV.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/Instructions/JMP_L.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/Instructions/LDB_L.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/Instructions/LDR_L.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/Instructions/MOV.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/Instructions/MUL.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/Instructions/SUB.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/Instructions/TRP.cpp
)

# Create executable for the virtual machine target of the project
add_executable (VM_4380 ${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/VM_4380_main.cpp ${VM_4380_SOURCE} ${VM_4380_INSTRUCTIONS})
target_link_libraries(VM_4380 PRIVATE VMFramework)

target_include_directories(VM_4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/include)
target_include_directories(VM_4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/include/Instructions)

################################################################################################################################################################

#ASM_4380 target section (Assembler_4380)
################################################################################################################################################################

#set source for ASM_4380 executable
set(ASM_4380_SOURCE
	
)

set(ASM_4380_DIRECTIVES

)

set(ASM_4380_INSTRUCTIONS
	
)

# Create executable for the Assembler target of the project
add_executable (ASM_4380 ${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/ASM_4380_main.cpp ${ASM_4380_SOURCE} ${ASM_4380_DIRECTIVES} ${ASM_4380_INSTRUCTIONS})
target_link_libraries(ASM_4380 PRIVATE ASMFramework)

target_include_directories(ASM_4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/include)
target_include_directories(ASM_4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/include/Directives)
target_include_directories(ASM_4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/include/Instructions)

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
set(VM_FRAMEWORK_UNIT_TESTS
	${CMAKE_CURRENT_SOURCE_DIR}/VMFramework/VMFramework_UnitTests/MemoryManagerTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VMFramework/VMFramework_UnitTests/PointerMathTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VMFramework/VMFramework_UnitTests/StackAllocatorTests.cpp
)

set(VM_4380_UNIT_TESTS
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/VM_4380_UnitTests/InstructionsTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/VM_4380_UnitTests/ISA_4380Tests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/VM_4380_UnitTests/Process_4380Tests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/VM_4380_UnitTests/VM4380Tests.cpp
)

set(ASM_FRAMEWORK_UNIT_TESTS
	${CMAKE_CURRENT_SOURCE_DIR}/ASMFramework/ASMFramework_UnitTests/SingletonWrapperTests.cpp
)

set(ASM_4380_UNIT_TESTS

)

#Create executable for the execution of the project's tests
add_executable(runTests ${VM_FRAMEWORK_UNIT_TESTS} ${VM_4380_UNIT_TESTS} 
${VM_4380_SOURCE} ${VM_4380_INSTRUCTIONS} 
${ASM_FRAMEWORK_UNIT_TESTS} ${ASM_4380_UNIT_TESTS} 
${ASM_4380_SOURCE} ${ASM_4380_DIRECTIVES} ${ASM_4380_INSTRUCTIONS})

#include the gtest_main function from the gtest library to automatically run all tests from its provided main
target_link_libraries(runTests PRIVATE GTest::gtest_main)

#include the VMFramework library
target_link_libraries(runTests PRIVATE VMFramework)

#include the AssemblerFramework library
target_link_libraries(runTests PRIVATE ASMFramework)

include(GoogleTest)
gtest_discover_tests(runTests)
################################################################################################################################################################