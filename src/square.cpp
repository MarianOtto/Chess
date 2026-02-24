#include "../include/square.h"
#include "../include/figure.h"
#include <stdexcept>

Square::Square(Index idx, Board& board)
:_index(idx), _board(board){
    _figure = nullptr;
    if (idx >= 64) {
        throw std::out_of_range("Square index must be 0..63");
    }
}

Square Square::fromNotation(std::string notation, Board& board){
    if(notation.size() != 2){
        std::length_error("Invalid notation size");
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

    return Square((file) * 8 + rank, board);
}

Square::Index Square::index() const{
    return _index;
}

Square::Bitmap Square::bit() const{
    return 1ULL << _index;
}


std::string Square::notation() const {
    char file = 'A' + (_index / 8);
    char rank = '1' + (_index % 8);
    return {file, rank};
}

Figure* Square::get_figure(){
    return _figure;
}

void Square::set_figure(Figure* figure){
    figure->set_square_index(this->index());
    _figure = figure;
}