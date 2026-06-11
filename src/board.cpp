#include "../include/board.h"
#include "../include/bishop.h"
#include "../include/king.h"
#include "../include/knight.h"
#include "../include/pawn.h"
#include "../include/queen.h"
#include "../include/rook.h"
#include <cstdint>
#include <stdexcept>
#include <vector>

Bishop bishop;
Knight knight;
King king;
Pawn pawn;
Queen queen;
Rook rook;

// CONSTRUCTORS
Board::Board()
{
  _black_bitmap = 0;
  _white_bitmap = 0;
  _has_not_moved = 0xFFFFFFFFFFFFFFFF;
  for (int i = 0; i < 64; i++)
    _figures.push_back('0');
}

// GETTERS
std::vector<char> Board::get_figures()
{
  return _figures;
}

char Board::get_figure_on(std::string notation)
{
  Board::Index index = this->notation2index(notation);
  return _figures[index];
}

char Board::get_figure_on(Index index)
{
  return _figures[index];
}

uint64_t Board::get_black_bitmap()
{
  return _black_bitmap;
}

uint64_t Board::get_white_bitmap()
{
  return _white_bitmap;
}

uint64_t Board::get_any_bitmap()
{
  return _white_bitmap | _black_bitmap;
}

uint64_t Board::get_has_not_moved()
{
  return _has_not_moved;
}

bool Board::is_white(Index index)
{
  return (_figures[index] < 0x60 || _figures[index] == '0') ? 1 : 0;
}

Board::Index Board::notation2index(std::string notation)
{
  if (notation.size() != 2) {
    throw std::length_error("Invalid notation size");
  }

  char file = notation[0];
  char rank = notation[1];

  if (!(file >= 'A' && file <= 'H')) {
    throw std::out_of_range("fromNotation[0] not between A..H");
  } else if (!('1' <= rank && rank <= '8')) {
    throw std::out_of_range("fromNotation[1] not between 1..8");
  }

  file = file - 'A';
  rank = rank - '1';

  return rank * 8 + file;
}

// ADD FIGURE
void Board::addFigure(Color color, Type type, std::string notation)
{
  Board::Index index = notation2index(notation);
  uint64_t bit = 1ULL << index;

  // Cant put a piece on an occupied square
  if (_figures[index] != '0')
    return;

  switch (type) {
    case Type::King:
      _figures[index] = color == Color::White ? 'K' : 'k';
      break;
    case Type::Queen:
      _figures[index] = color == Color::White ? 'Q' : 'q';
      break;
    case Type::Rook:
      _figures[index] = color == Color::White ? 'R' : 'r';
      break;
    case Type::Bishop:
      _figures[index] = color == Color::White ? 'B' : 'b';
      break;
    case Type::Knight:
      _figures[index] = color == Color::White ? 'N' : 'n';
      break;
    case Type::Pawn:
      _figures[index] = color == Color::White ? 'P' : 'p';
      break;
  }

  // Update bitmaps
  if (color == Color::Black) {
    _black_bitmap |= bit;
  } else {
    _white_bitmap |= bit;
  }

  _has_not_moved |= bit;
}

uint64_t Board::get_possible_moves(std::string notation)
{
  Board::Index index = this->notation2index(notation);
  return get_possible_moves(index);
}

uint64_t Board::get_possible_moves(Index index)
{
  uint64_t pos = 1ULL << index;
  bool is_white = _figures[index] < 0x60 ? 1 : 0;
  uint64_t friendly_squares = is_white ? _white_bitmap : _black_bitmap;
  uint64_t enemy_squares = is_white ? _black_bitmap : _white_bitmap;
  uint64_t free_squares = ~this->get_any_bitmap();

  char type = _figures[index];
  switch (type) {
    ///////////////////////////////////////////
    //               PAWN
    ///////////////////////////////////////////
    case 'p':
    case 'P':

      return Pawn::get_possible_moves(
        pos, is_white, friendly_squares, enemy_squares, free_squares);

    ///////////////////////////////////////////
    //               King
    ///////////////////////////////////////////
    case 'K':
    case 'k':

      return King::get_possible_moves(
        pos, is_white, friendly_squares, enemy_squares, free_squares);

    ///////////////////////////////////////////
    //               Queen
    ///////////////////////////////////////////
    case 'Q':
    case 'q':
      return Queen::get_possible_moves(
        pos, is_white, friendly_squares, enemy_squares, free_squares);

    ///////////////////////////////////////////
    //               Rook
    ///////////////////////////////////////////
    case 'R':
    case 'r':
      return Rook::get_possible_moves(
        pos, is_white, friendly_squares, enemy_squares, free_squares);

    ///////////////////////////////////////////
    //               Bishop
    ///////////////////////////////////////////
    case 'B':
    case 'b':
      return Bishop::get_possible_moves(
        pos, is_white, friendly_squares, enemy_squares, free_squares);

    ///////////////////////////////////////////
    //               Knight
    ///////////////////////////////////////////
    case 'N':
    case 'n':
      return Knight::get_possible_moves(
        pos, is_white, friendly_squares, enemy_squares, free_squares);

    default:
      // Not occupied
      return 0ULL;
  }
}