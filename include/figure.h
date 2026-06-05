#pragma once
#include "../include/color.h"
#include "../include/square.h"
#include "../include/type.h"
#include <memory>
#include <vector>

class Board;

class Figure
{
public:
  Figure(Color color, Square* square, Type type, Board& board);
  static std::unique_ptr<Figure> fromNotation(Color color,
                                              std::string notation,
                                              Type type,
                                              Board& board);

  Color get_color() const;
  Square* get_square() const;
  Type get_type() const;
  bool get_has_moved() const;
  Color get_opposite_color() const;
  Board* get_board() const;

  void set_square(Square* square);
  void set_has_moved(bool has_moved);
  void set_type(Type type);

  virtual void move() = 0;
  virtual std::vector<Square*> get_possible_moves() = 0;

protected:
  Color _color;
  Square* _square;
  Type _type;
  bool _has_moved;
  Color _opposite_color;
  Board& _board;
};