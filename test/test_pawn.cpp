#include "../include/board.h"
#include "../include/catch.hpp"

TEST_CASE(
  "get_possible_moves: White pawn, unmoved and clear path gets two squares",
  "[pawn][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Pawn, "A2");

  uint64_t moves = 0ULL;
  moves |= 0x0000000001010000;

  THEN("The Pawn should be able to just move two squares forward")
  {
    CHECK(board.get_possible_moves("A2") == moves);
  }
}

TEST_CASE("get_possible_moves: Black pawn, unmoved and clear path gets "
          "two squares",
          "[pawn][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::Black, Type::Pawn, "A7");

  uint64_t moves = 0ULL;
  moves |= 0x0000010100000000;

  THEN("The Pawn should be able to just move two squares forward")
  {
    CHECK(board.get_possible_moves("A7") == moves);
  }
}

TEST_CASE("get_possible_moves: White pawn diagonale capture",
          "[pawn][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Pawn, "B2");

  board.addFigure(Color::Black, Type::Pawn, "A3");
  board.addFigure(Color::Black, Type::Pawn, "C3");

  uint64_t moves = 0ULL;
  moves |= 0x0000000002070000;

  CHECK(board.get_possible_moves("B2") == moves);
}

TEST_CASE("get_possible_moves: Black pawn diagonale capture",
          "[pawn][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::Black, Type::Pawn, "G7");

  board.addFigure(Color::White, Type::Pawn, "F6");
  board.addFigure(Color::White, Type::Pawn, "H6");

  uint64_t moves = 0ULL;
  moves |= 0x00E04000000000;

  CHECK(board.get_possible_moves("G7") == moves);
}

TEST_CASE("get_possible_moves: On last rank no possibles moves",
          "[pawn][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Pawn, "E8");
  board.addFigure(Color::Black, Type::Pawn, "D1");

  uint64_t moves = 0ULL;

  CHECK(board.get_possible_moves("E8") == moves);
  CHECK(board.get_possible_moves("D1") == moves);
}

TEST_CASE("get_possible_moves: On left/right file no left/right capture",
          "[pawn][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Pawn, "A3"); // DUT left file
  board.addFigure(Color::White, Type::Pawn, "H5"); // DUT right file
  // Captures across board
  board.addFigure(Color::Black, Type::Pawn, "H4");
  board.addFigure(Color::Black, Type::Pawn, "A6");

  uint64_t movesA3 = 0ULL;
  movesA3 |= 0x1000000;

  uint64_t movesH5 = 0ULL;
  movesH5 |= 0x800000000000;

  CHECK(board.get_possible_moves("A3") == movesA3);
  CHECK(board.get_possible_moves("H5") == movesH5);
}

TEST_CASE("get_possible_moves: Cant capture your own pieces",
          "[pawn][get_possible_moves]")
{
  Board board;
  // DUT
  board.addFigure(Color::White, Type::Pawn, "C3");
  board.addFigure(Color::Black, Type::Pawn, "E6");

  // Own diagonal pawn
  board.addFigure(Color::White, Type::Pawn, "D4");
  board.addFigure(Color::Black, Type::Pawn, "D5");

  uint64_t movesC3 = 0ULL;
  movesC3 |= 0x4000000;

  uint64_t movesE6 = 0ULL;
  movesE6 |= 0x1000000000;

  CHECK(board.get_possible_moves("C3") == movesC3);
  CHECK(board.get_possible_moves("E6") == movesE6);
}

TEST_CASE("get_possible_moves: Cant move forward if blocked",
          "[pawn][get_possible_moves]")
{
  Board board;
  // DUT
  board.addFigure(Color::White, Type::Pawn, "C3");

  // Blocking pawn
  board.addFigure(Color::White, Type::Pawn, "C4");

  uint64_t movesC3 = 0ULL;

  CHECK(board.get_possible_moves("C3") == movesC3);
}
