#include "../include/king.h"

uint64_t King::get_possible_moves(uint64_t pos,
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

  // right
  moves |= (pos & ~h_file) ? pos << 1 : 0ULL;
  // upper right
  moves |= (pos & ~h_file & ~rank_8) ? pos << 9 : 0ULL;
  // up
  moves |= (pos & ~rank_8) ? pos << 8 : 0ULL;
  // upper left
  moves |= (pos & ~a_file & ~rank_8) ? pos << 7 : 0ULL;
  // left
  moves |= (pos & ~a_file) ? pos >> 1 : 0ULL;
  // lower left
  moves |= (pos & ~a_file & ~rank_1) ? pos >> 9 : 0ULL;
  // down
  moves |= (pos & ~rank_1) ? pos >> 8 : 0ULL;
  // lower right
  moves |= (pos & ~h_file & ~rank_1) ? pos >> 7 : 0ULL;

  // TODO: Casteling
  // TODO: Cant move to squares which are visible by enemies

  return moves & ~friendly_squares;
}