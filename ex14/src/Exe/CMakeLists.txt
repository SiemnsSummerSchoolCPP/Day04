# Constants
Set(ProjName "Exe")
Set(FileExtensions "*.h" "*.c" "*.cpp" "*.hpp" "*.cc")
Set(CMAKE_CXX_STANDARD 17)
Set(CMAKE_BUILD_TYPE Debug)

# General
Cmake_Minimum_Required(VERSION 3.10)
Project(${ProjName})

# Include all files with extensions
File(GLOB files "./" ${FileExtensions})
Add_Executable(${ProjName} ${files})

# Libs
target_link_libraries(${ProjName} "MinstToolsLib" "BMPToolsLib")

Set_Target_Properties(${ProjName}
	PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY	"${CMAKE_SOURCE_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY	"${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY	"${CMAKE_SOURCE_DIR}/bin"
    EXECUTABLE_OUTPUT_PATH		"${CMAKE_SOURCE_DIR}/bin"
)

target_include_directories(
	${ProjName} PRIVATE
	"${CMAKE_SOURCE_DIR}/includes/")

# Flags
# String(CONCAT Flags ${Flags} " " "-g")
# String(CONCAT Flags ${Flags} " " "-Wall")
# String(CONCAT Flags ${Flags} " " "-Wextra")
# String(CONCAT Flags ${Flags} " " "-Werror")
# String(CONCAT Flags ${Flags} " " "-Waddress")
# String(CONCAT Flags ${Flags} " " "-Waggregate-return")
Set(CMAKE_CXX_FLAGS "${Flags}")