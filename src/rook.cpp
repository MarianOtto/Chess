#include "../include/rook.h"

Rook::Rook(Color color, Square* square, Board& board)
  : Figure(color, square, Type::Rook, board)
{
}

std::vector<Square*> Rook::get_possible_moves()
{
  // TODO
}