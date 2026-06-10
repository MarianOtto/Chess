#include "../include/bishop.h"
#include "../include/board.h"
#include <cstdint>
#include <cstdio>
#include <sys/types.h>

Bishop::Bishop(Color color, Square* square, Board& board)
  : Figure(color, square, Type::Bishop, board)
{
}

Figure* Bishop::fromNotation(Color color, std::string notation, Board& board)
{
  std::unique_ptr<Figure> figure;
  figure =
    std::make_unique<Bishop>(color, board.get_square_at(notation), board);
  board.get_square_at(notation)->set_figure(figure.get());
  board.addFigure(std::move(figure));
  return board.get_figure_on(notation);
}

uint64_t Bishop::get_possible_moves()
{
  uint64_t pos = this->_square->bit();
  bool is_white = _color == Color::White ? 1 : 0;
  uint64_t my_squares =
    is_white ? _board.get_white_bitmap() : _board.get_black_bitmap();
  uint64_t enemy_squares =
    is_white ? _board.get_black_bitmap() : _board.get_white_bitmap();
  uint64_t free_squares = ~_board.get_any_bitmap();

  uint64_t moves = 0ULL;

  uint64_t a_file = 0x0101010101010101ULL;
  uint64_t h_file = 0x8080808080808080ULL;
  uint64_t rank_1 = 0x00000000000000FFULL;
  uint64_t rank_8 = 0xFF00000000000000ULL;

  uint64_t square = pos;

  // North East
  for (int i = 1; i <= 7; i++) {
    if (square & (rank_8 | h_file)) // Check Edge
      break;
    square <<= 9;
    if (square & free_squares) {
      moves |= square;
      continue;
    }
    moves |= (square & enemy_squares) ? square : 0ULL;
    break;
  }

  // South East
  square = pos;
  for (int i = 1; i <= 7; i++) {
    if (square & (rank_1 | h_file)) // Check Edge
      break;
    square >>= 7;
    if (square & free_squares) {
      moves |= square;
      continue;
    }
    moves |= (square & enemy_squares) ? square : 0ULL;
    break;
  }

  // South West
  square = pos;
  for (int i = 1; i <= 7; i++) {
    if (square & (rank_1 | a_file)) // Check Edge
      break;
    square >>= 9;
    if (square & free_squares) {
      moves |= square;
      continue;
    }
    moves |= (square & enemy_squares) ? square : 0ULL;
    break;
  }

  // North West
  square = pos;
  for (int i = 1; i <= 7; i++) {
    if (square & (rank_8 | a_file)) // Check Edge
      break;
    square <<= 7;
    if (square & free_squares) {
      moves |= square;
      continue;
    }
    moves |= (square & enemy_squares) ? square : 0ULL;
    break;
  }

  return moves;
}