#include "../include/knight.h"

uint64_t Knight::get_possible_moves(uint64_t pos,
                                    bool is_white,
                                    uint64_t friendly_squares,
                                    uint64_t enemy_squares,
                                    uint64_t free_squares)
{
  uint64_t moves = 0ULL;

  uint64_t a_file = 0x0101010101010101ULL;
  uint64_t b_file = 0x0202020202020202ULL;
  uint64_t g_file = 0x4040404040404040ULL;
  uint64_t h_file = 0x8080808080808080ULL;
  uint64_t rank_1 = 0x00000000000000FFULL;
  uint64_t rank_2 = 0x000000000000FF00ULL;
  uint64_t rank_7 = 0x00FF000000000000ULL;
  uint64_t rank_8 = 0xFF00000000000000ULL;

  // NNE
  moves |= (pos & (h_file | rank_7 | rank_8)) ? 0ULL : pos << 17;

  // NEE
  moves |= (pos & (g_file | h_file | rank_8)) ? 0ULL : pos << 10;

  // SEE
  moves |= (pos & (g_file | h_file | rank_1)) ? 0ULL : pos >> 6;

  // SSE
  moves |= (pos & (h_file | rank_1 | rank_2)) ? 0ULL : pos >> 15;

  // SSW
  moves |= (pos & (a_file | rank_1 | rank_2)) ? 0ULL : pos >> 17;

  // SWW
  moves |= (pos & (a_file | b_file | rank_1)) ? 0ULL : pos >> 10;

  // NWW
  moves |= (pos & (a_file | b_file | rank_8)) ? 0ULL : pos << 6;

  // NNW
  moves |= (pos & (a_file | rank_7 | rank_8)) ? 0ULL : pos << 15;

  return moves & ~friendly_squares;
}