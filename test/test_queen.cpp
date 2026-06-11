#include "../include/board.h"
#include "../include/catch.hpp"

TEST_CASE(
  "get_possible_moves: Queen in center should have row and file to move to ",
  "[queen][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Queen, "C6");

  uint64_t moves = 0ULL;
  moves |= 0x0404FB0404040404;
  moves |= 0x110A000A11204080;

  CHECK(board.get_possible_moves("C6") == moves);
}

// %%%%%%%%% Edge fields %%%%%%%%%%%%%
TEST_CASE("get_possible_moves: Queen on A File should not move left",
          "[queen][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Queen, "A7");

  uint64_t moves = 0ULL;
  moves |= 0x01FE010101010101;
  moves |= 0x0200020408102040;

  CHECK(board.get_possible_moves("A7") == moves);
}

TEST_CASE("get_possible_moves: Queen on H File should not move right",
          "[queen][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Queen, "H4");

  uint64_t moves = 0ULL;
  moves |= 0x808080807F808080;
  moves |= 0x0810204000402010;

  CHECK(board.get_possible_moves("H4") == moves);
}

TEST_CASE("get_possible_moves: Queen on Rank 1 should not move down",
          "[queen][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Queen, "C1");

  uint64_t moves = 0ULL;
  moves |= 0x04040404040404FB;
  moves |= 0x0000804020110A00;

  CHECK(board.get_possible_moves("C1") == moves);
}

TEST_CASE("get_possible_moves: Queen on Rank 8 should not move up",
          "[queen][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Queen, "D8");

  uint64_t moves = 0ULL;
  moves |= 0xF708080808080808;
  moves |= 0x0014224180000000;

  CHECK(board.get_possible_moves("D8") == moves);
}

TEST_CASE("get_possible_moves: Queen cant go on firendly square",
          "[queen][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Queen, "D5");

  board.addFigure(Color::White, Type::Pawn, "F7");
  board.addFigure(Color::White, Type::Pawn, "G2");
  board.addFigure(Color::White, Type::Pawn, "C6");

  board.addFigure(Color::White, Type::Pawn, "D7");
  board.addFigure(Color::White, Type::Pawn, "B5");
  board.addFigure(Color::White, Type::Pawn, "D1");

  uint64_t moves = 0ULL;
  moves |= 0x000008F408080800;
  moves |= 0x0000100014220100;

  CHECK(board.get_possible_moves("D5") == moves);
}

TEST_CASE("get_possible_moves: Queen can go on firendly square but stops",
          "[queen][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Queen, "D5");

  board.addFigure(Color::White, Type::Pawn, "D7");
  board.addFigure(Color::Black, Type::Pawn, "B5");
  board.addFigure(Color::Black, Type::Pawn, "D1");

  board.addFigure(Color::White, Type::Pawn, "F7");
  board.addFigure(Color::Black, Type::Pawn, "G2");
  board.addFigure(Color::Black, Type::Pawn, "C6");

  uint64_t moves = 0ULL;
  moves |= 0x000008F608080808;
  moves |= 0x0000140014224100;

  CHECK(board.get_possible_moves("D5") == moves);
}

// Castleing