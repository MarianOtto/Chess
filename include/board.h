#pragma once

#include <array>
#include <cstdint>
#include <vector>
#include <memory>
#include "../include/square.h"
#include "../include/color.h"
#include "../include/type.h"

class Figure;

class Board{
    public:
        uint64_t get_white_bitmap();
        uint64_t get_black_bitmap();
        uint64_t get_any_bitmap();
        std::vector<std::unique_ptr<Square>>* get_squares();
        std::vector<std::unique_ptr<Figure>>* get_figures();
        Figure* get_figure_on(std::string notation);
        Figure* get_figure_on(Square::Index index);
        Square* get_square_at(std::string notation);
        Square* get_square_at(Square::Index index);

        Board();

        void addFigure(std::unique_ptr<Figure> figure);
        void addFigure(std::unique_ptr<Figure> figure, std::string notation); 
        void addFigure(std::unique_ptr<Figure> figure, Square* square);

    private:
        uint64_t _white_bitmap;
        uint64_t _black_bitmap;
        std::vector<std::unique_ptr<Square>> _squares;
        std::vector<std::unique_ptr<Figure>> _figures;
};