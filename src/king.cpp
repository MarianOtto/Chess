#include "../include/king.h"
#include "../include/board.h"
#include <cstdint>
#include <cstdio>
#include <sys/types.h>

King::King(Color color, Square* square, Board& board)
  : Figure(color, square, Type::King, board)
{
}

Figure* King::fromNotation(Color color, std::string notation, Board& board)
{
  std::unique_ptr<Figure> figure;
  figure = std::make_unique<King>(color, board.get_square_at(notation), board);
  board.get_square_at(notation)->set_figure(figure.get());
  board.addFigure(std::move(figure));
  return board.get_figure_on(notation);
}

uint64_t King::get_possible_moves()
{
  uint64_t pos = this->_square->bit();
  bool is_white = _color == Color::White ? 1 : 0;
  uint64_t my_squares =
    is_white ? _board.get_white_bitmap() : _board.get_black_bitmap();

  uint64_t moves = 0ULL;

  uint64_t not_a_file = 0xFEFEFEFEFEFEFEFEULL;
  uint64_t not_h_file = 0x7F7F7F7F7F7F7F7FULL;
  uint64_t not_rank_1 = 0xFFFFFFFFFFFFFF00ULL;
  uint64_t not_rank_8 = 0x00FFFFFFFFFFFFFFULL;

  // right
  moves |= (pos & not_h_file) ? pos << 1 : 0ULL;
  // upper right
  moves |= (pos & not_h_file & not_rank_8) ? pos << 9 : 0ULL;
  // up
  moves |= (pos & not_rank_8) ? pos << 8 : 0ULL;
  // upper left
  moves |= (pos & not_a_file & not_rank_8) ? pos << 7 : 0ULL;
  // left
  moves |= (pos & not_a_file) ? pos >> 1 : 0ULL;
  // lower left
  moves |= (pos & not_a_file & not_rank_1) ? pos >> 9 : 0ULL;
  // down
  moves |= (pos & not_rank_1) ? pos >> 8 : 0ULL;
  // lower right
  moves |= (pos & not_h_file & not_rank_1) ? pos >> 7 : 0ULL;

  // TODO: Casteling
  // TODO: Cant move to squares which are visible by enemies

  return (moves & ~my_squares);
}