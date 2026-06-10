#include "../include/board.h"
#include "../include/catch.hpp"
#include "../include/rook.h"
#include "../include/square.h"
#include "../include/testFigure.h"
#include "color.h"
#include <cstdint>
#include <string>

TEST_CASE(
  "get_possible_moves: Rook in center should have row and file to move to ",
  "[rook][get_possible_moves]")
{
  Board board;
  auto Rook = Rook::fromNotation(Color::White, "C6", board);

  uint64_t moves = 0ULL;
  moves |= 0x0404FB0404040404;

  CHECK(Rook->get_possible_moves() == moves);
}

// %%%%%%%%% Edge fields %%%%%%%%%%%%%
TEST_CASE("get_possible_moves: Rook on A File should not move left",
          "[rook][get_possible_moves]")
{
  Board board;
  auto Rook = Rook::fromNotation(Color::White, "A7", board);

  uint64_t moves = 0ULL;
  moves |= 0x01FE010101010101;

  CHECK(Rook->get_possible_moves() == moves);
}

TEST_CASE("get_possible_moves: Rook on H File should not move right",
          "[rook][get_possible_moves]")
{
  Board board;
  auto Rook = Rook::fromNotation(Color::White, "H4", board);

  uint64_t moves = 0ULL;
  moves |= 0x808080807F808080;

  CHECK(Rook->get_possible_moves() == moves);
}

TEST_CASE("get_possible_moves: Rook on Rank 1 should not move down",
          "[rook][get_possible_moves]")
{
  Board board;
  auto Rook = Rook::fromNotation(Color::White, "C1", board);

  uint64_t moves = 0ULL;
  moves |= 0x04040404040404FB;

  CHECK(Rook->get_possible_moves() == moves);
}

TEST_CASE("get_possible_moves: Rook on Rank 8 should not move up",
          "[rook][get_possible_moves]")
{
  Board board;
  auto Rook = Rook::fromNotation(Color::White, "D8", board);

  uint64_t moves = 0ULL;
  moves |= 0xF708080808080808;

  CHECK(Rook->get_possible_moves() == moves);
}

TEST_CASE("get_possible_moves: Rook cant go on firendly square",
          "[rook][get_possible_moves]")
{
  Board board;
  auto Rook = Rook::fromNotation(Color::White, "D5", board);

  auto fB3 = TestFigure::fromNotation(Color::White, "D7", board);
  auto fA3 = TestFigure::fromNotation(Color::White, "B5", board);
  auto fC4 = TestFigure::fromNotation(Color::White, "D1", board);

  uint64_t moves = 0ULL;
  moves |= 0x000008F408080800;

  CHECK(Rook->get_possible_moves() == moves);
}

TEST_CASE("get_possible_moves: Rook can go on firendly square but stops",
          "[rook][get_possible_moves]")
{
  Board board;
  auto Rook = Rook::fromNotation(Color::White, "D5", board);

  auto fB3 = TestFigure::fromNotation(Color::White, "D7", board);
  auto fA3 = TestFigure::fromNotation(Color::Black, "B5", board);
  auto fC4 = TestFigure::fromNotation(Color::Black, "D1", board);

  uint64_t moves = 0ULL;
  moves |= 0x000008F608080808;

  CHECK(Rook->get_possible_moves() == moves);
}

// Castleing