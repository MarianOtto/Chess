#include "../include/figure.h"

class Pawn : public Figure
{
public:
  Pawn(Color color, Square* square, Board& board);

  static Figure* fromNotation(Color color, std::string notation, Board& board);

  uint64_t get_possible_moves() override;
};