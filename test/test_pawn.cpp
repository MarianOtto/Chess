#include "../include/board.h"
#include "../include/catch.hpp"
#include "../include/pawn.h"
#include "../include/square.h"
#include "color.h"
#include "type.h"
#include <memory>
#include <string>
#include <vector>

TEST_CASE(
  "get_possible_squares: White pawn, unmoved and clear path gets two squares",
  "[pawn][get_possible_moves]")
{
  Board board;
  auto Pawn = Pawn::fromNotation(Color::White, "A2", Type::Pawn, board);

  std::vector<Square*> moves;
  moves.push_back(board.get_square_at("A3"));
  moves.push_back(board.get_square_at("A4"));

  REQUIRE(Pawn->get_has_moved() == 0);
  THEN("The Pawn should be able to just move two squares forward")
  {
    CHECK(Pawn->get_possible_moves() == moves);
  }
}

TEST_CASE("get_possible_squares: Black pawn, unmoved and clear path gets "
          "two squares",
          "[pawn][get_possible_moves]")
{
  Board board;
  auto Pawn = Pawn::fromNotation(Color::Black, "A7", Type::Pawn, board);

  std::vector<Square*> moves;
  moves.push_back(board.get_square_at("A6"));
  moves.push_back(board.get_square_at("A5"));

  REQUIRE(Pawn->get_has_moved() == 0);
  THEN("The Pawn should be able to just move two squares forward")
  {
    CHECK(Pawn->get_possible_moves() == moves);
  }
}

TEST_CASE("get_possible_squares: White pawn diagonale capture",
          "[pawn][get_possible_moves]")
{
  Board board;
  auto Pawn1 = Pawn::fromNotation(Color::White, "A2", Type::Pawn, board);
  auto Pawn2 = Pawn::fromNotation(Color::Black, "B1", Type::Pawn, board);
  auto Pawn3 = Pawn::fromNotation(Color::Black, "B3", Type::Pawn, board);

  std::vector<Square*> moves;
  moves.push_back(board.get_square_at("B1"));
  moves.push_back(board.get_square_at("B3"));
  moves.push_back(board.get_square_at("A3"));
  moves.push_back(board.get_square_at("A4"));

  REQUIRE(Pawn1->get_has_moved() == 0);
  THEN("The Pawn should be able to just move two squares forward")
  {
    CHECK(Pawn1->get_possible_moves() == moves);
  }
}

TEST_CASE("get_possible_squares: Black pawn diagonale capture",
          "[pawn][get_possible_moves]")
{
  Board board;
  auto Pawn1 = Pawn::fromNotation(Color::Black, "G7", Type::Pawn, board);
  auto Pawn2 = Pawn::fromNotation(Color::White, "F6", Type::Pawn, board);
  auto Pawn3 = Pawn::fromNotation(Color::White, "F8", Type::Pawn, board);

  std::vector<Square*> moves;
  moves.push_back(board.get_square_at("G6"));
  moves.push_back(board.get_square_at("G5"));
  moves.push_back(board.get_square_at("F6"));
  moves.push_back(board.get_square_at("F8"));

  REQUIRE(Pawn1->get_has_moved() == 0);
  THEN("The Pawn should be able to just move two squares forward")
  {
    CHECK(Pawn1->get_possible_moves() == moves);
  }
}