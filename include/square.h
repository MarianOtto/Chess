#pragma once

#include "../include/color.h"
#include <cstdint>
#include <memory>
#include <string>

class Figure;
class Board;

class Square
{
public:
  using Index = uint8_t;
  using Bitmap = uint64_t;

  // Constructors
  Square(Index idx, Board& board);

  /**
   * @brief Factory to construct Squares
   *
   * @param notation
   * @param board
   * @return Square
   */
  static Square fromNotation(std::string notation, Board& board);

  // Getters

  /**
   * @name Get representation
   * Returns postition of square
   */
  ///@{
  // Return as index (0..63)
  Index index() const;
  // Return uint64_t bitmap
  Bitmap bit() const;
  // Return as String
  std::string notation() const;
  ///@}

  Figure* get_figure();

  void set_figure(Figure* figure);

  bool occupied_by(Color color);
  bool has_figure();

private:
  const Index _index;
  Board& _board;
  Figure* _figure;
};
