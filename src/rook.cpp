#include "../include/rook.h"
#include "../include/board.h"
#include <cstdint>
#include <cstdio>
#include <sys/types.h>

Rook::Rook(Color color, Square* square, Board& board)
  : Figure(color, square, Type::Rook, board)
{
}

Figure* Rook::fromNotation(Color color, std::string notation, Board& board)
{
  std::unique_ptr<Figure> figure;
  figure = std::make_unique<Rook>(color, board.get_square_at(notation), board);
  board.get_square_at(notation)->set_figure(figure.get());
  board.addFigure(std::move(figure));
  return board.get_figure_on(notation);
}

uint64_t Rook::get_possible_moves()
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

  // North
  for (int i = 1; i <= 7; i++) {
    if (square & rank_8)
      break;
    square <<= 8;
    if (square & free_squares) {
      moves |= square;
      continue;
    }
    moves |= (square & enemy_squares) ? square : 0ULL;
    break;
  }

  // East
  square = pos;
  for (int i = 1; i <= 7; i++) {
    if (square & h_file)
      break;
    square <<= 1;
    if (square & free_squares) {
      moves |= square;
      continue;
    }
    moves |= (square & enemy_squares) ? square : 0ULL;
    break;
  }

  // South
  square = pos;
  for (int i = 1; i <= 7; i++) {
    if (square & rank_1)
      break;
    square >>= 8;
    if (square & free_squares) {
      moves |= square;
      continue;
    }
    moves |= (square & enemy_squares) ? square : 0ULL;
    break;
  }

  // West
  square = pos;
  for (int i = 1; i <= 7; i++) {
    if (square & a_file)
      break;
    square >>= 1;
    if (square & free_squares) {
      moves |= square;
      continue;
    }
    moves |= (square & enemy_squares) ? square : 0ULL;
    break;
  }
  // TODO: Castleing

  return moves;
}