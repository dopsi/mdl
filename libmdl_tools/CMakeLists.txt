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

include(CheckFunctionExists)

# Set project data
project(libmdl_tools)
set(libmdl_VERSION_MAJOR 1)
set(libmdl_VERSION_MINOR 0)
set(libmdl_VERSION_REVISION 0)

find_package(Boost COMPONENTS program_options REQUIRED)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

configure_file(${PROJECT_SOURCE_DIR}/includes/configure.hpp.in ${PROJECT_BINARY_DIR}/configure.hpp)
include_directories(BEFORE ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/includes)

add_library(libmdl_tools SHARED
	ansi_wrapper.cpp
	)

set_target_properties(libmdl_tools
	PROPERTIES OUTPUT_NAME mdl_tools)
set_target_properties(libmdl_tools
	PROPERTIES SOVERSION 
	${libmdl_VERSION_MAJOR}.${libmdl_VERSION_MINOR}.${libmdl_VERSION_REVISION})

target_compile_features(libmdl_tools PRIVATE cxx_nullptr cxx_strong_enums)

install(TARGETS libmdl_tools DESTINATION lib)

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/includes
	PARENT_SCOPE)

file(GLOB include_files "${PROJECT_SOURCE_DIR}/includes/tools/*.hpp")
install(FILES ${include_files} DESTINATION include/mdl/tools)
