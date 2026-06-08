#include "../include/testFigure.h"
#include "../include/board.h"

Figure* TestFigure::fromNotation(Color color,
                                 std::string notation,
                                 Board& board)
{
  std::unique_ptr<Figure> figure;
  figure =
    std::make_unique<TestFigure>(color, board.get_square_at(notation), board);
  board.get_square_at(notation)->set_figure(figure.get());
  board.addFigure(std::move(figure));
  return board.get_figure_on(notation);
}