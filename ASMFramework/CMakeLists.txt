# CMakeList.txt : CMakeLists for AssemblerFramework, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.20)

#add _DEBUG macro based on build type for code that should compile differently in Debug vs Release
if(CMAKE_BUILD_TYPE MATCHES "Debug")
	add_definitions(-D_DEBUG)
endif()

#Google tests require mimimum c++ version 14
#setting minimum c++ version to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#A significant release that likely includes new features, changes, and enhancements that may not be backward compatible with the previous version
set(VERSION_MAJOR 2)
#A release that may add new features but remains backward compatible with the previous version
set(VERSION_MINOR 1)
#A release that includes minor changes, bug fixes, and patches without adding new features. It is typically backward and forward compatible with the corresponding minor version
set(VERSION_PATCH 1)
#A version that is often used to denote a specific build of the software, including revisions, builds, or other metadata
set(VERSION_BUILD 0)

#Add versioning definitions for the ASM_4380 executable
add_definitions(-DVERSION_MAJOR=${VERSION_MAJOR})
add_definitions(-DVERSION_MINOR=${VERSION_MINOR})
add_definitions(-DVERSION_PATCH=${VERSION_PATCH})
add_definitions(-DVERSION_BUILD=${VERSION_BUILD})

set(SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/src/ASMDirective.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ASMFramework_GetVersion.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ASMInstruction.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Assembler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/LanguageDefinition.cpp
	
)

add_library(ASMFramework STATIC ${SOURCE_FILES})
#include the header files in the include directory
target_include_directories(ASMFramework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

#install the public header files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ 
DESTINATION ASMFramework/include 
FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")

#install the static library
install(TARGETS ASMFramework DESTINATION ASMFramework/lib)

#ASMFrameworkTests target section
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

target_include_directories(ASMFrameworkTests PRIVATE ${googletest_SOURCE_DIR}/googletest/include)

target_include_directories(ASMFramework PRIVATE ${googletest_SOURCE_DIR}/googletest/include)


include(GoogleTest)
gtest_discover_tests(ASMFrameworkTests)
################################################################################################################################################################