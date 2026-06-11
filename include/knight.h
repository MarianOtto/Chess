#pragma once

#include "piece.h"
#include <cstdint>

class Knight : public Piece
{
public:
  uint64_t static get_possible_moves(uint64_t pos,
                                     bool is_white,
                                     uint64_t friendly_squares,
                                     uint64_t enemy_squares,
                                     uint64_t free_squares);
};