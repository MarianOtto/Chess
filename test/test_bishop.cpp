#include "../include/board.h"
#include "../include/catch.hpp"

TEST_CASE("get_possible_moves: Bishop in center has both diagonales to "
          "move to ",
          "[bishop][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Bishop, "C6");

  uint64_t moves = 0ULL;
  moves |= 0x110A000A11204080;
  CHECK(board.get_possible_moves("C6") == moves);
}

// %%%%%%%%% Edge fields %%%%%%%%%%%%%
TEST_CASE("get_possible_moves: Bishop on A File can not move west",
          "[bishop][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Bishop, "A7");

  uint64_t moves = 0ULL;
  moves |= 0x0200020408102040;

  CHECK(board.get_possible_moves("A7") == moves);
}

TEST_CASE("get_possible_moves: Bishop on H File can not move east",
          "[bishop][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Bishop, "H4");

  uint64_t moves = 0ULL;
  moves |= 0x0810204000402010;

  CHECK(board.get_possible_moves("H4") == moves);
}

TEST_CASE("get_possible_moves: Bishop on Rank 1 can not move down",
          "[bishop][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Bishop, "C1");

  uint64_t moves = 0ULL;
  moves |= 0x0000804020110A00;

  CHECK(board.get_possible_moves("C1") == moves);
}

TEST_CASE("get_possible_moves: Bishop on Rank 8 can not move up",
          "[bishop][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Bishop, "D8");

  uint64_t moves = 0ULL;
  moves |= 0x0014224180000000;

  CHECK(board.get_possible_moves("D8") == moves);
}

TEST_CASE("get_possible_moves: Bishop cant go on firendly square",
          "[bishop][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Bishop, "D5");

  board.addFigure(Color::White, Type::Pawn, "F7");
  board.addFigure(Color::White, Type::Pawn, "G2");
  board.addFigure(Color::White, Type::Pawn, "C6");

  uint64_t moves = 0ULL;
  moves |= 0x0000100014220100;

  CHECK(board.get_possible_moves("D5") == moves);
}

TEST_CASE("get_possible_moves: Bishop can go on firendly square but stops",
          "[bishop][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Bishop, "D5");

  board.addFigure(Color::White, Type::Pawn, "F7");
  board.addFigure(Color::Black, Type::Pawn, "G2");
  board.addFigure(Color::Black, Type::Pawn, "C6");

  uint64_t moves = 0ULL;
  moves |= 0x0000140014224100;

  CHECK(board.get_possible_moves("D5") == moves);
}