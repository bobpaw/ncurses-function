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
		using chartype = chtype;

	private:
		using size_t = std::vector<chartype>::size_type;
		size_t w;
		size_t h;
		std::vector<chartype> map;
		static std::default_random_engine random_engine;
		static std::uniform_int_distribution<int> random_distribution;

	public:

		// Random number generator, often useful.
		static int RNG () {
			return random_distribution(random_engine);
		}

		// Constructors, Destructors, Copy/Move

		// Fill with character
		Board(size_t width, size_t height, chartype f);

		Board (size_t width, size_t height): Board(width, height, 0) {}

		// Access
#if defined(HAVE_AUTO_RETURN) || defined(HAVE_CXX14) || __cplusplus > 201400
		auto width () const noexcept { return w; }
		auto height () const noexcept { return h; }
#else
		decltype(w) width () const noexcept { return w; }
		decltype(h) height () const noexcept { return h; }
#endif

		chartype operator[] (size_t n) const;
		chartype& operator[] (size_t n);

		chartype operator() (size_t x, size_t y) const;
		chartype& operator() (size_t x, size_t y);

		bool in_range(size_t x, size_t y) const noexcept;
	}; // class Board

} // namespace graph

#endif // GRAPH_BOARD_H_
