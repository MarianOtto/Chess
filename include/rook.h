#include "../include/figure.h"

class Rook : public Figure
{
public:
  Rook(Color color, Square* square, Board& board);

  static Figure* fromNotation(Color color, std::string notation, Board& board);

  uint64_t get_possible_moves() override;
};