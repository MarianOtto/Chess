#include "../include/bishop.h"

Bishop::Bishop(Color color, Square *square, Board &board)
    : Figure(color, square, Type::Bishop, board) {}

<<<<<<< HEAD
std::vector<Square *> Bishop::get_possible_moves() {
  // TODO
}

void Bishop::move() {
=======
std::vector<Square*> Bishop::get_possible_moves()
{
>>>>>>> 68f0376 (Remove move method)
  // TODO
}