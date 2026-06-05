#include "../include/bishop.h"

Bishop::Bishop(Color color, Square *square, Board &board)
    : Figure(color, square, Type::Bishop, board) {}

std::vector<Square *> Bishop::get_possible_moves() {
  // TODO
}

void Bishop::move() {
  // TODO
}