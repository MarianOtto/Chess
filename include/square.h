#pragma once

#include <cstdint>
#include <memory>
#include <string>

class Figure;
class Board;

class Square{
    public:
        using Index = uint8_t;
        using Bitmap = uint64_t;
    
        Square(Index idx, Board &board);
    
        static Square fromNotation(std::string notation, Board &board);
    
        Index index() const;
        Bitmap bit() const;
        std::string notation() const;

        Figure* get_figure();

        void set_figure(Figure* figure);
    
    private:
        const Index _index;
        Board& _board;
        Figure* _figure;
    };