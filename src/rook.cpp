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
  // TODO
}