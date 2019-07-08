cmake_minimum_required(VERSION 3.8)
project(ncurses-function VERSION 0.0 LANGUAGES C CXX)

# Macros and stuff
include(CheckIncludeFileCXX)
include(CheckIncludeFile)
include(CheckCXXCompilerFlag)
include(CheckSymbolExists)
include(CheckCXXSymbolExists)

# CXX Compile Features options
if ($<COMPILE_FEATURES:cxx_return_type_deduction>)
	set(HAVE_AUTO_RETURN YES)
endif()

# Settable options, i.e. to fix issues on VisualStudio
set(EXTRA_GLOBAL_OPTIONS "" CACHE STRING "Extra options to set")
set(EXTRA_LINKER_OPTIONS "" CACHE STRING "Extra linker options to set")
add_compile_options(${EXTRA_GLOBAL_OPTIONS})
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EXTRA_LINKER_OPTIONS}")

option(USE_PDCURSES "Use PDCurses")
if (USE_PDCURSES)
	set(PDCURSES_SRCDIR "C:/PDCurses" CACHE FILEPATH "PDCurses' Source Directory")
	set(PDCURSES_LIBRARIES "C:/PDCurses/wincon/pdcurses.lib" CACHE FILEPATH "PDCurses Library")
else()
	include(FindCurses)
endif()

# Large number of compiler flags (but not unreasonable, i.e. not VS's -Wall)
check_cxx_compiler_flag(-W4 HAVE_W4)
if (HAVE_W4)
	add_compile_options(-W4)
else()
	check_cxx_compiler_flag(-Wall HAVE_WALL)
	check_cxx_compiler_flag(-Wextra HAVE_WEXTRA)
	check_cxx_compiler_flag(-pedantic HAVE_PEDANTIC)
endif()
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG" $<${HAVE_WALL}:-Wall> $<${HAVE_WEXTRA}:-Wextra> $<${HAVE_PEDANTIC}:-pedantic>)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE" -DNDEBUG)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Set some variables to match autoconf ones
set(PACKAGE_NAME ${PROJECT_NAME})
string(TOLOWER ${PACKAGE_NAME} PACKAGE)
set(PACKAGE_VERSION ${PROJECT_VERSION})
string(CONCAT PACKAGE_STRING ${PACKAGE_NAME} " " ${VERSION})
set(PACKAGE_BUGREPORT aiden.woodruff@gmail.com)
set(PACKAGE_URL ${HOMEPAGE_URL})

# Check for headers
check_include_file_cxx(string HAVE_STRING)
check_include_file_cxx(cstdint HAVE_CSTDINT)
check_include_file_cxx(cassert HAVE_CASSERT)
check_include_file_cxx(iostream HAVE_IOSTREAM)
check_include_file_cxx(functional HAVE_FUNCTIONAL)
check_include_file_cxx(random HAVE_RANDOM)
check_include_file_cxx(cmath HAVE_CMATH)
check_include_file(inttypes.h HAVE_INTTYPES_H)
check_include_file(memory.h HAVE_MEMORY_H)
check_include_file(stdint.h HAVE_STDINT_H)
check_include_file(stdlib.h HAVE_STDLIB_H)
check_include_file(string.h HAVE_STRING_H)
check_include_file(strings.h HAVE_STRINGS_H)
check_include_file(sys/stat.h HAVE_SYS_STAT_H)
check_include_file(sys/types.h HAVE_SYS_TYPES_H)
check_include_file(unistd.h HAVE_UNISTD_H))

# Check for libraries

# Set options similar to autoconf ones based off FindCurses's flags
if (USE_PDCURSES)
	# Change PDCurses options to match FindCurses ones
	message(STATUS "Using PDCurses")
	set(CURSES_INCLUDE_DIRS ${PDCURSES_SRCDIR})
	set(CURSES_LIBRARIES ${PDCURSES_LIBRARIES})
	set(HAVE_CURSES YES)
	set(HAVE_CURSES_H YES)
else ()
	find_package(Curses)
	if (CURSES_FOUND)
		set(HAVE_CURSES ${CURSES_FOUND})
		set(HAVE_CURSES_H ${CURSES_HAVE_CURSES_H})
		set(HAVE_NCURSES_H ${CURSES_HAVE_NCURSES_H})
		set(HAVE_NCURSES_CURSES_H ${CURSES_HAVE_NCURSES_CURSES_H})
	else()
		message(FATAL_ERROR "No type of curses has been found. One fix might be to run cmake with the USE_PDCURSES option.")
	endif ()
endif ()

# Set the header to include
# NOTE: There are a number of other weird ones FindCurses has, but we'll ignore those
if (HAVE_NCURSES_CURSES_H)
	set(CURSES_HEADER "ncurses/curses.h")
	set(HAVE_NCURSES YES)
elseif (HAVE_NCURSES_H)
	set(CURSES_HEADER "ncurses.h")
	set(HAVE_NCURSES YES)
elseif (HAVE_CURSES_H)
	set(CURSES_HEADER "curses.h")
endif()

# Check for color support in curses, based off existence of the start_color function
if (HAVE_CURSES)
	set(CMAKE_REQUIRED_INCLUDES ${CURSES_INCLUDE_DIRS})
	set(CMAKE_REQUIRED_LIBRARIES ${CURSES_LIBRARIES})
	check_cxx_symbol_exists(start_color ${CURSES_HEADER} HAVE_CURSES_COLOR)
	if (HAVE_CURSES_COLOR)
		message(STATUS "Found color support for curses")
	else()
		message(STATUS "Did NOT find color support for curses")
	endif()
endif()

find_library(HAVE_MATH m)

# Check for types
check_cxx_symbol_exists(int32_t cstdint HAVE_UINT32_T)

add_compile_definitions(HAVE_CMAKE_CONFIG_H)
configure_file(cmakeconfig.h.in cmakeconfig.h ESCAPE_QUOTES @ONLY)

# add_subdirectory(src)
# add_subdirectory(test)