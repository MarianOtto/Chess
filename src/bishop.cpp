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
  // TODO
}