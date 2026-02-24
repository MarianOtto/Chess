#include "../include/figure.h"
#include "../include/board.h"
#include <memory>

//CONSTRUCTORS
Figure::Figure(Color color, Square::Index square_index, Type type, Board& board)
:_color(color), _square_index(square_index), _type(type), _board(board){
    _has_moved = 0;
    //Assign opposite color
    switch (color) {
        case Color::White:
            _opposite_color = Color::Black;
            break;
        case Color::Black:
            _opposite_color = Color::White;
            break;
        default: //Color is Any
            _opposite_color = Color::Any;
            break;
    }
}

std::unique_ptr<Figure> Figure::fromNotation(Color color, std::string notation, Board& board){
    Square square = Square::fromNotation(notation, board);
    
    return std::make_unique<Figure>(color, square.index(), Type::None, board);
}


//GETTER
Color Figure::get_color() const{
    return _color;
}

Square Figure::get_square() const{
    return (_board.get_squares()->at(_square_index));
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
void Figure::set_square_index(Square::Index index){
    _square_index = index;
}
void Figure::set_has_moved(bool has_moved){
    _has_moved = has_moved;
}
void Figure::set_type(Type type){
    _type = type;
}