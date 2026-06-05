#include "../include/testFigure.h"
#include "../include/board.h"

std::unique_ptr<Figure> TestFigure::fromNotation(Color color,
                                                 std::string notation,
                                                 Board& board)
{
  return std::make_unique<TestFigure>(
    color, board.get_square_at(notation), board);
}