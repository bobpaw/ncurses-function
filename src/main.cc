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
	if (noecho() == ERR) CURSES_ERROR(noecho);
	if (cbreak() == ERR) CURSES_ERROR(cbreak); // Non-buffered reads
	if (keypad(stdscr, true) == ERR) CURSES_ERROR(keypad);
	timeout(-1); // Blocking getch
	graph::Board board(stdscr, ' ');
	int x = 30, y = 15, ch = 0;
	if (board.line(0, 0, 30, 15) == ERR) {
		endwin();
		std::cerr << "Error drawing line" << std::endl;
		return -1;
	}
	board.display();
	if (refresh() == ERR) CURSES_ERROR(refresh);
	do {
		ch = getch();
		if (ch == ERR) CURSES_ERROR(getch);
		ch = tolower(ch);
		switch (ch) {
		case KEY_LEFT:
		case 'a':
			--x;
			break;
		case KEY_RIGHT:
		case 'd':
			++x;
			break;
		case KEY_UP:
		case 'w':
			--y;
			break;
		case KEY_DOWN:
		case 's':
			++y;
			break;
		}
		if (board.clear(true) == ERR) CURSES_ERROR(erase);
		if (board.line(0, 0, x, y) == ERR) {
			endwin();
			std::cerr << "Error drawing line" << std::endl;
			return -1;
		}
		board.display();
		refresh();
	} while (ch != 'q');
	endwin();
	return 0;
}