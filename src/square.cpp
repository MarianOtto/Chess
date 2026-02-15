#include "../include/square.h"
#include <stdexcept>

Square::Square(Index idx){
    if (idx >= 64) {
        throw std::out_of_range("Square index must be 0..63");
    } else {
        _index = idx;
    }
}

Square Square::fromNotation(std::string notation){
    if(notation.size() != 2){
        std::length_error("Invalid notation size");
    }

    char file = notation[0];
    char rank = notation[1];

    if (!(('a' <= file && file <= 'h') || (file >= 'A' && file <= 'H'))) {
        std::out_of_range("fromNotation[0] not between a..h or A..H");
        return -1;
    } else if (!('1' <= rank && rank <= '8')) {
        std::out_of_range("fromNotation[1] not between 1..8");
        return -1;
    }

    file = ('a' <= file && file <= 'h') ? file - 'a' : file - 'A';
    rank = rank - '1';

    return Square((file) * 8 + rank);
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