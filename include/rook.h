#include "../include/figure.h"

class Rook : public Figure
{
public:
  Rook(Color color, Square* square, Board& board);

  std::vector<Square*> get_possible_moves() override;
  void move() override;
};