# CMakeList.txt : CMake project for Project1_VM, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.20)

#setting project scope
project ("4380")

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

#A significant release that likely includes new features, changes, and enhancements that may not be backward compatible with the previous version
set(ASM4380_VERSION_MAJOR 1)
#A release that may add new features but remains backward compatible with the previous version
set(ASM4380_VERSION_MINOR 1)
#A release that includes minor changes, bug fixes, and patches without adding new features. It is typically backward and forward compatible with the corresponding minor version
set(ASM4380_VERSION_PATCH 0)
#A version that is often used to denote a specific build of the software, including revisions, builds, or other metadata
set(ASM4380_VERSION_BUILD 0)

#Add versioning definitions for the ASM_4380 executable
add_definitions(-DASM4380_VERSION_MAJOR=${ASM4380_VERSION_MAJOR})
add_definitions(-DASM4380_VERSION_MINOR=${ASM4380_VERSION_MINOR})
add_definitions(-DASM4380_VERSION_PATCH=${ASM4380_VERSION_PATCH})
add_definitions(-DASM4380_VERSION_BUILD=${ASM4380_VERSION_BUILD})

#A significant release that likely includes new features, changes, and enhancements that may not be backward compatible with the previous version
set(VM4380_VERSION_MAJOR 1)
#A release that may add new features but remains backward compatible with the previous version
set(VM4380_VERSION_MINOR 1)
#A release that includes minor changes, bug fixes, and patches without adding new features. It is typically backward and forward compatible with the corresponding minor version
set(VM4380_VERSION_PATCH 0)
#A version that is often used to denote a specific build of the software, including revisions, builds, or other metadata
set(VM4380_VERSION_BUILD 0)

#Add versioning definitions for the ASM_4380 executable
add_definitions(-DVM4380_VERSION_MAJOR=${VM4380_VERSION_MAJOR})
add_definitions(-DVM4380_VERSION_MINOR=${VM4380_VERSION_MINOR})
add_definitions(-DVM4380_VERSION_PATCH=${VM4380_VERSION_PATCH})
add_definitions(-DVM4380_VERSION_BUILD=${VM4380_VERSION_BUILD})

if(UNIX AND NOT APPLE)
	add_definitions(-DTARGET_OS="Linux")
	add_definitions(-D_LINUX_TARGET)
elseif(WIN32)
	add_definitions(-DTARGET_OS="Windows")
	add_definitions(-D_WIN_TARGET)
elseif(UNIX AND APPLE)
	add_definitions(-DTARGET_OS="MacOS")
	add_definitions(-D_MAC_TARGET)
else()
	add_definitions(-DTARGET_OS="Unkown")
endif()

if(UNIX)
    add_definitions(
        -DRESET="\\033[0m"
        -DRED="\\033[31m"
        -DGREEN="\\033[32m"
        -DYELLOW="\\033[33m"
        -DBLUE="\\033[34m"
		-DDIMB="\\033[2m"
		-DNORM_TXT="\\03[22m"
    )
endif()

configure_file(
	"${CMAKE_SOURCE_DIR}/rootConfig.h.in"
	"${CMAKE_SOURCE_DIR}/rootConfig.h"
)

include_directories(${CMAKE_SOURCE_DIR})

#this CMake variable is used by the VM_4380 unit test that needs a path to a test bin
set(VM_TEST_BIN_PATH "${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/VM_4380_UnitTests/TestBins/we.bin" CACHE STRING "VM_4380 Unit Test bin file path")

#this CMake variable is used by the Assembler unit test that needs a path to test exceptions handing
set(ASSEMBLER_TEST_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/ASM_4380_UnitTests/TestDocs/test.txt" CACHE STRING "Assember Unit Test file path")

add_definitions(-DBIN_PATH="${VM_TEST_BIN_PATH}")
add_definitions(-DTEST_TXT_PATH="${ASSEMBLER_TEST_PATH}")

#Add the VMFramework subdirectory
add_subdirectory(VMFramework)
#Add the VM_4380 subdirectory
add_subdirectory(VM_4380)

#Add the AssemblerFramework subdirectory
add_subdirectory(ASMFramework)
#Add the ASM_4380 subdirectory
add_subdirectory(ASM_4380)

#root reference to all targets source
################################################################################################################################################################

#ASMFramework Source
############################################################################
set(ASM_FRAMEWORK_SOURCE
	${CMAKE_CURRENT_SOURCE_DIR}/ASMFramework/src/Assembler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASMFramework/src/Directive.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASMFramework/src/Instruction.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASMFramework/src/LanguageDefinition.cpp
	
)
############################################################################

#ASM_4380 Source
############################################################################
set(ASM_4380_SOURCE
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/ASM4380.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/LanguageDefinition_4380.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/PassOne_Tokenization.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/PassTwo_Assemble.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/PassThree_Serialize.cpp

)

set(ASM_4380_DIRECTIVES
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Directives/BYT_DIR.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Directives/CSTR_DIR.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Directives/INT_DIR.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Directives/STR_DIR.cpp

)

set(ASM_4380_INSTRUCTIONS_ARTH
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Arth_INS/ADD_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Arth_INS/ADI_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Arth_INS/DIVI_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Arth_INS/DIV_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Arth_INS/MULI_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Arth_INS/MUL_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Arth_INS/SUB_INS.cpp

)

set(ASM_4380_INSTRUCTIONS_COMP
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Comp_INS/CMPI_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Comp_INS/CMP_INS.cpp

)

set(ASM_4380_INSTRUCTIONS_HEAP
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Heap_INS/ALCI_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Heap_INS/ALLC_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Heap_INS/FREE_INS.cpp

)

set(ASM_4380_INSTRUCTIONS_JUMP
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Jump_INS/BGT_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Jump_INS/BLT_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Jump_INS/BNZ_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Jump_INS/BRZ_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Jump_INS/JMP_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Jump_INS/JMR_INS.cpp

)

set(ASM_4380_INSTRUCTIONS_LOGICAL
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Logical_INS/AND_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Logical_INS/NOT_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Logical_INS/OR_INS.cpp

)

set(ASM_4380_INSTRUCTIONS_MOVE
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Move_INS/LDA_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Move_INS/LDB_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Move_INS/LDR_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Move_INS/MOVI_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Move_INS/MOV_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Move_INS/STB_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Move_INS/STR_INS.cpp

)

set(ASM_4380_INSTRUCTIONS_MULTI_THREAD
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Multi_Thread_INS/BLK_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Multi_Thread_INS/END_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Multi_Thread_INS/LCK_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Multi_Thread_INS/RUN_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/Multi_Thread_INS/ULK_INS.cpp

)

set(ASM_4380_INSTRUCTIONS_TRP
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/src/Instructions/TRP_INS/TRP_INS.cpp

)
############################################################################

#VMFramework Source
############################################################################
set(VM_FRAMEWORK_SOURCE
	${CMAKE_CURRENT_SOURCE_DIR}/VMFramework/src/Allocator.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VMFramework/src/MemoryManager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VMFramework/src/StackAllocator.cpp

)
############################################################################

#VM_4380 Source
############################################################################
set(VM_4380_SOURCE
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/ISA_4380.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/Process_4380.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/VM4380.cpp

)

set(VM_4380_INSTRUCTIONS_ARTH
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/Instructions/Arth/ADD.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/Instructions/Arth/DIV.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/Instructions/Arth/MUL.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/Instructions/Arth/SUB.cpp

)

set(VM_4380_INSTRUCTIONS_COMP
	

)

set(VM_4380_INSTRUCTIONS_HEAP
	

)

set(VM_4380_INSTRUCTIONS_JUMP
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/Instructions/Jump/JMP_L.cpp

)

set(VM_4380_INSTRUCTIONS_LOGICAL
	

)

set(VM_4380_INSTRUCTIONS_MOVE
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/Instructions/Move/LDB_L.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/Instructions/Move/LDR_L.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/Instructions/Move/MOV.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/Instructions/Move/STB_L.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/Instructions/Move/STR_L.cpp

)

set(VM_4380_INSTRUCTIONS_MULTI_THREAD

)

set(VM_4380_INSTRUCTIONS_TRP
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/src/Instructions/TRP/TRP.cpp

)
############################################################################

################################################################################################################################################################

#root reference to all targets unit test source
################################################################################################################################################################

#ASMFramework Unit Tests Source
############################################################################
set(ASM_FRAMEWORK_UNIT_TESTS
	${CMAKE_CURRENT_SOURCE_DIR}/ASMFramework/ASMFramework_UnitTests/SingletonWrapperTests.cpp

)
############################################################################

#ASM_4380 Unit Tests Source
############################################################################
set(ASM_4380_UNIT_TESTS
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/ASM_4380_UnitTests/ASM4380Tests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/ASM_4380_UnitTests/PassOneTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/ASM_4380_UnitTests/PassTwoTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/ASM_4380_UnitTests/PassThreeTests.cpp

)
############################################################################

#VMFramework Unit Tests Source
############################################################################
set(VM_FRAMEWORK_UNIT_TESTS
	${CMAKE_CURRENT_SOURCE_DIR}/VMFramework/VMFramework_UnitTests/MemoryManagerTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VMFramework/VMFramework_UnitTests/PointerMathTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VMFramework/VMFramework_UnitTests/StackAllocatorTests.cpp

)
############################################################################

#VM_4380 Unit Tests Source
############################################################################
set(VM_4380_UNIT_TESTS
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/VM_4380_UnitTests/InstructionsTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/VM_4380_UnitTests/ISA_4380Tests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/VM_4380_UnitTests/Process_4380Tests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/VM_4380_UnitTests/VM4380Tests.cpp
)
############################################################################

################################################################################################################################################################

#monoSystem target section
################################################################################################################################################################

# Create monoSystem executable for the joined VM and Assembler thing
add_executable (monoSystem ${CMAKE_CURRENT_SOURCE_DIR}/MonolithicMain.cpp 
${ASM_4380_SOURCE} 
${ASM_4380_DIRECTIVES} 
${ASM_4380_INSTRUCTIONS_ARTH} 
${ASM_4380_INSTRUCTIONS_COMP} 
${ASM_4380_INSTRUCTIONS_HEAP} 
${ASM_4380_INSTRUCTIONS_JUMP} 
${ASM_4380_INSTRUCTIONS_LOGICAL} 
${ASM_4380_INSTRUCTIONS_MOVE} 
${ASM_4380_INSTRUCTIONS_MULTI_THREAD} 
${ASM_4380_INSTRUCTIONS_TRP}

${VM_4380_SOURCE} 
${VM_4380_INSTRUCTIONS_ARTH} 
${VM_4380_INSTRUCTIONS_COMP} 
${VM_4380_INSTRUCTIONS_HEAP} 
${VM_4380_INSTRUCTIONS_JUMP} 
${VM_4380_INSTRUCTIONS_LOGICAL} 
${VM_4380_INSTRUCTIONS_MOVE} 
${VM_4380_INSTRUCTIONS_MULTI_THREAD} 
${VM_4380_INSTRUCTIONS_TRP})

#Signify that the ASM_4380 target depends upon the ASMFramework library target and VMFramework library target
add_dependencies(monoSystem ASMFramework VMFramework)

#Include the ASMFramework library
target_link_libraries(monoSystem PRIVATE ASMFramework VMFramework)

target_include_directories(monoSystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/include)
target_include_directories(monoSystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/include/Directives)
target_include_directories(monoSystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/include/Instructions)
target_include_directories(monoSystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/include/Instructions/Arth_INS)
target_include_directories(monoSystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/include/Instructions/Comp_INS)
target_include_directories(monoSystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/include/Instructions/Heap_INS)
target_include_directories(monoSystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/include/Instructions/Jump_INS)
target_include_directories(monoSystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/include/Instructions/Logical_INS)
target_include_directories(monoSystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/include/Instructions/Move_INS)
target_include_directories(monoSystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/include/Instructions/Multi_Thread_INS)
target_include_directories(monoSystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380/include/Instructions/TRP_INS)

target_include_directories(VM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/include)
target_include_directories(VM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/include/Instructions)
target_include_directories(VM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/include/Instructions/Arth)
target_include_directories(VM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/include/Instructions/Comp)
target_include_directories(VM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/include/Instructions/Heap)
target_include_directories(VM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/include/Instructions/Jump)
target_include_directories(VM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/include/Instructions/Logical)
target_include_directories(VM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/include/Instructions/Move)
target_include_directories(VM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/include/Instructions/Multi_Thread)
target_include_directories(VM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/VM_4380/include/Instructions/TRP)
################################################################################################################################################################

#runAllTargetTests target section
################################################################################################################################################################
#installation and setup of the gTest suite
#build a tests executable for the execution of the projects tests
include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
	DOWNLOAD_EXTRACT_TIMESTAMP true
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

#Create executable for the execution of the project's tests
add_executable(runAllTargetTests
${ASM_FRAMEWORK_UNIT_TESTS} 

${ASM_4380_UNIT_TESTS} 
${ASM_4380_SOURCE} 
${ASM_4380_DIRECTIVES} 
${ASM_4380_INSTRUCTIONS_ARTH} 
${ASM_4380_INSTRUCTIONS_COMP} 
${ASM_4380_INSTRUCTIONS_HEAP} 
${ASM_4380_INSTRUCTIONS_JUMP} 
${ASM_4380_INSTRUCTIONS_LOGICAL} 
${ASM_4380_INSTRUCTIONS_MOVE} 
${ASM_4380_INSTRUCTIONS_MULTI_THREAD} 
${ASM_4380_INSTRUCTIONS_TRP}

${VM_FRAMEWORK_UNIT_TESTS} 

${VM_4380_UNIT_TESTS} 
${VM_4380_SOURCE} 
${VM_4380_INSTRUCTIONS_ARTH} 
${VM_4380_INSTRUCTIONS_COMP} 
${VM_4380_INSTRUCTIONS_HEAP} 
${VM_4380_INSTRUCTIONS_JUMP} 
${VM_4380_INSTRUCTIONS_LOGICAL} 
${VM_4380_INSTRUCTIONS_MOVE} 
${VM_4380_INSTRUCTIONS_MULTI_THREAD} 
${VM_4380_INSTRUCTIONS_TRP}
)

add_dependencies(runAllTargetTests VMFramework ASMFramework VM4380 ASM4380)

#include the gtest_main function from the gtest library to automatically run all tests from its provided main
target_link_libraries(runAllTargetTests PRIVATE GTest::gtest_main)

#include the VMFramework library
target_link_libraries(runAllTargetTests PRIVATE VMFramework)

#include the AssemblerFramework library
target_link_libraries(runAllTargetTests PRIVATE ASMFramework)

include(GoogleTest)
gtest_discover_tests(runAllTargetTests)
################################################################################################################################################################