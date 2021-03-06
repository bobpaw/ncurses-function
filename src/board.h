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
#if defined(__cpp_alias_templates) || __cplusplus >= 200704L
		using chartype = chtype;
#else
		typedef chtype chartype;
#endif

	private:

#if defined(__cpp_alias_templates) || __cplusplus >= 200704L
		using size_t = std::vector<chartype>::size_type;
#else
		typedef std::vector<chartype>::size_type size_t;
#endif
		struct {
			unsigned int invx: 1; // Boolean
			unsigned int invy: 1; // Boolean
			unsigned int : 0; // Padding
		} opts;
		size_t w;
		size_t h;
		size_t c_x;
		size_t c_y;
		std::vector<chartype> map;
		chartype blank;
		WINDOW* win;
		static std::default_random_engine random_engine;
		static std::uniform_int_distribution<int> random_distribution;

		// Read-only access, specifically for drawing implementation
		auto at (size_t x, size_t y) const->chartype;

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
#if defined(HAVE_AUTO_RETURN) || defined(HAVE_CXX14) || __cplusplus >= 201400L
		auto width () const my_noexcept { return w; }
		auto height () const my_noexcept { return h; }
#else
		decltype(w) width () const my_noexcept { return w; }
		decltype(h) height () const my_noexcept { return h; }
#endif
		// NOTE: minx/y functions were written after midnight, so they're error-prone I guess.
		// Output minimums and maximums of the form [min, max]
		int maxx () const my_noexcept { return static_cast<int>(w - c_x - 1); }
		int minx () const my_noexcept { return static_cast<int>(c_x) * -1; }
		int maxy () const my_noexcept { return static_cast<int>(h - c_y - 1); }
		int miny () const my_noexcept { return static_cast<int>(c_y) * -1; }

		chartype operator[] (size_t n) const { return map[n]; }
		chartype& operator[] (size_t n) { return map[n]; }

		auto operator() (int x, int y) const -> chartype;
		auto operator() (int x, int y) -> chartype&;
		
		/* set_range (int x, int y, const_iterator begin, const_iterator end, bool vertical = false)
		If vertical is true, prints low y to high y as much as possible. Returns ERR on out of range (x,y), but never throws.
		*/
		template <typename I>
		typename std::enable_if<std::is_convertible<typename std::iterator_traits<I>::value_type, chartype>::value, int>::type
			set_range (int x, int y, const I &begin, const I &end, bool vertical = false) my_noexcept {
			if (!in_range(x, y)) return ERR;
			for (I iter = begin; iter != end && in_range(x, y); vertical ? ++y : ++x, std::advance(iter, 1))
				operator()(x, y) = *iter;
			return OK;
		}

		bool in_range(int x, int y) const my_noexcept;

		// Options
		void set_center(size_t x, size_t y);
		void invert_x (bool val = true) my_noexcept { opts.invx = val; }
		void invert_y (bool val = true) my_noexcept { opts.invy = val; }

		// Execution
		void draw_axes (bool xaxis = true, bool yaxis = true) my_noexcept;
		int display() const;
		int clear(bool clr_scr = false);
		int line(int x1, int y1, int x2, int y2, chartype c = '#') my_noexcept;
	}; // class Board

} // namespace graph

#endif // GRAPH_BOARD_H_
