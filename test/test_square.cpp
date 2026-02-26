#include "../include/catch.hpp"
#include "../include/square.h"
#include "../include/figure.h"
#include "../include/board.h"
#include <string>

TEST_CASE("Create Square", "[square]"){
    Board board;
    SECTION("Square at 0"){
        Square square(0, board); //Create square with idx 35

        CHECK(square.index() == 0);
        CHECK(square.bit() == 0b1);
        CHECK(square.notation() == "A1");
    }
    SECTION("Square at 63"){
        Square square(63, board); //Create square with idx 35

        CHECK(square.index() == 63);
        CHECK(square.bit() == 0x8000000000000000);
        CHECK(square.notation() == "H8");
    }
}

TEST_CASE("Create Wrong Squares", "[square]"){
    Board board;
    GIVEN("Wrong parameters for Square creation"){
        WHEN("You create the Square with an index too big"){
            THEN("The Square should throw an error"){
                CHECK_THROWS(Square(64, board));
            }
        }
        WHEN("You create the Square with an index too small"){
            THEN("The Square should throw an error"){
                CHECK_THROWS(Square(-1, board));                
            }
        }
        WHEN("You create the Square with a string too long or wrong notation"){
            THEN("The Square should throw an error"){
                CHECK_THROWS(Square::fromNotation("abc", board));
                CHECK_THROWS(Square::fromNotation("A9", board));
                CHECK_THROWS(Square::fromNotation("I1", board));
            }
        }
    }

}

TEST_CASE("Create Square from notation", "[square]"){
    Board board;
    SECTION("A1"){
        Square square = Square::fromNotation("A1", board);

        CHECK(square.index() == 0);
        CHECK(square.bit() == 0b1);
        CHECK(square.notation() == "A1");
    }

    SECTION("A8"){
        Square square = Square::fromNotation("A8", board);

        CHECK(square.index() == 7);
        CHECK(square.bit() == 0x80);
        CHECK(square.notation() == "A8");
    }

    SECTION("H1"){
        Square square = Square::fromNotation("H1", board);

        CHECK(square.index() == 56);
        CHECK(square.bit() == 0x100000000000000);
        CHECK(square.notation() == "H1");
    }

    SECTION("H8"){
        Square square = Square::fromNotation("H8", board);

        CHECK(square.index() == 63);
        CHECK(square.bit() == 0x8000000000000000);
        CHECK(square.notation() == "H8");
    }
}

TEST_CASE("Add Figure on Square", "[square]"){
    GIVEN("A Square on A3 and a Figure on A4"){
        Board board;
        Square square = Square::fromNotation("A3", board);
        auto figure = Figure::fromNotation(Color::Black, "A4", board);
        auto figptr = figure.get();
        

        WHEN("You add the Figure to the Square and to the Board"){
            square.set_figure(figptr);
            board.addFigure(std::move(figure), &square);
            
            THEN("The Figure should be accessible by the Square"){
                CHECK(square.get_figure() == figptr);
            }
            THEN("The Figure square index should change to the Square"){
                CHECK(figptr->get_square()->index() == square.index());
            }
            THEN("The change should also show in the Board Square"){
                CHECK(board.get_figure_on(square.index()) == figptr);
            }
        }
    }
}