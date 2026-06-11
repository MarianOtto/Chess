#include "../include/board.h"
#include "../include/catch.hpp"

TEST_CASE(
  "get_possible_moves: King in center should have all squares available ",
  "[king][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::King, "C6");

  uint64_t moves = 0ULL;
  moves |= 0x000E0A0E00000000;

  CHECK(board.get_possible_moves("C6") == moves);
}

// %%%%%%%%% Edge fields %%%%%%%%%%%%%
TEST_CASE("get_possible_moves: King on A File should not move left",
          "[king][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::King, "A7");

  uint64_t moves = 0ULL;
  moves |= 0x0302030000000000;

  CHECK(board.get_possible_moves("A7") == moves);
}

TEST_CASE("get_possible_moves: King on H File should not move right",
          "[king][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::King, "H4");

  uint64_t moves = 0ULL;
  moves |= 0x0000C040C00000;

  CHECK(board.get_possible_moves("H4") == moves);
}

TEST_CASE("get_possible_moves: King on Rank 1 should not move down",
          "[king][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::King, "C1");

  uint64_t moves = 0ULL;
  moves |= 0x0000000000000E0A;

  CHECK(board.get_possible_moves("C1") == moves);
}

TEST_CASE("get_possible_moves: King on Rank 8 should not move up",
          "[king][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::King, "D8");

  uint64_t moves = 0ULL;
  moves |= 0x141C000000000000;

  CHECK(board.get_possible_moves("D8") == moves);
}

TEST_CASE("get_possible_moves: King should not move to friendly squares",
          "[king][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::King, "B4");

  board.addFigure(Color::White, Type::Pawn, "B3");
  board.addFigure(Color::White, Type::Pawn, "A3");
  board.addFigure(Color::White, Type::Pawn, "C4");

  uint64_t moves = 0ULL;
  moves |= 0x0000000701040000;

  CHECK(board.get_possible_moves("B4") == moves);
}

TEST_CASE("get_possible_moves: King should move to enemy squares",
          "[king][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::King, "B4");

  board.addFigure(Color::White, Type::Pawn, "B3");
  board.addFigure(Color::Black, Type::Pawn, "A3");
  board.addFigure(Color::Black, Type::Pawn, "C4");

  uint64_t moves = 0ULL;
  moves |= 0x0000000705050000;

  CHECK(board.get_possible_moves("B4") == moves);
}

// Castleing