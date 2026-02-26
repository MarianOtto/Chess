#include "../include/board.h"
#include "../include/figure.h"
#include <cstdint>
#include <vector>

//CONSTRUCTORS
Board::Board(){
    for(int idx = 0; idx <= 63; idx++){
        Square square(idx, *this);
        _squares.push_back(square);
    }
    _black_bitmap = 0;
    _white_bitmap = 0;
    _any_bitmap = 0;
}


//GETTERS
std::vector<Square>* Board::get_squares(){
    return &_squares;
}

std::vector<std::unique_ptr<Figure>>* Board::get_figures(){
    return &_figures;
}

Figure* Board::get_figure_on(std::string notation){
    Square square = Square::fromNotation(notation, *this);
    Square::Index index = square.index();
    return _squares.at(index).get_figure();
}

Figure* Board::get_figure_on(Square::Index index){
    return _squares.at(index).get_figure();
}

Square* Board::get_square_at(std::string notation){
    Square square = Square::fromNotation(notation, *this);

    return get_square_at(square.index());
}

Square* Board::get_square_at(Square::Index index){
    return &_squares.at(index);
}

uint64_t Board::get_black_bitmap(){
    return _black_bitmap;
}

uint64_t Board::get_white_bitmap(){
    return _white_bitmap;
}

uint64_t Board::get_any_bitmap(){
    return _any_bitmap;
}


//ADD FIGURE
void Board::addFigure(std::unique_ptr<Figure> figure){
    //Update bitmaps
    switch (figure->get_color()) {
        case Color::Any:
            _any_bitmap ^= figure->get_square()->bit();
            break;
        case Color::Black:
            _black_bitmap ^= figure->get_square()->bit();
            _any_bitmap ^= figure->get_square()->bit();
            break;
        case Color::White:
            _white_bitmap ^= figure->get_square()->bit();
            _any_bitmap ^= figure->get_square()->bit();
            break;
    }

    
    _figures.push_back(std::move(figure));
}

void Board::addFigure(std::unique_ptr<Figure> figure, std::string notation){
    //TODO: Get square on board via notation
    Square square = Square::fromNotation(notation, *this);
    //figure->set_square(square);
    get_square_at(notation)->set_figure(figure.get());
    
    addFigure(std::move(figure));
}

void Board::addFigure(std::unique_ptr<Figure> figure, Square* square){
    figure->set_square(square);

    get_squares()->at(square->index()).set_figure(figure.get());
    addFigure(std::move(figure));
}