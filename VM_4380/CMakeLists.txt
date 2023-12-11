# CMakeList.txt : CMakeLists for VM4380, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.20)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

#add _DEBUG macro based on build type for code that should compile differently in Debug vs Release
if(CMAKE_BUILD_TYPE MATCHES "Debug")
	add_definitions(-D_DEBUG)
endif()

#Google tests require mimimum c++ version 14
#setting minimum c++ version to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#VM_4380 target section
################################################################################################################################################################

#set source for VM_4380 executable
set(VM_4380_SOURCE
	${CMAKE_CURRENT_SOURCE_DIR}/src/ISA_4380.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Process_4380.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/VM4380.cpp

)

set(VM_4380_INSTRUCTIONS_ARTH
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Arth/ADD.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Arth/ADDI.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Arth/DIV.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Arth/DIVI.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Arth/MUL.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Arth/MULI.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Arth/SUB.cpp

)

set(VM_4380_INSTRUCTIONS_COMP
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Comp/CMP.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Comp/CMPI.cpp

)

set(VM_4380_INSTRUCTIONS_HEAP
	

)

set(VM_4380_INSTRUCTIONS_JUMP
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Jump/BGT.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Jump/BLT.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Jump/BNZ.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Jump/BRZ.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Jump/JMP_L.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Jump/JMR.cpp

)

set(VM_4380_INSTRUCTIONS_LOGICAL
	

)

set(VM_4380_INSTRUCTIONS_MOVE
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Move/LDA.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Move/LDB_L.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Move/LDB_R.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Move/LDR_L.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Move/LDR_R.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Move/MOV.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Move/MOVI.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Move/STB_L.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Move/STB_R.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Move/STR_L.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Move/STR_R.cpp

)

set(VM_4380_INSTRUCTIONS_MULTI_THREAD

)

set(VM_4380_INSTRUCTIONS_TRP
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/TRP/TRP.cpp

)

# Create executable for the virtual machine target of the project
add_executable (VM4380 ${CMAKE_CURRENT_SOURCE_DIR}/VM_4380_main.cpp 
${VM_4380_SOURCE} 
${VM_4380_INSTRUCTIONS_ARTH} 
${VM_4380_INSTRUCTIONS_COMP} 
${VM_4380_INSTRUCTIONS_HEAP} 
${VM_4380_INSTRUCTIONS_JUMP} 
${VM_4380_INSTRUCTIONS_LOGICAL} 
${VM_4380_INSTRUCTIONS_MOVE} 
${VM_4380_INSTRUCTIONS_MULTI_THREAD} 
${VM_4380_INSTRUCTIONS_TRP})

#Signify that the VM_4380 executable depends upon the VMFramework library
add_dependencies(VM4380 VMFramework)

#include the VMFramework library
target_link_libraries(VM4380 PRIVATE VMFramework)

target_include_directories(VM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(VM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Instructions)
target_include_directories(VM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Instructions/Arth)
target_include_directories(VM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Instructions/Comp)
target_include_directories(VM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Instructions/Heap)
target_include_directories(VM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Instructions/Jump)
target_include_directories(VM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Instructions/Logical)
target_include_directories(VM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Instructions/Move)
target_include_directories(VM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Instructions/Multi_Thread)
target_include_directories(VM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Instructions/TRP)

install(TARGETS VM4380 DESTINATION VM4380)

################################################################################################################################################################

#VM_4380Tests target section
################################################################################################################################################################
#installation and setup of the gTest suite
#build a tests executable for the execution of the projects tests
include(FetchContent)
FetchContent_Declare(
	googletest
	DOWNLOAD_EXTRACT_TIMESTAMP true
	URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#new format for including googletest subdirectory. To prevent googletest items being added to install
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
	FetchContent_Populate(googletest)
	add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

enable_testing()

#set source for "VM_4380Tests" unit testing executable
set(VM_4380_UNIT_TESTS
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380_UnitTests/InstructionsTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380_UnitTests/ISA_4380Tests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380_UnitTests/Process_4380Tests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380_UnitTests/VM4380Tests.cpp
)

#Create executable for the execution of the project's tests
add_executable(VM4380_Tests ${VM_4380_UNIT_TESTS} 
${VM_4380_SOURCE} 
${VM_4380_INSTRUCTIONS_ARTH} 
${VM_4380_INSTRUCTIONS_COMP} 
${VM_4380_INSTRUCTIONS_HEAP} 
${VM_4380_INSTRUCTIONS_JUMP} 
${VM_4380_INSTRUCTIONS_LOGICAL} 
${VM_4380_INSTRUCTIONS_MOVE} 
${VM_4380_INSTRUCTIONS_MULTI_THREAD} 
${VM_4380_INSTRUCTIONS_TRP})

#Signify that the VM_4380Tests executable depends upon the VMFramework library
add_dependencies(VM4380_Tests VMFramework)

#include the gtest_main function from the gtest library to automatically run all tests from its provided main
target_link_libraries(VM4380_Tests PRIVATE GTest::gtest_main)

#include the VMFramework library
target_link_libraries(VM4380_Tests PRIVATE VMFramework)

target_include_directories(VM4380_Tests PRIVATE ${googletest_SOURCE_DIR}/googletest/include)
target_include_directories(VM4380 PRIVATE ${googletest_SOURCE_DIR}/googletest/include)


include(GoogleTest)
gtest_discover_tests(VM4380_Tests)
################################################################################################################################################################