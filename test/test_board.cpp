#include "../include/board.h"
#include "../include/catch.hpp"
#include "../include/testFigure.h"
#include <utility>

TEST_CASE("Create Board", "[board]")
{
  Board board;
  int idx = GENERATE(range(0, 64));
  CHECK(board.get_square_at(idx)->index() == idx);
}

TEST_CASE("addFigure: Overloads apply the correct target square",
          "[board][addFigure]")
{
  GIVEN("An empty board")
  {
    Board board;

    WHEN("You add a black Figure")
    {
      auto figure = TestFigure::fromNotation(Color::Black, "D3", board);
      board.addFigure(std::move(figure));

      THEN("You should be able to access the Figure")
      {
        CHECK(board.get_figure_on("D3")->get_opposite_color() == Color::White);

        CHECK(board.get_white_bitmap() == 0);
        CHECK(board.get_black_bitmap() == 0x80000);
        CHECK(board.get_any_bitmap() == 0x80000);
      }
    }

    WHEN("You add a white Figure with string parameter")
    {
      auto figure = TestFigure::fromNotation(Color::White, "A4", board);
      board.addFigure(std::move(figure), "B5");

      THEN("The Figure should be on B5")
      {
        CHECK(board.get_square_at("B5")->notation() == "B5");

        CHECK(board.get_white_bitmap() == 0x200000000);
        CHECK(board.get_black_bitmap() == 0);
        CHECK(board.get_any_bitmap() == 0x200000000);
      }
    }

    WHEN("You add a white Figure with index parameter")
    {
      auto figure = TestFigure::fromNotation(Color::White, "A4", board);
      board.addFigure(std::move(figure), board.get_square_at(18));

      THEN("The Figure should be accessible by the target Sqaure")
      {
        CHECK(board.get_square_at(18)->index() == 18);
      }
    }
  }
}

TEST_CASE("addFigure: Add multiple Figures", "[board][addFigure]")
{
  GIVEN("A black and a white Figure")
  {
    Board board;
    auto figureA = TestFigure::fromNotation(Color::Black, "A8", board);
    auto figureB = TestFigure::fromNotation(Color::White, "B3", board);

    WHEN("You add both Figures to the Board")
    {
      board.addFigure(std::move(figureA));
      board.addFigure(std::move(figureB));

      THEN("The bitmaps should update")
      {
        CHECK(board.get_black_bitmap() == 0x100000000000000);
        CHECK(board.get_white_bitmap() == 0x20000);
        CHECK(board.get_any_bitmap() == 0x100000000020000);
      }
    }
  }
}

TEST_CASE("Board accessors return consistent Figure pointer", "[board]")
{
  GIVEN("A Board with a single Figure on A4")
  {
    Board board;
    auto figure = TestFigure::fromNotation(Color::White, "A4", board);
    Figure* figptr = figure.get();

    WHEN("You add the Figure to the Board")
    {
      board.addFigure(std::move(figure));

      THEN("All accessors return the same pointer")
      {
        CHECK(board.get_figure_on("A4") == figptr);
        CHECK(board.get_figure_on(24) == figptr);
        CHECK(board.get_squares()->at(24)->get_figure() == figptr);
      }
    }
  }
}

TEST_CASE("occupied_by: Overload varients should behave consistently",
          "[board][occupied_by]")
{
  GIVEN("A board with two figures on it")
  {
    Board board;
    auto whiteFigure = TestFigure::fromNotation(Color::White, "B3", board);
    auto blackFigure = TestFigure::fromNotation(Color::Black, "G4", board);

    board.addFigure(std::move(whiteFigure));
    board.addFigure(std::move(blackFigure));

    WHEN("You check for all combinations")
    {

      THEN("Occupied_by(string) should give the same results as the "
           "Square::occupied_by")
      {
        // Empty Square
        CHECK(board.occupied_by(Color::Black, "A1") == 0);
        CHECK(board.occupied_by(Color::White, "A1") == 0);
        CHECK(board.occupied_by(Color::Any, "A1") == 0);
        // White Square
        CHECK(board.occupied_by(Color::Black, "B3") == 0);
        CHECK(board.occupied_by(Color::White, "B3") == 1);
        CHECK(board.occupied_by(Color::Any, "B3") == 1);
        // Black Square
        CHECK(board.occupied_by(Color::Black, "G4") == 1);
        CHECK(board.occupied_by(Color::White, "G4") == 0);
        CHECK(board.occupied_by(Color::Any, "G4") == 1);
      }

      THEN("Occupied_by(index) should give the same results as the "
           "Square::occupied_by")
      {
        // Empty Square
        CHECK(board.occupied_by(Color::Black, 0) == 0);
        CHECK(board.occupied_by(Color::White, 0) == 0);
        CHECK(board.occupied_by(Color::Any, 0) == 0);
        // White Square
        CHECK(board.occupied_by(Color::Black, 17) == 0);
        CHECK(board.occupied_by(Color::White, 17) == 1);
        CHECK(board.occupied_by(Color::Any, 17) == 1);
        // Black Square
        CHECK(board.occupied_by(Color::Black, 30) == 1);
        CHECK(board.occupied_by(Color::White, 30) == 0);
        CHECK(board.occupied_by(Color::Any, 30) == 1);
      }
    }
  }
}

TEST_CASE("Move Figure", "[board] [move]")
{
  GIVEN("A Figure on A3")
  {
    Board board;
    auto figure = TestFigure::fromNotation(Color::White, "A3", board);

    // WHEN("You move the Figure to D3"){
    //     board.move("A3", "D3");

    //     THEN("The Figure square index should change"){
    //         CHECK(figure->get_square().notation() == "D3");
    //     }
    //     THEN("The Figure should belong to the D3 (Index 26) of the Board"){
    //         CHECK(board.get_figure_at(26) == figure.get());
    //     }
    // }
  }
}