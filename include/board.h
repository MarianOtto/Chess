#pragma once

#include "../include/color.h"
#include "../include/type.h"
#include <cstdint>
#include <string>
#include <vector>
class Board
{
public:
  using Index = uint8_t;
  using Bitmap = uint64_t; // Maybe use
  /**
   * @brief Construct a new Board object
   *
   */
  Board();

  /**
   * @brief Get the bitmaps representing
   *
   * @return uint64_t
   */
  uint64_t get_white_bitmap();
  uint64_t get_black_bitmap();
  uint64_t get_any_bitmap();
  uint64_t get_has_not_moved();

  std::vector<char> get_figures();

  // Helper Functions
  bool is_white(Index index);
  Index notation2index(std::string notation);

  char get_figure_on(std::string notation);
  char get_figure_on(Index index);

  /**
   * @brief Add figure to _figures
   *
   * Add the figure to the board
   *
   * @param figure
   */
  void addFigure(Color color, Type type, std::string notation);
  void addFigure(Color color, Type type, uint64_t bitmap);

  uint64_t get_possible_moves(Index index);
  uint64_t get_possible_moves(std::string notation);

private:
  uint64_t _white_bitmap;
  uint64_t _black_bitmap;
  uint64_t _has_not_moved;
  std::vector<char> _figures;
};