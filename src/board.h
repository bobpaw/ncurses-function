#if defined(HAVE_CMAKECONFIG_H)
#include <cmakeconfig.h>
#endif

#include <random> // std::random_device, std::default_random_engine, etc.
#include <vector> // std::vector (duh)

#include "correct_curses.h"

#ifndef GRAPH_BOARD_H_
#define GRAPH_BOARD_H_

namespace graph {
	class Board {
	public:
#if defined(__cpp_alias_templates) || __cplusplus > 200704
		using chartype = chtype;
#else
		typedef chtype chartype;
#endif

	private:

#if defined(__cpp_alias_templates) || __cplusplus > 200704
		using size_t = std::vector<chartype>::size_type;
#else
		typedef std::vector<chartype>::size_type size_t;
#endif

		size_t w;
		size_t h;
		std::vector<chartype> map;
		chartype blank;
		WINDOW* win;
		static std::default_random_engine random_engine;
		static std::uniform_int_distribution<int> random_distribution;

	public:

		// Random number generator, often useful.
		static int RNG () {
			return random_distribution(random_engine);
		}

		// Constructors, Destructors, Copy/Move

		// Fill with character
		Board(size_t width, size_t height, chartype f, WINDOW* w);

		Board(size_t width, size_t height, chartype f) : Board(width, height, f, stdscr) {}
		Board(WINDOW* w, chartype f);
		Board(WINDOW* w) : Board(w, 0) {}
		Board (size_t width, size_t height): Board(width, height, 0) {}

		// Access
#if defined(HAVE_AUTO_RETURN) || defined(HAVE_CXX14) || __cplusplus > 201400
		auto width () const my_noexcept { return w; }
		auto height () const my_noexcept { return h; }
#else
		decltype(w) width () const my_noexcept { return w; }
		decltype(h) height () const my_noexcept { return h; }
#endif

		chartype operator[] (Board::size_t n) const { return map[n]; }
		chartype& operator[] (Board::size_t n) { return map[n]; }

		auto operator() (size_t x, size_t y) const -> chartype;
		auto operator() (size_t x, size_t y) -> chartype&;

		bool in_range(size_t x, size_t y) const my_noexcept;
		int display() const;
		int clear(bool clr_scr = false);
		int line(size_t x1, size_t y1, size_t x2, size_t y2, chartype c = '#') my_noexcept;
	}; // class Board

} // namespace graph

#endif // GRAPH_BOARD_H_
