#include "../include/figure.h"

class Queen : public Figure
{
public:
  Queen(Color color, Square* square, Board& board);

  std::vector<Square*> get_possible_moves() override;
};