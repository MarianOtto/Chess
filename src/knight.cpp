#include "../include/knight.h"

Knight::Knight(Color color, Square* square, Board& board)
  : Figure(color, square, Type::Knight, board)
{
}

std::vector<Square*> Knight::get_possible_moves()
{
  // TODO
}

void Knight::move()
{
  // TODO
}