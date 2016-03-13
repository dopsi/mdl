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

# Set compiler flags
if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

# Set project data
project(mdl)
set(mdl_VERSION_MAJOR 0)
set(mdl_VERSION_MINOR 1)
set(mdl_VERSION_REVISION 0)

find_package(Boost REQUIRED)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

configure_file(${PROJECT_SOURCE_DIR}/configure.hpp.in ${PROJECT_BINARY_DIR}/configure.hpp)
include_directories(BEFORE ${PROJECT_BINARY_DIR})
include_directories(${Boost_INCLUDE_DIRS})

add_executable(mdl 
	main.cpp
	display_driver.cpp
	ncurses_display_driver.cpp
	plaintext_display_driver.cpp
	document.cpp
	line_element.cpp
	text_line_element.cpp
	paragraph.cpp
	text_paragraph.cpp
	title1_paragraph.cpp
	title2_paragraph.cpp
	parser.cpp
	md_parser.cpp) 

target_link_libraries(mdl 
	${Boost_LIBRARIES}
	ncurses)
