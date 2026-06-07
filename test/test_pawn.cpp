#include "../include/board.h"
#include "../include/catch.hpp"
#include "../include/pawn.h"
#include "../include/square.h"
#include "color.h"
#include "type.h"
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

TEST_CASE(
  "get_possible_squares: White pawn, unmoved and clear path gets two squares",
  "[pawn][get_possible_moves]")
{
  Board board;
  auto Pawn = Pawn::fromNotation(Color::White, "A2", board);

  uint64_t moves = 0ULL;
  moves |= board.get_square_at("A3")->bit();
  moves |= board.get_square_at("A4")->bit();

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
  auto Pawn = Pawn::fromNotation(Color::Black, "A7", board);

  uint64_t moves = 0ULL;
  moves |= board.get_square_at("A6")->bit();
  moves |= board.get_square_at("A5")->bit();

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
  auto Pawn1 = Pawn::fromNotation(Color::White, "B2", board);
  auto Pawn2 = Pawn::fromNotation(Color::Black, "A3", board);
  auto Pawn3 = Pawn::fromNotation(Color::Black, "C3", board);

  uint64_t moves = 0ULL;
  moves |= board.get_square_at("A3")->bit();
  moves |= board.get_square_at("C3")->bit();
  moves |= board.get_square_at("B3")->bit();
  moves |= board.get_square_at("B4")->bit();

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
  auto Pawn1 = Pawn::fromNotation(Color::Black, "G7", board);
  auto Pawn2 = Pawn::fromNotation(Color::White, "F6", board);
  auto Pawn3 = Pawn::fromNotation(Color::White, "H6", board);

  uint64_t moves = 0ULL;
  moves |= board.get_square_at("G6")->bit();
  moves |= board.get_square_at("G5")->bit();
  moves |= board.get_square_at("F6")->bit();
  moves |= board.get_square_at("H6")->bit();

  REQUIRE(Pawn1->get_has_moved() == 0);
  THEN("The Pawn should be able to just move two squares forward")
  {
    CHECK(Pawn1->get_possible_moves() == moves);
  }
}

// TODO: At the last rank you get no possible moves.
// TODO: At left/right file you cant capture left/right.
// TODO: Cant capture your own
// TODO: Cant go forward if blocked
