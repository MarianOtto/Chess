#include "../include/board.h"
#include "../include/catch.hpp"
#include "../include/king.h"
#include "../include/square.h"
#include "../include/testFigure.h"
#include "color.h"
#include <cstdint>
#include <string>

TEST_CASE(
  "get_possible_moves: King in center should have all squares available ",
  "[king][get_possible_moves]")
{
  Board board;
  auto King = King::fromNotation(Color::White, "C6", board);

  uint64_t moves = 0ULL;
  moves |= 0x000E0A0E00000000;

  CHECK(King->get_possible_moves() == moves);
}

// %%%%%%%%% Edge fields %%%%%%%%%%%%%
TEST_CASE("get_possible_moves: King on A File should not move left",
          "[king][get_possible_moves]")
{
  Board board;
  auto King = King::fromNotation(Color::White, "A7", board);

  uint64_t moves = 0ULL;
  moves |= 0x0302030000000000;

  CHECK(King->get_possible_moves() == moves);
}

TEST_CASE("get_possible_moves: King on H File should not move right",
          "[king][get_possible_moves]")
{
  Board board;
  auto King = King::fromNotation(Color::White, "H4", board);

  uint64_t moves = 0ULL;
  moves |= 0x0000C040C00000;

  CHECK(King->get_possible_moves() == moves);
}

TEST_CASE("get_possible_moves: King on Rank 1 should not move down",
          "[king][get_possible_moves]")
{
  Board board;
  auto King = King::fromNotation(Color::White, "C1", board);

  uint64_t moves = 0ULL;
  moves |= 0x0000000000000E0A;

  CHECK(King->get_possible_moves() == moves);
}

TEST_CASE("get_possible_moves: King on Rank 8 should not move up",
          "[king][get_possible_moves]")
{
  Board board;
  auto King = King::fromNotation(Color::White, "D8", board);

  uint64_t moves = 0ULL;
  moves |= 0x141C000000000000;

  CHECK(King->get_possible_moves() == moves);
}

TEST_CASE("get_possible_moves: King should not move to friendly squares",
          "[king][get_possible_moves]")
{
  Board board;
  auto King = King::fromNotation(Color::White, "B4", board);

  auto fB3 = TestFigure::fromNotation(Color::White, "B3", board);
  auto fA3 = TestFigure::fromNotation(Color::White, "A3", board);
  auto fC4 = TestFigure::fromNotation(Color::White, "C4", board);

  uint64_t moves = 0ULL;
  moves |= 0x0000000701040000;

  CHECK(King->get_possible_moves() == moves);
}

TEST_CASE("get_possible_moves: King should move to enemy squares",
          "[king][get_possible_moves]")
{
  Board board;
  auto King = King::fromNotation(Color::White, "B4", board);

  auto fB3 = TestFigure::fromNotation(Color::White, "B3", board);
  auto fA3 = TestFigure::fromNotation(Color::Black, "A3", board);
  auto fC4 = TestFigure::fromNotation(Color::Black, "C4", board);

  uint64_t moves = 0ULL;
  moves |= 0x0000000705050000;

  CHECK(King->get_possible_moves() == moves);
}

// Castleing