#include "../include/board.h"
#include "../include/catch.hpp"

TEST_CASE("get_possible_moves: Knight in center has 8 squares to "
          "move to ",
          "[knight][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Knight, "C6");

  uint64_t moves = 0ULL;
  moves |= 0x0A1100110A000000;
  CHECK(board.get_possible_moves("C6") == moves);
}

// %%%%%%%%% Edge fields %%%%%%%%%%%%%
TEST_CASE("get_possible_moves", "[knight][get_possible_moves]")
{
  Board board;
  SECTION("A7")
  {
    board.addFigure(Color::White, Type::Knight, "A7");

    uint64_t moves = 0ULL;
    moves |= 0x0400040200000000;

    CHECK(board.get_possible_moves("A7") == moves);
  }

  SECTION("H4")
  {
    board.addFigure(Color::White, Type::Knight, "H4");

    uint64_t moves = 0ULL;
    moves |= 0x0000402000204000;

    CHECK(board.get_possible_moves("H4") == moves);
  }

  SECTION("C1")
  {
    board.addFigure(Color::White, Type::Knight, "C1");

    uint64_t moves = 0ULL;
    moves |= 0x0A1100;

    CHECK(board.get_possible_moves("C1") == moves);
  }

  SECTION("D8")
  {
    board.addFigure(Color::White, Type::Knight, "D8");

    uint64_t moves = 0ULL;
    moves |= 0x0022140000000000;

    CHECK(board.get_possible_moves("D8") == moves);
  }
}

TEST_CASE("get_possible_moves: Knight cant go on firendly square",
          "[knight][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Knight, "D5");

  board.addFigure(Color::White, Type::Pawn, "F6");
  board.addFigure(Color::White, Type::Pawn, "E3");
  board.addFigure(Color::White, Type::Pawn, "B4");

  uint64_t moves = 0ULL;
  moves |= 0x0014020020040000;

  CHECK(board.get_possible_moves("D5") == moves);
}

TEST_CASE("get_possible_moves: Knight can go on firendly square but stops",
          "[knight][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Knight, "D5");

  board.addFigure(Color::White, Type::Pawn, "F6");
  board.addFigure(Color::Black, Type::Pawn, "E3");
  board.addFigure(Color::Black, Type::Pawn, "B4");

  uint64_t moves = 0ULL;
  moves |= 0x0014020022140000;

  CHECK(board.get_possible_moves("D5") == moves);
}