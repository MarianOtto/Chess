#include "../include/figure.h"

//CONSTRUCTORS
Figure::Figure(Color color, Square square, Type type)
:_color(color), _square_index(square.index()), _type(type){
    _has_moved = 0;
    //Assign opposite color
    switch (color) {
        case Figure::Color::White:
            _opposite_color = Color::Black;
            break;
        case Figure::Color::Black:
            _opposite_color = Color::White;
            break;
        default: //Color is Any
            _opposite_color = Color::Any;
            break;
    }
}

Figure Figure::fromNotation(Color color, std::string notation){
    Square square = Square::fromNotation(notation);
    
    return Figure(color, square, Type::None);
}


//GETTER
Figure::Color Figure::get_color() const{
    return _color;
}

Square::Index Figure::get_square_index() const{
    return _square_index;
}

Figure::Type Figure::get_type() const{
    return _type;
}

bool Figure::get_has_moved() const{
    return _has_moved;
}

Figure::Color Figure::get_opposite_color() const{
    return _opposite_color;
}


//SETTER
void Figure::set_square_index(Square square){
    _square_index = square.index();
}
void Figure::set_has_moved(bool has_moved){
    _has_moved = has_moved;
}
void Figure::set_type(Type type){
    _type = type;
}