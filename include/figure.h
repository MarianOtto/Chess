#pragma once
#include "../include/square.h"

class Figure{
    public:
        enum class Color{
            Black = 0,
            White = 1,
            Any = -1
        };

        enum class Type{
            King = 1,
            Queen,
            Rook,
            Bishop,
            Knight,
            Pawn,
            None = -1
        };

        Color get_color() const;
        Square::Index get_square_index() const;
        Type get_type() const;
        bool get_has_moved() const;
        Color get_opposite_color() const;

        void set_square_index(Square square);
        void set_has_moved(bool has_moved);
        void set_type(Type type);

        Figure(Color color, Square square, Type type);
        static Figure fromNotation(Color color, std::string notation);

    private:
        Color _color;
        Square::Index _square_index;
        Type _type;
        bool _has_moved;
        Color _opposite_color;
        
};