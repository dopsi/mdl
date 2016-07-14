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

add_custom_command(OUTPUT mdl.1
	COMMAND ${PROJECT_BINARY_DIR}/mdl/mdl
	ARGS -d troff -o ${PROJECT_BINARY_DIR}/mdl.1
		${PROJECT_SOURCE_DIR}/assets/mdl.1.md
	DEPENDS ${PROJECT_SOURCE_DIR}/assets/mdl.1.md
	COMMENT Generate manpage
	VERBATIM)

add_custom_target(
	man ALL
	DEPENDS ${PROJECT_BINARY_DIR}/mdl.1 mdlbin
	)

install(FILES ${PROJECT_BINARY_DIR}/mdl.1 DESTINATION man/man1)
