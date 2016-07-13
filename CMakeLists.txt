cmake_minimum_required(VERSION 2.6)
# Check for out-of-source build
if( CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR AND NOT MSVC_IDE )
	message(FATAL_ERROR "In-source builds are not allowed.
	Please create a directory and run cmake from there, passing the path
	to this source directory as the last argument.
	This process created the file `CMakeCache.txt' and the directory `CMakeFiles'.
	Please delete them.")
endif()

set(CMAKE_BUILD_TYPE Debug)

# Set project data
project(mdl)
set(mdl_VERSION_MAJOR 0)
set(mdl_VERSION_MINOR 5)
set(mdl_VERSION_REVISION 1)

add_subdirectory(libmdl)
add_subdirectory(mdl)
