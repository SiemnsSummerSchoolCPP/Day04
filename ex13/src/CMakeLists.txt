# Constants
Set(ProjName "Ex11_Src")
Set(FileExtensions "*.h" "*.c" "*.cpp" "*.hpp" "*.cc")
Set(CMAKE_CXX_STANDARD 11)
Set(CMAKE_BUILD_TYPE Debug)

# General
Cmake_Minimum_Required(VERSION 3.10)
Project(${ProjName})

# Include all files with extensions
File(GLOB files "./" ${FileExtensions})
Add_Executable(${ProjName} ${files})

Set_Target_Properties(${ProjName}
	PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY	"${CMAKE_SOURCE_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY	"${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY	"${CMAKE_SOURCE_DIR}/bin"
    EXECUTABLE_OUTPUT_PATH		"${CMAKE_SOURCE_DIR}/bin"
)

# Flags
Set(CMAKE_CXX_FLAGS "-g")
Set(CMAKE_CXX_FLAGS "-Wall")
Set(CMAKE_CXX_FLAGS "-Wextra")
Set(CMAKE_CXX_FLAGS "-Werror")
Set(CMAKE_CXX_FLAGS "-w")
Set(CMAKE_CXX_FLAGS "-Waddress")
Set(CMAKE_CXX_FLAGS "-Waggregate-return")
