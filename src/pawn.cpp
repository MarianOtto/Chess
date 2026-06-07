#include "../include/pawn.h"
#include "../include/board.h"
#include <cstdint>
#include <cstdio>
#include <sys/types.h>
#include <vector>

Pawn::Pawn(Color color, Square* square, Board& board)
  : Figure(color, square, Type::Pawn, board)
{
}

Figure* Pawn::fromNotation(Color color, std::string notation, Board& board)
{
  std::unique_ptr<Figure> figure;
  figure = std::make_unique<Pawn>(color, board.get_square_at(notation), board);
  board.get_square_at(notation)->set_figure(figure.get());
  board.addFigure(std::move(figure));
  return board.get_figure_on(notation);
}

uint64_t Pawn::get_possible_moves()
{
  uint64_t pos = this->_square->bit();
  bool is_white = _color == Color::White ? 1 : 0;

  uint64_t enemy_squares =
    is_white ? _board.get_black_bitmap() : _board.get_white_bitmap();
  uint64_t free_squares = ~_board.get_any_bitmap();

  uint64_t last_rank =
    is_white ? 0xFF00000000000000ULL : 0xFFULL; // 8th or 1st row

  // Pawns on last rank dont have valid moves
  if (pos & last_rank)
    return 0ULL;

  // Single Push
  uint64_t single_push = is_white ? pos << 8 : pos >> 8;

  // Double Push
  uint64_t start_rank =
    is_white ? 0xFF00ULL : 0x00FF000000000000ULL; // 7th or 2nd row

  uint64_t double_push = 0ULL;
  if (pos & start_rank) {
    if (single_push & free_squares) {
      double_push = is_white ? pos << 16 : pos >> 16;
    }
  }

  // Capture left
  uint64_t not_a_file = 0xFEFEFEFEFEFEFEFE;
  uint64_t cap_left =
    (pos & not_a_file) ? (is_white ? pos << 7 : pos >> 9) : 0ULL;

  // Capture right
  uint64_t not_h_file = 0x7F7F7F7F7F7F7F7F;
  uint64_t cap_right =
    (pos & not_h_file) ? (is_white ? pos << 9 : pos >> 7) : 0ULL;

  return ((single_push | double_push) & free_squares) |
         ((cap_left | cap_right) & enemy_squares);
}