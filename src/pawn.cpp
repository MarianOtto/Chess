#include "../include/pawn.h"
#include "../include/board.h"
#include <vector>

Pawn::Pawn(Color color, Square* square, Board& board)
  : Figure(color, square, Type::Pawn, board)
{
}

std::vector<Square*> Pawn::get_possible_moves()
{
  std::vector<Square*> possible_moves;
  if (_color == Color::White) {
    if (_has_moved == 0) {
      if (_board.get_square_at(_square->index() + 16)) {
      }
    }
  } else {
    // Implement logic for black pawn moves
  }
}