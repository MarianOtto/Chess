#include "../include/queen.h"

Queen::Queen(Color color, Square* square, Board& board)
  : Figure(color, square, Type::Queen, board)
{
}

std::vector<Square*> Queen::get_possible_moves()
{
  // TODO
}

void Queen::move()
{
  // TODO
}
