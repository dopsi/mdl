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
project(mdl)
set(mdl_VERSION_MAJOR 0)
set(mdl_VERSION_MINOR 4)
set(mdl_VERSION_REVISION 1)

find_package(Boost COMPONENTS program_options REQUIRED)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

configure_file(${PROJECT_SOURCE_DIR}/src/configure.hpp.in ${PROJECT_BINARY_DIR}/configure.hpp)
include_directories(BEFORE ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/src)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(mdl 
	src/main.cpp
	src/display_drivers/display_driver.cpp
	src/display_drivers/ncurses_display_driver.cpp
	src/display_drivers/plaintext_display_driver.cpp
	src/document/document.cpp
	src/document/line_element.cpp
	src/document/text_line_element.cpp
	src/document/url_line_element.cpp
	src/document/code_line_element.cpp
	src/document/bold_line_element.cpp
	src/document/italic_line_element.cpp
	src/document/paragraph.cpp
	src/document/text_paragraph.cpp
	src/document/title1_paragraph.cpp
	src/document/title2_paragraph.cpp
	src/document/ulist1_paragraph.cpp
	src/document/code_paragraph.cpp
	src/document/quote_paragraph.cpp
	src/parsers/parser.cpp
	src/parsers/md_parser.cpp) 

target_compile_features(mdl PRIVATE cxx_nullptr cxx_strong_enums)

target_link_libraries(mdl 
	${Boost_LIBRARIES}
	ncurses)

install(TARGETS mdl DESTINATION bin)
