#include "../include/board.h"
#include "../include/catch.hpp"

TEST_CASE("addFigure: Overloads apply the correct target square",
          "[board][addFigure]")
{
  GIVEN("An empty board")
  {
    Board board;

    WHEN("You add a black Figure")
    {
      board.addFigure(Color::Black, Type::Pawn, "D3");

      THEN("You should be able to access the Figure")
      {
        CHECK(board.get_white_bitmap() == 0);
        CHECK(board.get_black_bitmap() == 0x80000);
        CHECK(board.get_any_bitmap() == 0x80000);
      }
    }
  }
}

TEST_CASE("addFigure: Add multiple Figures", "[board][addFigure]")
{
  GIVEN("A black and a white Figure")
  {
    Board board;
    board.addFigure(Color::White, Type::Pawn, "A8");
    board.addFigure(Color::Black, Type::Pawn, "B3");

    WHEN("You add both Figures to the Board")
    {

      THEN("The bitmaps should update")
      {
        CHECK(board.get_white_bitmap() == 0x100000000000000);
        CHECK(board.get_black_bitmap() == 0x20000);
        CHECK(board.get_any_bitmap() == 0x100000000020000);
      }
    }
  }
}

TEST_CASE("Move Figure", "[board] [move]")
{
  GIVEN("A Figure on A3")
  {
    Board board;
  }
}