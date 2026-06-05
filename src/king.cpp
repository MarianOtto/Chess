#include "../include/king.h"
#include <vector>

King::King(Color color, Square* square, Board& board)
  : Figure(color, square, Type::King, board)
{
}

std::vector<Square*> King::get_possible_moves()
{
  // TODO
}

void King::move()
{
  // TODO
}