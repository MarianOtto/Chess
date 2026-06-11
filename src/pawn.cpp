#include "../include/pawn.h"

uint64_t Pawn::get_possible_moves(uint64_t pos,
                                  bool is_white,
                                  uint64_t friendly_squares,
                                  uint64_t enemy_squares,
                                  uint64_t free_squares)
{
  uint64_t a_file = 0x0101010101010101ULL;
  uint64_t h_file = 0x8080808080808080ULL;
  uint64_t rank_1 = 0x00000000000000FFULL;
  uint64_t rank_8 = 0xFF00000000000000ULL;
  uint64_t rank_2 = 0x000000000000FF00ULL;
  uint64_t rank_7 = 0x00FF000000000000ULL;

  uint64_t last_rank = is_white ? rank_8 : rank_1;  // 8th or 1st row
  uint64_t start_rank = is_white ? rank_2 : rank_7; // 7th or 2nd row

  uint64_t single_push = 0ULL;
  uint64_t double_push = 0ULL;
  uint64_t cap_right = 0ULL;
  uint64_t cap_left = 0ULL;

  // Pawns on last rank dont have valid moves
  if (pos & last_rank)
    return 0ULL;

  // Single Push
  single_push = is_white ? pos << 8 : pos >> 8;

  // Double Push
  double_push = 0ULL;
  if (pos & start_rank) {
    if (single_push & free_squares) {
      double_push = is_white ? pos << 16 : pos >> 16;
    }
  }

  // Capture left
  cap_left = (pos & ~a_file) ? (is_white ? pos << 7 : pos >> 9) : 0ULL;

  // Capture right
  cap_right = (pos & ~h_file) ? (is_white ? pos << 9 : pos >> 7) : 0ULL;

  return (((single_push | double_push) & free_squares) |
          ((cap_left | cap_right) & enemy_squares));
}