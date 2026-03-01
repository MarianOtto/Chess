#include "../include/catch.hpp"
#include "../include/square.h"
#include "../include/figure.h"
#include "../include/board.h"
#include <string>

TEST_CASE("Create Square", "[square]"){
    Board board;
    SECTION("Square at 0"){
        Square square(0, board);

        CHECK(square.index() == 0);
        CHECK(square.bit() == 0b1);
        CHECK(square.notation() == "A1");
    }
    SECTION("Square at 63"){
        Square square(63, board);

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

TEST_CASE("set_figure: Add Figure on Square", "[square]"){
    GIVEN("A Square on A3 and a Figure on A4"){
        Board board;
        Square square = Square::fromNotation("A3", board);
        auto figure = Figure::fromNotation(Color::Black, "A4", board); //Create square with idx 35
        auto figptr = figure.get();
        

        WHEN("You add the Figure to the Square"){
            square.set_figure(figptr);
            
            THEN("The Figure should be accessible by the Square"){
                CHECK(square.get_figure() == figptr);
            }
            THEN("The Figure square should change to the Square"){
                CHECK(figptr->get_square() == &square);
            }
        }
    }
}


TEST_CASE("occupied_by: Check Square for Occupancy", "[sqaure][occupied_by]"){
    GIVEN("A board with three different color Figures"){
        Board board;
        auto whiteFigure = Figure::fromNotation(Color::White, "B3", board);
        auto blackFigure = Figure::fromNotation(Color::Black, "G4", board);

        board.addFigure(std::move(whiteFigure));
        board.addFigure(std::move(blackFigure));


        WHEN("You check for all combinations"){
            
            
            THEN("All returns should be consistent"){
                //Empty Square
                CHECK(board.get_square_at("A1")->occupied_by(Color::Black) == 0);
                CHECK(board.get_square_at("A1")->occupied_by(Color::White) == 0);
                CHECK(board.get_square_at("A1")->occupied_by(Color::Any) == 0);
                //White Square
                CHECK(board.get_square_at("B3")->occupied_by(Color::Black) == 0);
                CHECK(board.get_square_at("B3")->occupied_by(Color::White) == 1);
                CHECK(board.get_square_at("B3")->occupied_by(Color::Any) == 1);
                //Black Square
                CHECK(board.get_square_at("G4")->occupied_by(Color::Black) == 1);
                CHECK(board.get_square_at("G4")->occupied_by(Color::White) == 0);
                CHECK(board.get_square_at("G4")->occupied_by(Color::Any) == 1);
            }
        }
    }
}

TEST_CASE("has_figure: Check if Square has Figure", "[square][has_figure]"){
    Board board;
    auto figure = Figure::fromNotation(Color::White, "A7", board);

    Square* occupiedSquare =  board.get_square_at("A7");
    Square* emptySquare = board.get_square_at("A1");

    CHECK(occupiedSquare->has_figure() == 1);
    CHECK(emptySquare->has_figure() == 0);
}