#pragma once

#include "../include/color.h"
#include "../include/square.h"
#include "../include/type.h"
#include <array>
#include <cstdint>
#include <memory>
#include <vector>

class Figure;

class Board
{
public:
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

  std::vector<std::unique_ptr<Square>>* get_squares();
  std::vector<std::unique_ptr<Figure>>* get_figures();

  Figure* get_figure_on(std::string notation);
  Figure* get_figure_on(Square::Index index);

  Square* get_square_at(std::string notation);
  Square* get_square_at(Square::Index index);

  /**
   * @brief Add figure to _figures
   *
   * Add the figure to the board using its own square
   * Alternatively specify new square
   *
   * @param figure
   */
  void addFigure(std::unique_ptr<Figure> figure);
  void addFigure(std::unique_ptr<Figure> figure, std::string notation);
  void addFigure(std::unique_ptr<Figure> figure, Square* square);

  /**
   * @brief Check if Square is occupied by figure that color
   *
   * @param color (Black, White, Any)
   * @return true if occupied; else false
   */
  bool occupied_by(Color color, std::string notation);
  bool occupied_by(Color color, Square::Index index);

private:
  uint64_t _white_bitmap;
  uint64_t _black_bitmap;
  std::vector<std::unique_ptr<Square>> _squares;
  std::vector<std::unique_ptr<Figure>> _figures;
};