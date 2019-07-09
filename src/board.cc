#include <algorithm> // std::fill
#include <iterator> // std::begin, std::end
#include <stdexcept> // std::runtime_error, std::out_of_range
// #include <cassert>

#include "board.h"

namespace graph {
	std::default_random_engine Board::random_engine = std::default_random_engine(std::random_device()());
	std::uniform_int_distribution<int> Board::random_distribution(0);
	Board::Board(size_t width, size_t height, chartype f) : w(width), h(height), map(height * width) {
		if (f != 0) std::fill(map.begin(), map.end(), f);
	}
	Board::chartype Board::operator[] (Board::size_t n) const { return map[n]; }
	Board::chartype& Board::operator[] (Board::size_t n) { return map[n]; }

	Board::chartype Board::operator() (Board::size_t x, Board::size_t y) const {
		if (in_range(x, y)) return map[w * y + x];
		else throw std::out_of_range("base_map::operator() out of range");
	}
	Board::chartype& Board::operator() (Board::size_t x, Board::size_t y) {
		if (in_range(x, y)) return map[w * y + x];
		else throw std::out_of_range("base_map::operator() out of range");
	}

	bool Board::in_range(Board::size_t x, Board::size_t y) const noexcept {
		return x < w && x >= 0 && y < h && y >= 0;
	}
} // namespace graph