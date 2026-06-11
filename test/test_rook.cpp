#include "../include/board.h"
#include "../include/catch.hpp"

TEST_CASE(
  "get_possible_moves: Rook in center should have row and file to move to ",
  "[rook][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Rook, "C6");

  uint64_t moves = 0ULL;
  moves |= 0x0404FB0404040404;

  CHECK(board.get_possible_moves("C6") == moves);
}

// %%%%%%%%% Edge fields %%%%%%%%%%%%%
TEST_CASE("get_possible_moves: Rook on A File should not move left",
          "[rook][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Rook, "A7");

  uint64_t moves = 0ULL;
  moves |= 0x01FE010101010101;

  CHECK(board.get_possible_moves("A7") == moves);
}

TEST_CASE("get_possible_moves: Rook on H File should not move right",
          "[rook][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Rook, "H4");

  uint64_t moves = 0ULL;
  moves |= 0x808080807F808080;

  CHECK(board.get_possible_moves("H4") == moves);
}

TEST_CASE("get_possible_moves: Rook on Rank 1 should not move down",
          "[rook][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Rook, "C1");

  uint64_t moves = 0ULL;
  moves |= 0x04040404040404FB;

  CHECK(board.get_possible_moves("C1") == moves);
}

TEST_CASE("get_possible_moves: Rook on Rank 8 should not move up",
          "[rook][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Rook, "D8");

  uint64_t moves = 0ULL;
  moves |= 0xF708080808080808;

  CHECK(board.get_possible_moves("D8") == moves);
}

TEST_CASE("get_possible_moves: Rook cant go on firendly square",
          "[rook][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Rook, "D5");

  board.addFigure(Color::White, Type::Pawn, "D7");
  board.addFigure(Color::White, Type::Pawn, "B5");
  board.addFigure(Color::White, Type::Pawn, "D1");

  uint64_t moves = 0ULL;
  moves |= 0x000008F408080800;

  CHECK(board.get_possible_moves("D5") == moves);
}

TEST_CASE("get_possible_moves: Rook can go on firendly square but stops",
          "[rook][get_possible_moves]")
{
  Board board;
  board.addFigure(Color::White, Type::Rook, "D5");

  board.addFigure(Color::White, Type::Pawn, "D7");
  board.addFigure(Color::Black, Type::Pawn, "B5");
  board.addFigure(Color::Black, Type::Pawn, "D1");

  uint64_t moves = 0ULL;
  moves |= 0x000008F608080808;

  CHECK(board.get_possible_moves("D5") == moves);
}

// Castleing