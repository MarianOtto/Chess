#include "../include/figure.h"
#include "../include/bishop.h"
#include "../include/board.h"
#include "../include/king.h"
#include "../include/knight.h"
#include "../include/pawn.h"
#include "../include/queen.h"
#include "../include/rook.h"
#include <memory>
#include <stdexcept>

// CONSTRUCTORS
Figure::Figure(Color color, Square* square, Type type, Board& board)
  : _color(color)
  , _square(square)
  , _type(type)
  , _board(board)
{
  _has_moved = 0;
  // Assign opposite color
  switch (color) {
    case Color::White:
      _opposite_color = Color::Black;
      break;
    case Color::Black:
      _opposite_color = Color::White;
      break;
    case Color::Any: // Color is Any
      throw std::invalid_argument("Color needs to be Black or White");
      break;
  }
  // Add to board
  square->set_figure(this);
}

std::unique_ptr<Figure> Figure::fromNotation(Color color,
                                             std::string notation,
                                             Type type,
                                             Board& board)
{
  switch (type) {
    case Type::Pawn:
      return std::make_unique<Pawn>(
        color, board.get_square_at(notation), board);
    case Type::Knight:
      return std::make_unique<Knight>(
        color, board.get_square_at(notation), board);
    case Type::Bishop:
      return std::make_unique<Bishop>(
        color, board.get_square_at(notation), board);
    case Type::Rook:
      return std::make_unique<Rook>(
        color, board.get_square_at(notation), board);
    case Type::Queen:
      return std::make_unique<Queen>(
        color, board.get_square_at(notation), board);
    case Type::King:
      return std::make_unique<King>(
        color, board.get_square_at(notation), board);
    default:
      throw std::invalid_argument("Type needs to be a valid chess piece");
  }
}

// GETTER
Color Figure::get_color() const
{
  return _color;
}

Square* Figure::get_square() const
{
  return _square;
}

Type Figure::get_type() const
{
  return _type;
}

bool Figure::get_has_moved() const
{
  return _has_moved;
}

Color Figure::get_opposite_color() const
{
  return _opposite_color;
}

// SETTER
void Figure::set_square(Square* square)
{
  _square = square;
}
void Figure::set_has_moved(bool has_moved)
{
  _has_moved = has_moved;
}
void Figure::set_type(Type type)
{
  _type = type;
}