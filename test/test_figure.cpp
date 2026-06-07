#include "../include/bishop.h"
#include "../include/board.h"
#include "../include/catch.hpp"
#include "../include/king.h"
#include "../include/knight.h"
#include "../include/pawn.h"
#include "../include/queen.h"
#include "../include/rook.h"
#include "../include/testFigure.h"

TEST_CASE("Create Figure", "[figure]")
{
  Board board;

  WHEN("You construct a white Figure on Square 8")
  {
    TestFigure figure(Color::White, board.get_square_at(8), board);

    THEN("All the members should be set")
    {
      CHECK(figure.get_color() == Color::White);
      CHECK(figure.get_square() == board.get_square_at(8));
      CHECK(figure.get_has_moved() == 0);
      CHECK(figure.get_opposite_color() == Color::Black);
      CHECK(figure.get_type() == Type::None);
    }
  }

  WHEN("You construct a Figure with an invalid color")
  {
    THEN("An exception should be thrown")
    {
      CHECK_THROWS(TestFigure(Color::Any, board.get_square_at(8), board));
    }
  }
}

TEST_CASE("White has opposite color black", "[figure]")
{
  Board board;
  TestFigure figure(Color::Black, board.get_square_at("H3"), board);

  CHECK(figure.get_color() == Color::Black);
  CHECK(figure.get_opposite_color() == Color::White);
}

TEST_CASE("You construct a white Figure", "[figure]")
{
  Board board;
  TestFigure figure(Color::White, board.get_square_at("H3"), board);

  CHECK(figure.get_color() == Color::White);
  CHECK(figure.get_opposite_color() == Color::Black);
}

TEST_CASE("fromNotation: Overloads behave consistantly", "[figure]")
{
  Board board;

  WHEN("You create a Figure from Notation")
  {
    auto figure = TestFigure::fromNotation(Color::Black, "B1", board);

    THEN("The square of the figure should be add to the square")
    {
      CHECK(figure->get_square() == board.get_square_at("B1"));
    }
  }
}

TEST_CASE("Test setters", "[figure]")
{
  GIVEN("A white figure on C3")
  {
    Board board;
    auto figure = TestFigure::fromNotation(Color::White, "C3", board);

    REQUIRE(figure->get_square() == board.get_square_at("C3"));
    REQUIRE(figure->get_has_moved() == 0);
    REQUIRE(figure->get_type() == Type::None);

    WHEN("You set different members")
    {
      figure->set_square(board.get_square_at(31));
      figure->set_has_moved(1);
      figure->set_type(Type::King);

      THEN("The all the members should change")
      {
        CHECK(figure->get_square() == board.get_square_at(31));
        CHECK(figure->get_has_moved() == 1);
        CHECK(figure->get_type() == Type::King);
      }
    }
  }
}