#include "../include/rook.h"

uint64_t Rook::get_possible_moves(uint64_t pos,
                                  bool is_white,
                                  uint64_t friendly_squares,
                                  uint64_t enemy_squares,
                                  uint64_t free_squares)
{
  uint64_t moves = 0ULL;

  uint64_t a_file = 0x0101010101010101ULL;
  uint64_t h_file = 0x8080808080808080ULL;
  uint64_t rank_1 = 0x00000000000000FFULL;
  uint64_t rank_8 = 0xFF00000000000000ULL;

  uint64_t square = pos;
  // North
  for (int i = 1; i <= 7; i++) {
    if (square & rank_8)
      break;
    square <<= 8;
    if (square & free_squares) {
      moves |= square;
      continue;
    }
    moves |= (square & enemy_squares) ? square : 0ULL;
    break;
  }

  // East
  square = pos;
  for (int i = 1; i <= 7; i++) {
    if (square & h_file)
      break;
    square <<= 1;
    if (square & free_squares) {
      moves |= square;
      continue;
    }
    moves |= (square & enemy_squares) ? square : 0ULL;
    break;
  }

  // South
  square = pos;
  for (int i = 1; i <= 7; i++) {
    if (square & rank_1)
      break;
    square >>= 8;
    if (square & free_squares) {
      moves |= square;
      continue;
    }
    moves |= (square & enemy_squares) ? square : 0ULL;
    break;
  }

  // West
  square = pos;
  for (int i = 1; i <= 7; i++) {
    if (square & a_file)
      break;
    square >>= 1;
    if (square & free_squares) {
      moves |= square;
      continue;
    }
    moves |= (square & enemy_squares) ? square : 0ULL;
    break;
  }
  // TODO: Castleing

  return moves;
}