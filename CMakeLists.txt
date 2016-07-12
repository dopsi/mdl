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
set(mdl_VERSION_MINOR 5)
set(mdl_VERSION_REVISION 1)

find_package(Boost COMPONENTS program_options REQUIRED)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

configure_file(${PROJECT_SOURCE_DIR}/includes/configure.hpp.in ${PROJECT_BINARY_DIR}/configure.hpp)
include_directories(BEFORE ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/includes)
include_directories(${Boost_INCLUDE_DIRS})

add_library(mdl SHARED
	libmdl/document/document.cpp
	libmdl/document/line_element.cpp
	libmdl/document/text_line_element.cpp
	libmdl/document/url_line_element.cpp
	libmdl/document/code_line_element.cpp
	libmdl/document/bold_line_element.cpp
	libmdl/document/italic_line_element.cpp
	libmdl/document/paragraph.cpp
	libmdl/document/text_paragraph.cpp
	libmdl/document/title1_paragraph.cpp
	libmdl/document/title2_paragraph.cpp
	libmdl/document/ulist1_paragraph.cpp
	libmdl/document/code_paragraph.cpp
	libmdl/document/quote_paragraph.cpp
	libmdl/display_driver.cpp
	libmdl/parser.cpp
	)

add_executable(mdless 
	mdl/main.cpp
	mdl/display_drivers/ncurses_display_driver.cpp
	mdl/display_drivers/plaintext_display_driver.cpp
	mdl/display_drivers/latex_display_driver.cpp
	mdl/parsers/md_parser.cpp) 

target_compile_features(mdl PRIVATE cxx_nullptr cxx_strong_enums)
target_compile_features(mdless PRIVATE cxx_nullptr cxx_strong_enums)

target_link_libraries(mdless 
	${Boost_LIBRARIES}
	ncurses
	mdl)

install(TARGETS mdl DESTINATION lib)
install(TARGETS mdless DESTINATION bin)
