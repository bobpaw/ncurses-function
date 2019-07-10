#ifdef HAVE_CMAKECONFIG_H
#include <cmakeconfig.h>
#endif

#include <algorithm> // std::fill
#include <iterator> // std::begin, std::end
#include <stdexcept> // std::runtime_error, std::out_of_range
#include <cassert>

#include "board.h"

namespace graph {
	std::default_random_engine Board::random_engine = std::default_random_engine(std::random_device()());
	std::uniform_int_distribution<int> Board::random_distribution(0);
	Board::Board(size_t width, size_t height, chartype f, WINDOW* w): 
		w(width),
		h(height),
		map(height * width),
		blank(f),
		win(w) {
		assert(getmaxx(w) != ERR);
		assert(getmaxy(w) != ERR);
		assert(width <= static_cast<size_t>(getmaxx(w)));
		assert(height <= static_cast<size_t>(getmaxy(w)));
		if (f != 0) std::fill(map.begin(), map.end(), f);
	}

	Board::Board(WINDOW* w, chartype f) : Board(getmaxx(w), getmaxy(w), f, w) {
		assert(win != nullptr);
		assert(getmaxx(w) != ERR);
		assert(getmaxy(w) != ERR);
	}

	auto Board::operator() (size_t x, size_t y) const -> chartype {
		if (in_range(x, y)) return map[w * y + x];
		else throw std::out_of_range("base_map::operator() out of range");
	}
	auto Board::operator() (size_t x, size_t y) -> chartype& {
		if (in_range(x, y)) return map[w * y + x];
		else throw std::out_of_range("base_map::operator() out of range");
	}

	bool Board::in_range(size_t x, size_t y) const my_noexcept {
		return x < w && y < h;
	}

	int Board::display () const {
		int errorvalue;
		for (int y = 0; static_cast<size_t>(y) < h; ++y) {
			for (int x = 0; static_cast<size_t>(x) < w; ++x) {
				errorvalue = mvwaddch(win, y, x, operator()(x, y));
				if (errorvalue == ERR) return ERR;
			}
		}
		return OK;
	}

	double distance(double x1, double y1, double x2, double y2) {
		return std::sqrt(std::pow(y2 - y1, 2) + std::pow(x2 - x1, 2));
	}

	int Board::line(size_t x1, size_t y1, size_t x2, size_t y2, chartype c) my_noexcept {
		// if (!(in_range(x1, y1) && in_range(x2, y2))) return ERR;
		// Allow it to be way too far so it can be weird stuff
		
		// Naive point slope form
#if 1
		double m = (y2 - y1) * 1.0 / (x2 - x1);
		for (size_t x = x1, y = 0; x <= x2 && x < w; ++x) {
			y = static_cast<size_t>(m * (x - x1) + y1);
			if (in_range(x, y)) operator()(x, y) = c;
		}
#else
		// Other method, likely try to use distance
#endif
		return OK;
	}
	int Board::clear(bool clr_scr) {
		std::fill(map.begin(), map.end(), blank);
		if (clr_scr) return werase(win);
		return OK;
	}
} // namespace graph