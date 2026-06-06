#include "../include/figure.h"

class Knight : public Figure
{
public:
  Knight(Color color, Square* square, Board& board);

  std::vector<Square*> get_possible_moves() override;
};