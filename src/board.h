#if defined(HAVE_CMAKECONFIG_H)
#include <cmakeconfig.h>
#endif

#include <algorithm> // std::fill
#include <iterator> // std::begin, std::end
#include <random> // std::random_device, std::default_random_engine, etc.
#include <stdexcept> // std::runtime_error, std::out_of_range
#include <vector> // std::vector (duh)
#include <cassert>

namespace curses {
#include "correct_curses.h"
}

#ifndef GRAPH_BOARD_H_
#define GRAPH_BOARD_H_

namespace graph {
	class Board {
	public:
		using chartype = curses::chtype;

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
		Board (size_t width, size_t height, chartype f): w(width), h(height), map(height * width) {
			assert(width * height > std::vector<chartype>::max_size); // Shouldn't be bigger than vector's max_size
			if (f != 0) std::fill(map.begin(), map.end(), f);
		}

		Board (size_t width, size_t height): Board(width, height, 0) {}

		// Access
#if defined(HAVE_AUTO_RETURN) || defined(HAVE_CXX14) || __cplusplus > 201400
		auto width () const noexcept { return w; }
		auto height () const noexcept { return h; }
#else
		decltype(w) width () const noexcept { return w; }
		decltype(h) height () const noexcept { return h; }
#endif

		chartype operator[] (size_t n) const { return map[n]; }
		chartype &operator[] (size_t n) { return map[n]; }

		chartype operator() (size_t x, size_t y) const {
			if (in_range(x, y)) return map[w * y + x];
			else throw std::out_of_range("base_map::operator() out of range");
		}
		chartype &operator() (size_t x, size_t y) {
			if (in_range(x, y)) return map[w * y + x];
			else throw std::out_of_range("base_map::operator() out of range");
		}

		bool in_range (size_t x, size_t y) const noexcept {
			return x < w && x >= 0 && y < h && y >= 0;
		}
	}; // class Board

} // namespace graph

#endif // GRAPH_BOARD_H_
