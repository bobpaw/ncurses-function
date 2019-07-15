#include <iostream> // std::cerr
#include <cstdlib> // std::atexit, EXIT_SUCCESS, EXIT_FAILURE

#include "correct_curses.h"

#include "board.h"

#define CURSES_ERROR(func) do { \
if (!isendwin()) endwin(); \
std::cerr << "curses error (" #func ")." << std::endl; \
return EXIT_FAILURE; \
} while (0)

#define CURSES_ERRORM(func, msg) do { \
if (!isendwin()) endwin(); \
std::cerr << "curses error (" #func "): " msg << std::endl; \
return EXIT_FAILURE; \
} while (0)

void exit_func () {
	if (!isendwin()) endwin();
}

int main () {
	if (std::atexit(exit_func) != 0) {
		std::cerr << "atexit failure" << std::endl;
		return EXIT_FAILURE;
	}
	if (initscr() == NULL) CURSES_ERROR(initscr);
	if (curs_set(0) == ERR) CURSES_ERROR(curs_set);
	if (noecho() == ERR) CURSES_ERROR(noecho);
	if (cbreak() == ERR) CURSES_ERROR(cbreak); // Non-buffered reads
	if (keypad(stdscr, true) == ERR) CURSES_ERROR(keypad);
	timeout(-1); // Blocking getch
	graph::Board board(stdscr, ' ');
	board.set_center(COLS / 2, LINES / 2);
	board.invert_y(true);
	int x1 = 0, y1 = 0, x2 = 5, y2 = 5, ch = 0, moving = 1;
	board.draw_axes();
	if (board.line(x1, y1, x2, y2) == ERR) {
		endwin();
		std::cerr << "Error drawing line" << std::endl;
		return EXIT_FAILURE;
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
			if (moving == 1) --x2;
			else --x1;
			break;
		case KEY_RIGHT:
		case 'd':
			if (moving == 1) ++x2;
			else ++x1;
			break;
		case KEY_UP:
		case 'w':
			if (moving == 1) ++y2;
			else ++y1;
			break;
		case KEY_DOWN:
		case 's':
			if (moving == 1) --y2;
			else --y1;
			break;
		case 'e':
			moving ^= 1;
		}
		if (board.clear(true) == ERR) CURSES_ERROR(erase);
		board.draw_axes();
		if (board.line(x1, y1, x2, y2) == ERR) {
			endwin();
			std::cerr << "Error drawing line" << std::endl;
			return -1;
		}
		board(x1, y1) = 'A';
		board(x2, y2) = 'B';
		board.display();
		refresh();
	} while (ch != 'q');
	endwin();
	return EXIT_SUCCESS;
}