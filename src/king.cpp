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
  // TODO
}