#include "../include/bishop.h"

uint64_t Bishop::get_possible_moves(uint64_t pos,
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

  // North East
  for (int i = 1; i <= 7; i++) {
    if (square & (rank_8 | h_file)) // Check Edge
      break;
    square <<= 9;
    if (square & free_squares) {
      moves |= square;
      continue;
    }
    moves |= (square & enemy_squares) ? square : 0ULL;
    break;
  }

  // South East
  square = pos;
  for (int i = 1; i <= 7; i++) {
    if (square & (rank_1 | h_file)) // Check Edge
      break;
    square >>= 7;
    if (square & free_squares) {
      moves |= square;
      continue;
    }
    moves |= (square & enemy_squares) ? square : 0ULL;
    break;
  }

  // South West
  square = pos;
  for (int i = 1; i <= 7; i++) {
    if (square & (rank_1 | a_file)) // Check Edge
      break;
    square >>= 9;
    if (square & free_squares) {
      moves |= square;
      continue;
    }
    moves |= (square & enemy_squares) ? square : 0ULL;
    break;
  }

  // North West
  square = pos;
  for (int i = 1; i <= 7; i++) {
    if (square & (rank_8 | a_file)) // Check Edge
      break;
    square <<= 7;
    if (square & free_squares) {
      moves |= square;
      continue;
    }
    moves |= (square & enemy_squares) ? square : 0ULL;
    break;
  }

  return moves;
}