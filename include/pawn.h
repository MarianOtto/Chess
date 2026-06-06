#include "../include/figure.h"

class Pawn : public Figure
{
public:
  Pawn(Color color, Square* square, Board& board);

  std::vector<Square*> get_possible_moves() override;
};