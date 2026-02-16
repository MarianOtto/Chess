#include "../include/catch.hpp"
#include "../include/figure.h"

TEST_CASE("Create Figure", "[figure]"){
    Square square(8);
    Figure figure(Figure::Color::Any, square, Figure::Type::None);

    CHECK(figure.get_color() == Figure::Color::Any);
    CHECK(figure.get_square_index() == 8);
    CHECK(figure.get_has_moved() == 0);
    CHECK(figure.get_opposite_color() == Figure::Color::Any);
    CHECK(figure.get_type() == Figure::Type::None);
}

TEST_CASE("Create Figure from Notation", "[figure]"){
    Figure figure = Figure::fromNotation(Figure::Color::Black, "B1");

    CHECK(figure.get_color() == Figure::Color::Black);
    CHECK(figure.get_square_index() == 8);
    CHECK(figure.get_has_moved() == 0);
    CHECK(figure.get_opposite_color() == Figure::Color::White);
    CHECK(figure.get_type() == Figure::Type::None);
}

TEST_CASE("Test setters", "[figure]"){
    Figure figure = Figure::fromNotation(Figure::Color::White, "C3");

    REQUIRE(figure.get_square_index() == 18);
    REQUIRE(figure.get_has_moved() == 0);
    REQUIRE(figure.get_type() == Figure::Type::None);

    SECTION("Set square"){
        Square square = Square::fromNotation("D8");
        figure.set_square_index(square);

        CHECK(figure.get_square_index() == square.index());
    }

    SECTION("Set has_moved"){
        figure.set_has_moved(1);

        CHECK(figure.get_has_moved() == 1);
    }

    SECTION("Set type"){
        figure.set_type(Figure::Type::King);

        CHECK(figure.get_type() == Figure::Type::King);
    }
}

TEST_CASE("Move Figure", "[figure]"){
    Figure figure = Figure::fromNotation(Figure::Color::White, "B6");
    Figure figureBlack = Figure::fromNotation(Figure::Color::Black, "D1");
    Figure figureWhite = Figure::fromNotation(Figure::Color::White, "A2");

    SECTION("Move to a free Square"){
        figure.move("A3");

        CHECK(figure.get_has_moved() == 1);
        CHECK(figure.get_square_index() == 2);
    }

    SECTION("Move to occupied Square"){
        CHECK_THROWS(figure.move("D1")); //Black Piece
        CHECK_THROWS(figure.move("A2")); //White Piece
    }

    SECTION("Move out of board"){
        CHECK_THROWS(figure.move("A9"));
    }

    /*\
    TODO: Check for swap
    i.e. if figure moves to empty square or captures 
    piece the old square should be empty now
    */

}
//TODO: move
//TODO: get squares