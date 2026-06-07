#include "figure.h"

class TestFigure : public Figure
{
public:
  TestFigure(Color color, Square* square, Board& board)
    : Figure(color, square, Type::None, board)
  {
  }

  static std::unique_ptr<Figure> fromNotation(Color color,
                                              std::string notation,
                                              Board& board);

  uint64_t get_possible_moves() override { return {}; }
};