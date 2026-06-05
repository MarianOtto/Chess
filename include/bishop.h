#include "../include/figure.h"

class Bishop : public Figure {
public:
  Bishop(Color color, Square *square, Board &board);

  std::vector<Square *> get_possible_moves() override;
  void move() override;
};