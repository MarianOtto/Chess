#include "../include/queen.h"
#include "../include/board.h"
#include <cstdint>
#include <cstdio>
#include <sys/types.h>

Queen::Queen(Color color, Square* square, Board& board)
  : Figure(color, square, Type::Queen, board)
{
}

Figure* Queen::fromNotation(Color color, std::string notation, Board& board)
{
  std::unique_ptr<Figure> figure;
  figure = std::make_unique<Queen>(color, board.get_square_at(notation), board);
  board.get_square_at(notation)->set_figure(figure.get());
  board.addFigure(std::move(figure));
  return board.get_figure_on(notation);
}

uint64_t Queen::get_possible_moves()
{
  // TODO
}