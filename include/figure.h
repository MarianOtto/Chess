#pragma once
#include "../include/square.h"
#include "../include/color.h"
#include "../include/type.h"
#include <memory>

class Board;

class Figure{
    public:
        Color get_color() const;
        Square get_square() const;
        Type get_type() const;
        bool get_has_moved() const;
        Color get_opposite_color() const;
        Board* get_board() const;

        void set_square_index(Square::Index index);
        void set_has_moved(bool has_moved);
        void set_type(Type type);

        Figure(Color color, Square::Index square_index, Type type, Board& board);
        static std::unique_ptr<Figure> fromNotation(Color color, std::string notation, Board& board);

    private:
        Color _color;
        Square::Index _square_index;
        Type _type;
        bool _has_moved;
        Color _opposite_color;
        Board& _board;
};