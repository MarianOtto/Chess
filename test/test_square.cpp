#include "../include/catch.hpp"
#include "../include/square.h"
#include <string>

TEST_CASE("Create Square", "[square]"){
    Square square(3); //Create square with idx 35

    CHECK(square.index() == 3);
    CHECK(square.bit() == 0b1000);
    CHECK(square.notation() == "A4");
}

TEST_CASE("Create Wrong Squares", "[square]"){
    CHECK_THROWS(Square(65));
    CHECK_THROWS(Square(-1));
    CHECK_THROWS(Square::fromNotation(("longstring")));
    CHECK_THROWS(Square::fromNotation(("a9")));
    CHECK_THROWS(Square::fromNotation(("i1")));
    CHECK_THROWS(Square::fromNotation(("I1")));
}

TEST_CASE("Create Square from notation", "[square]"){
    Square square = Square::fromNotation("A5"); //Create square with idx 35

    CHECK(square.index() == 4);
    CHECK(square.bit() == 0b10000);
    CHECK(square.notation() == "A5");
}