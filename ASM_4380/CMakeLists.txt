# CMakeList.txt : CMakeLists for ASM4380 executable, include source and define
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

#ASM_4380 target section (Assembler_4380)
################################################################################################################################################################

#set source for ASM_4380 executable
set(ASM_4380_SOURCE
	${CMAKE_CURRENT_SOURCE_DIR}/src/ASM4380.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/LanguageDefinition_4380.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/PassOne_Tokenization.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/PassTwo_Assemble.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/PassThree_Serialize.cpp

)

set(ASM_4380_DIRECTIVES
	${CMAKE_CURRENT_SOURCE_DIR}/src/Directives/BYT_DIR.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Directives/CSTR_DIR.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Directives/INT_DIR.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Directives/STR_DIR.cpp

)

set(ASM_4380_INSTRUCTIONS_ARTH
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Arth_INS/ADD_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Arth_INS/ADI_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Arth_INS/DIVI_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Arth_INS/DIV_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Arth_INS/MULI_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Arth_INS/MUL_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Arth_INS/SUB_INS.cpp

)

set(ASM_4380_INSTRUCTIONS_COMP
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Comp_INS/CMPI_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Comp_INS/CMP_INS.cpp

)

set(ASM_4380_INSTRUCTIONS_HEAP
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Heap_INS/ALCI_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Heap_INS/ALLC_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Heap_INS/FREE_INS.cpp

)

set(ASM_4380_INSTRUCTIONS_JUMP
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Jump_INS/BAL_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Jump_INS/BGT_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Jump_INS/BLT_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Jump_INS/BNZ_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Jump_INS/BRZ_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Jump_INS/JMP_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Jump_INS/JMR_INS.cpp

)

set(ASM_4380_INSTRUCTIONS_LOGICAL
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Logical_INS/AND_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Logical_INS/NOT_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Logical_INS/OR_INS.cpp

)

set(ASM_4380_INSTRUCTIONS_MOVE
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Move_INS/LDA_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Move_INS/LDB_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Move_INS/LDR_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Move_INS/MOVI_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Move_INS/MOV_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Move_INS/STB_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Move_INS/STR_INS.cpp

)

set(ASM_4380_INSTRUCTIONS_MULTI_THREAD
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Multi_Thread_INS/BLK_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Multi_Thread_INS/END_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Multi_Thread_INS/LCK_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Multi_Thread_INS/RUN_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Multi_Thread_INS/ULK_INS.cpp

)

set(ASM_4380_INSTRUCTIONS_STACK
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Stack_INS/PEEK_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Stack_INS/POP_INS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/Stack_INS/PUSH_INS.cpp

)

set(ASM_4380_INSTRUCTIONS_TRP
	${CMAKE_CURRENT_SOURCE_DIR}/src/Instructions/TRP_INS/TRP_INS.cpp

)

# Create executable for the Assembler target of the project
add_executable (ASM4380 ${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380_main.cpp 
${ASM_4380_SOURCE} 
${ASM_4380_DIRECTIVES} 
${ASM_4380_INSTRUCTIONS_ARTH} 
${ASM_4380_INSTRUCTIONS_COMP} 
${ASM_4380_INSTRUCTIONS_HEAP} 
${ASM_4380_INSTRUCTIONS_JUMP} 
${ASM_4380_INSTRUCTIONS_LOGICAL} 
${ASM_4380_INSTRUCTIONS_MOVE} 
${ASM_4380_INSTRUCTIONS_MULTI_THREAD} 
${ASM_4380_INSTRUCTIONS_STACK} 
${ASM_4380_INSTRUCTIONS_TRP})

#Signify that the ASM_4380 target depends upon the ASMFramework library target
add_dependencies(ASM4380 ASMFramework)

#Include the ASMFramework library
target_link_libraries(ASM4380 PRIVATE ASMFramework)

target_include_directories(ASM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(ASM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Directives)
target_include_directories(ASM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Instructions)
target_include_directories(ASM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Instructions/Arth_INS)
target_include_directories(ASM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Instructions/Comp_INS)
target_include_directories(ASM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Instructions/Heap_INS)
target_include_directories(ASM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Instructions/Jump_INS)
target_include_directories(ASM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Instructions/Logical_INS)
target_include_directories(ASM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Instructions/Move_INS)
target_include_directories(ASM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Instructions/Multi_Thread_INS)
target_include_directories(ASM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Instructions/Stack_INS)
target_include_directories(ASM4380 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Instructions/TRP_INS)

install(TARGETS ASM4380 DESTINATION ASM4380)

################################################################################################################################################################

#ASM_4380Tests target section
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

#set source for "runTests" unit testing executable
set(ASM_4380_UNIT_TESTS
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380_UnitTests/ASM4380Tests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380_UnitTests/DirectivesTesting.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380_UnitTests/InstructionsTesting.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380_UnitTests/PassOneTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380_UnitTests/PassTwoTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ASM_4380_UnitTests/PassThreeTests.cpp

)

#Create executable for the execution of the project's tests
add_executable(ASM4380_Tests ${ASM_4380_UNIT_TESTS} 
${ASM_4380_SOURCE} 
${ASM_4380_DIRECTIVES} 
${ASM_4380_INSTRUCTIONS_ARTH} 
${ASM_4380_INSTRUCTIONS_COMP} 
${ASM_4380_INSTRUCTIONS_HEAP} 
${ASM_4380_INSTRUCTIONS_JUMP} 
${ASM_4380_INSTRUCTIONS_LOGICAL} 
${ASM_4380_INSTRUCTIONS_MOVE} 
${ASM_4380_INSTRUCTIONS_MULTI_THREAD} 
${ASM_4380_INSTRUCTIONS_TRP})

#Signify that the ASM_4380Tests executable depends upon the ASMFramework library
add_dependencies(ASM4380_Tests ASMFramework)

#include the gtest_main function from the gtest library to automatically run all tests from its provided main
target_link_libraries(ASM4380_Tests PRIVATE GTest::gtest_main)

#include the AssemblerFramework library
target_link_libraries(ASM4380_Tests PRIVATE ASMFramework)

target_include_directories(ASM4380_Tests PRIVATE ${googletest_SOURCE_DIR}/googletest/include)

target_include_directories(ASM4380 PRIVATE ${googletest_SOURCE_DIR}/googletest/include)


include(GoogleTest)
gtest_discover_tests(ASM4380_Tests)
################################################################################################################################################################