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

include_directories(${LIBMDL_INCLUDE_DIRS})

# Set project data
project(mdlbin)
set(mdlbin_VERSION_MAJOR 1)
set(mdlbin_VERSION_MINOR 0)
set(mdlbin_VERSION_REVISION 0)

find_package(Boost COMPONENTS program_options REQUIRED)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

configure_file(${PROJECT_SOURCE_DIR}/configure.hpp.in ${PROJECT_BINARY_DIR}/configure.hpp)
include_directories(BEFORE ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/includes)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${libmdl_INCLUDE_DIRS})

add_executable(mdlbin 
	main.cpp
	display_drivers/ncurses_display_driver.cpp
	display_drivers/plaintext_display_driver.cpp
	display_drivers/latex_display_driver.cpp
	display_drivers/html_display_driver.cpp
	display_drivers/troff_display_driver.cpp
	parsers/md_parser.cpp) 

set_target_properties(mdlbin
	PROPERTIES OUTPUT_NAME mdl)

target_compile_features(mdlbin PRIVATE cxx_nullptr cxx_strong_enums)

target_link_libraries(mdlbin 
	${Boost_LIBRARIES}
	ncurses
	libmdl)

install(TARGETS mdlbin DESTINATION bin)
