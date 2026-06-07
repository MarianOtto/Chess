#include "../include/knight.h"
#include "../include/board.h"
#include <cstdint>
#include <cstdio>
#include <sys/types.h>

Knight::Knight(Color color, Square* square, Board& board)
  : Figure(color, square, Type::Knight, board)
{
}

Figure* Knight::fromNotation(Color color, std::string notation, Board& board)
{
  std::unique_ptr<Figure> figure;
  figure =
    std::make_unique<Knight>(color, board.get_square_at(notation), board);
  board.get_square_at(notation)->set_figure(figure.get());
  board.addFigure(std::move(figure));
  return board.get_figure_on(notation);
}

uint64_t Knight::get_possible_moves()
{
  // TODO
}