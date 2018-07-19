# Macros

# Get all dirs in start_dir.
FUNCTION(GET_DIRS start_dir return_list)
	APPEND_STR_TO_LIST("${start_dir}/*" "${FILE_EXTENSIONS}" rs)
    FILE(GLOB_RECURSE new_list ${rs})

    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        LIST(APPEND dir_list ${dir_path})
    ENDFOREACH()

    LIST(REMOVE_DUPLICATES dir_list)

    SET(${return_list} "${dir_list}"  PARENT_SCOPE)
ENDFUNCTION(GET_DIRS)

# Appends the given target_str to every item from target_list
# forming a return_list.
FUNCTION(APPEND_STR_TO_LIST target_str target_list return_list)
	SET(results "")

	FOREACH(str_loop ${target_list})
		SET(new_str "${target_str}${str_loop}")
		LIST(APPEND results ${new_str})
	ENDFOREACH(str_loop)

	SET(${return_list} "${results}" PARENT_SCOPE)
ENDFUNCTION(APPEND_STR_TO_LIST)

FUNCTION(GET_FILES_GROUPED dir return_result)
	GET_DIRS("${CMAKE_CURRENT_SOURCE_DIR}/src" src_dirs)
	GET_DIRS("${CMAKE_CURRENT_SOURCE_DIR}/includes" includes_dirs)
	SET(DIRS ${src_dirs} ${includes_dirs})

	SET(srcs "")
	FOREACH(loop_dir IN ITEMS ${DIRS})
		SET(rs "")
		APPEND_STR_TO_LIST("${loop_dir}/*" "${FILE_EXTENSIONS}" rs)
		FILE(GLOB files ${rs})

		# Remove the root directories.
		STRING(REPLACE "${CMAKE_SOURCE_DIR}/" "" loop_dir "${loop_dir}")

		# Apparently, slashes need to be replaced with backslashes to
		# support subgroups.
		string(REPLACE "/" "\\" GROUP "${loop_dir}")

		# When built for VS or xcode, the directory hierarchy is kept.
		SOURCE_GROUP(${GROUP} FILES ${files})

		LIST(APPEND srcs ${files})
	ENDFOREACH(loop_dir)

	INCLUDE_DIRECTORIES(${DIRS})
	SET(${return_result} "${srcs}" PARENT_SCOPE)
ENDFUNCTION(GET_FILES_GROUPED)

################################################################################
#-------------------------- End of macros -------------------------------------#
################################################################################

# Constants
set(FILE_EXTENSIONS ".h" ".c" ".cpp" ".hpp" ".cc")
set(PROJ_NAME "GetSecretMsgLib")
set(BIN_DIR ./bin)
set(CMAKE_CXX_STANDARD 11)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

# General
cmake_minimum_required(VERSION 3.10)
project(${PROJ_NAME})

# Add executables
GET_FILES_GROUPED("${CMAKE_SOURCE_DIR}/src/" SRCS)
add_library(${PROJ_NAME} STATIC ${SRCS})

set_target_properties(${PROJ_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY	"${CMAKE_SOURCE_DIR}/${BIN_DIR}"
    LIBRARY_OUTPUT_DIRECTORY	"${CMAKE_SOURCE_DIR}/${BIN_DIR}"
    RUNTIME_OUTPUT_DIRECTORY	"${CMAKE_SOURCE_DIR}/${BIN_DIR}"
    EXECUTABLE_OUTPUT_PATH		"${CMAKE_SOURCE_DIR}/${BIN_DIR}"
)

# Flags
set(CMAKE_CXX_FLAGS "-g")
