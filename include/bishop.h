#include "../include/figure.h"

class Bishop : public Figure {
public:
  Bishop(Color color, Square *square, Board &board);

<<<<<<< HEAD
  std::vector<Square *> get_possible_moves() override;
  void move() override;
=======
  std::vector<Square*> get_possible_moves() override;
>>>>>>> 68f0376 (Remove move method)
};