#include <iostream> // std::cerr

#include "correct_curses.h"

#include "board.h"

#define CURSES_ERROR(func) do { \
if (!isendwin()) endwin(); \
std::cerr << "curses error (" #func ")." << std::endl; \
return -1; \
} while (0)

#define CURSES_ERRORM(func, msg) do { \
if (!isendwin()) endwin(); \
std::cerr << "curses error (" #func "): " msg << std::endl; \
return -1; \
} while (0)

int main (int argc, char* argv[]) {
	if (initscr() == NULL) CURSES_ERROR(initscr);
	if (addstr("Hello World.") == ERR) CURSES_ERROR(addstr);
	getch();
	endwin();
	return 0;
}