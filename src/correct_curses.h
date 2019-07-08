#if defined(HAVE_CONFIG_H) || defined(HAVE_CMAKE_CONFIG_H) // FIXME(Aiden): This is a CMake project, so HAVE_CONFIG_H won't be defined. Also get rid of impossible if's.
#if defined(HAVE_CONFIG_H)
#include <config.h>
#else
#include <cmakeconfig.h>
#endif

#if defined HAVE_NCURSESW_CURSES_H
#  include <ncursesw/curses.h>
#elif defined HAVE_NCURSESW_H
#  include <ncursesw.h>
#elif defined HAVE_NCURSES_CURSES_H
#  include <ncurses/curses.h>
#elif defined HAVE_NCURSES_H
#  include <ncurses.h>
#elif defined HAVE_CURSES_H
#  include <curses.h>
#else
#  error "SysV or X/Open-compatible Curses header file required"
#endif
#else

// Fingers-crossed
#include <curses.h>
#endif
