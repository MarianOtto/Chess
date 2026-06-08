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
  "get_possible_moves: White pawn, unmoved and clear path gets two squares",
  "[pawn][get_possible_moves]")
{
  Board board;
  auto Pawn = Pawn::fromNotation(Color::White, "A2", board);

  uint64_t moves = 0ULL;
  moves |= board.get_square_at("A3")->bit();
  moves |= board.get_square_at("A4")->bit();

  THEN("The Pawn should be able to just move two squares forward")
  {
    CHECK(Pawn->get_possible_moves() == moves);
  }
}

TEST_CASE("get_possible_moves: Black pawn, unmoved and clear path gets "
          "two squares",
          "[pawn][get_possible_moves]")
{
  Board board;
  auto Pawn = Pawn::fromNotation(Color::Black, "A7", board);

  uint64_t moves = 0ULL;
  moves |= board.get_square_at("A6")->bit();
  moves |= board.get_square_at("A5")->bit();

  THEN("The Pawn should be able to just move two squares forward")
  {
    CHECK(Pawn->get_possible_moves() == moves);
  }
}

TEST_CASE("get_possible_moves: White pawn diagonale capture",
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

  CHECK(Pawn1->get_possible_moves() == moves);
}

TEST_CASE("get_possible_moves: Black pawn diagonale capture",
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

  CHECK(Pawn1->get_possible_moves() == moves);
}

TEST_CASE("get_possible_moves: On last rank no possibles moves",
          "[pawn][get_possible_moves]")
{
  Board board;
  auto WhitePawn = Pawn::fromNotation(Color::White, "E8", board);
  auto BlackPawn = Pawn::fromNotation(Color::Black, "D1", board);

  uint64_t moves = 0ULL;

  CHECK(WhitePawn->get_possible_moves() == moves);
  CHECK(BlackPawn->get_possible_moves() == moves);
}

TEST_CASE("get_possible_moves: On left/right file no left/right capture",
          "[pawn][get_possible_moves]")
{
  Board board;
  auto PawnA3 = Pawn::fromNotation(Color::White, "A3", board); // DUT left file
  auto PawnH5 = Pawn::fromNotation(Color::White, "H5", board); // DUT right file
  // Captures across board
  auto PawnH4 = Pawn::fromNotation(Color::Black, "H4", board);
  auto PawnA4 = Pawn::fromNotation(Color::Black, "A6", board);

  uint64_t movesA3 = 0ULL;
  movesA3 |= 0x1000000;

  uint64_t movesH5 = 0ULL;
  movesH5 |= 0x800000000000;

  CHECK(PawnA3->get_possible_moves() == movesA3);
  CHECK(PawnH5->get_possible_moves() == movesH5);
}

TEST_CASE("get_possible_moves: Cant capture your own pieces",
          "[pawn][get_possible_moves]")
{
  Board board;
  // DUT
  auto PawnC3 = Pawn::fromNotation(Color::White, "C3", board);
  auto PawnE6 = Pawn::fromNotation(Color::Black, "E6", board);

  // Own diagonal pawn
  auto PawnD4 = Pawn::fromNotation(Color::White, "D4", board);
  auto PawnD5 = Pawn::fromNotation(Color::Black, "D5", board);

  uint64_t movesC3 = 0ULL;
  movesC3 |= 0x4000000;

  uint64_t movesE6 = 0ULL;
  movesE6 |= 0x1000000000;

  CHECK(PawnC3->get_possible_moves() == movesC3);
  CHECK(PawnE6->get_possible_moves() == movesE6);
}

TEST_CASE("get_possible_moves: Cant move forward if blocked",
          "[pawn][get_possible_moves]")
{
  Board board;
  // DUT
  auto PawnC3 = Pawn::fromNotation(Color::White, "C3", board);

  // Blocking pawn
  auto PawnC4 = Pawn::fromNotation(Color::White, "C4", board);

  uint64_t movesC3 = 0ULL;

  CHECK(PawnC3->get_possible_moves() == movesC3);
}
