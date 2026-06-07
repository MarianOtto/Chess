#pragma once
#include "../include/color.h"
#include "../include/square.h"
#include "../include/type.h"
#include <memory>

class Board;

class Figure
{
public:
  // Constructors
  Figure(Color color, Square* square, Type type, Board& board);

  /**
   * @brief Factory to construct Figures
   *
   * @param color
   * @param notation
   * @param type
   * @param board
   * @return std::unique_ptr<Figure>
   */
  static Figure* fromNotation(Color color, std::string notation, Board& board);

  // Getters
  Color get_color() const;
  Square* get_square() const;
  Type get_type() const;
  bool get_has_moved() const;
  Color get_opposite_color() const;
  Board* get_board() const;

  // Setters
  void set_square(Square* square);
  void set_has_moved(bool has_moved);
  void set_type(Type type);

  /**
   * @brief Pure Virtual Method to get possible moves
   *
   * @return uint64_t
   */
  virtual uint64_t get_possible_moves() = 0;

protected:
  Color _color;
  Square* _square;
  Type _type;
  bool _has_moved;
  Color _opposite_color;
  Board& _board;
};