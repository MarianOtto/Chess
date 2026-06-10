#include "../include/bishop.h"
#include "../include/board.h"
#include "../include/catch.hpp"
#include "../include/square.h"
#include "../include/testFigure.h"
#include "color.h"
#include <cstdint>
#include <string>

TEST_CASE("get_possible_moves: Bishop in center has both diagonales to "
          "move to ",
          "[bishop][get_possible_moves]")
{
  Board board;
  auto Bishop = Bishop::fromNotation(Color::White, "C6", board);

  uint64_t moves = 0ULL;
  moves |= 0x110A000A11204080;
  CHECK(Bishop->get_possible_moves() == moves);
}

// %%%%%%%%% Edge fields %%%%%%%%%%%%%
TEST_CASE("get_possible_moves: Bishop on A File can not move west",
          "[bishop][get_possible_moves]")
{
  Board board;
  auto Bishop = Bishop::fromNotation(Color::White, "A7", board);

  uint64_t moves = 0ULL;
  moves |= 0x0200020408102040;

  CHECK(Bishop->get_possible_moves() == moves);
}

TEST_CASE("get_possible_moves: Bishop on H File can not move east",
          "[bishop][get_possible_moves]")
{
  Board board;
  auto Bishop = Bishop::fromNotation(Color::White, "H4", board);

  uint64_t moves = 0ULL;
  moves |= 0x0810204000402010;

  CHECK(Bishop->get_possible_moves() == moves);
}

TEST_CASE("get_possible_moves: Bishop on Rank 1 can not move down",
          "[bishop][get_possible_moves]")
{
  Board board;
  auto Bishop = Bishop::fromNotation(Color::White, "C1", board);

  uint64_t moves = 0ULL;
  moves |= 0x0000804020110A00;

  CHECK(Bishop->get_possible_moves() == moves);
}

TEST_CASE("get_possible_moves: Bishop on Rank 8 can not move up",
          "[bishop][get_possible_moves]")
{
  Board board;
  auto Bishop = Bishop::fromNotation(Color::White, "D8", board);

  uint64_t moves = 0ULL;
  moves |= 0x0014224180000000;

  CHECK(Bishop->get_possible_moves() == moves);
}

TEST_CASE("get_possible_moves: Bishop cant go on firendly square",
          "[bishop][get_possible_moves]")
{
  Board board;
  auto Bishop = Bishop::fromNotation(Color::White, "D5", board);

  auto fB3 = TestFigure::fromNotation(Color::White, "F7", board);
  auto fA3 = TestFigure::fromNotation(Color::White, "G2", board);
  auto fC4 = TestFigure::fromNotation(Color::White, "C6", board);

  uint64_t moves = 0ULL;
  moves |= 0x0000100014220100;

  CHECK(Bishop->get_possible_moves() == moves);
}

TEST_CASE("get_possible_moves: Bishop can go on firendly square but stops",
          "[bishop][get_possible_moves]")
{
  Board board;
  auto Bishop = Bishop::fromNotation(Color::White, "D5", board);

  auto fB3 = TestFigure::fromNotation(Color::White, "F7", board);
  auto fA3 = TestFigure::fromNotation(Color::Black, "G2", board);
  auto fC4 = TestFigure::fromNotation(Color::Black, "C6", board);

  uint64_t moves = 0ULL;
  moves |= 0x0000140014224100;

  CHECK(Bishop->get_possible_moves() == moves);
}