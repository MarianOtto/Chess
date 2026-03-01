#include "../include/figure.h"
#include "../include/board.h"
#include <memory>
#include <stdexcept>

//CONSTRUCTORS
Figure::Figure(Color color, Square* square, Type type, Board& board)
:_color(color), _square(square), _type(type), _board(board){
    _has_moved = 0;
    //Assign opposite color
    switch (color) {
        case Color::White:
            _opposite_color = Color::Black;
            break;
        case Color::Black:
            _opposite_color = Color::White;
            break;
        case Color::Any: //Color is Any
            throw std::invalid_argument("Color needs to be Black or White");
            break;
    }
    //Add to board
    square->set_figure(this);
}

std::unique_ptr<Figure> Figure::fromNotation(Color color, std::string notation, Board& board){

    return std::make_unique<Figure>(color, board.get_square_at(notation), Type::None, board);
}

std::unique_ptr<Figure> Figure::fromNotation(Color color, std::string notation, Type type, Board& board){

    return std::make_unique<Figure>(color, board.get_square_at(notation), type, board);
}

//GETTER
Color Figure::get_color() const{
    return _color;
}

Square* Figure::get_square() const{
    return _square;
}

Type Figure::get_type() const{
    return _type;
}

bool Figure::get_has_moved() const{
    return _has_moved;
}

Color Figure::get_opposite_color() const{
    return _opposite_color;
}


//SETTER
void Figure::set_square(Square* square){
    _square = square;
}
void Figure::set_has_moved(bool has_moved){
    _has_moved = has_moved;
}
void Figure::set_type(Type type){
    _type = type;
}