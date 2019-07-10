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

int main () {
	if (initscr() == NULL) CURSES_ERROR(initscr);
	if (curs_set(0) == ERR) CURSES_ERROR(curs_set);
	graph::Board board(stdscr, ' ');
	if (board.line(0, 0, 30, 15) == ERR) {
		endwin();
		std::cerr << "Error drawing line" << std::endl;
		return -1;
	}
	board.display();
	refresh();
	getch();
	endwin();
	return 0;
}