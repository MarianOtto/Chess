#include "../include/figure.h"
#include <vector>

class King : public Figure
{
public:
  King(Color color, Square* square, Board& board);

  std::vector<Square*> get_possible_moves() override;
  void move() override;
};