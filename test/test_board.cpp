#include "../include/catch.hpp"
#include "../include/board.h"
#include "../include/figure.h"
#include <utility>

TEST_CASE("Create Board", "[board]"){
    GIVEN("A number x"){
    Board board;
    int x = GENERATE(range(0,64));

        WHEN("You check the index of a Square at that number"){
            THEN("The index should be the same as the number x "){
                CHECK(board.get_squares()->at(x).index() == x);
            }
        }
    }
}

TEST_CASE("Add Figures", "[board]"){
    GIVEN("A Figure on D3"){
    Board board;
    auto figure = Figure::fromNotation(Color::Black, "D3", board);
    

        WHEN("You add a black Figure to the Board"){
            board.addFigure(std::move(figure));

            THEN("You should be able to access the Figure via the Board"){
                CHECK(board.get_figure_on("D3")->get_opposite_color() == Color::White);
            }
            THEN("The white bitmap should not change"){
                CHECK(board.get_white_bitmap() == 0);
            }
            THEN("The black bitmap should change"){
                CHECK(board.get_black_bitmap() == 0x4000000);
            }
            THEN("THE any bitmap should change"){
                CHECK(board.get_any_bitmap() == 0x4000000);
            }
        }
    }
}

TEST_CASE("Add Figure to specific square by string", "[board]"){
    GIVEN("A white Figure on A4"){
        Board board;
        auto figure = Figure::fromNotation(Color::White, "A4", board);

        WHEN("You add a Figure by notation which is different then the original"){
            board.addFigure(std::move(figure), "B5");

            THEN("The notation/square of the figure should change"){
                CHECK(board.get_figures()->back()->get_square()->notation() == "B5");
            }
            THEN("The Figure should be added to the Square on B5"){
                CHECK(board.get_figure_on("B5")->get_square()->notation() == "B5");
            }
            THEN("The white bitmap should change"){
                CHECK(board.get_white_bitmap() == 0x1000);
            }
            THEN("The black bitmap should not change"){
                CHECK(board.get_black_bitmap() == 0);
            }
            THEN("The any bitmap should change"){
                CHECK(board.get_any_bitmap() == 0x1000);
            }
        }
    }
}

TEST_CASE("Add Figure to specific square by index", "[board]"){
    GIVEN("A White Figure on A4"){
        Board board;
        auto figure = Figure::fromNotation(Color::White, "A4", board);

        WHEN("You add a Figure to the Board at a certain index"){
            board.addFigure(std::move(figure), board.get_square_at(18));
            THEN("The square index of the Figure obbject should change"){
                CHECK(board.get_figures()->back()->get_square()->index() == 18);
            }
        }
    }
}

TEST_CASE("Add multiple Figures", "[board]"){
    GIVEN("A black and a white Figure"){
        Board board;
        auto figureA = Figure::fromNotation(Color::Black, "A8", board);
        auto figureB = Figure::fromNotation(Color::White, "B3", board);

        WHEN("You add both Figures to the Board"){
            board.addFigure(std::move(figureA));
            board.addFigure(std::move(figureB));
        
            THEN("The black bitmap should change for the black piece"){
                CHECK(board.get_black_bitmap() == 0x80);
            }
            THEN("The white bitmap should change for the white piece"){
                CHECK(board.get_white_bitmap() == 0x400);
            }
            THEN("The any bitmap should show the change of both piece added"){
                CHECK(board.get_any_bitmap() == 0x480);
            }
        }
    }
}

TEST_CASE("Get Figure on Square A4"){
    GIVEN("A Figure on A4"){
        Board board;
        auto figure = Figure::fromNotation(Color::White, "A4", board);
        Figure* figptr = figure.get();

        WHEN("You add the Figure to the Board on Square A4"){
            board.addFigure(std::move(figure), "A4");

            THEN("Board::get_figure_on(std::string) should return a pointer to the Figure"){
                CHECK(board.get_figure_on("A4") == figptr);
            }
            THEN("Board::get_figure_on(Index) should return a pointer to the Figure"){
                CHECK(board.get_figure_on(3) == figptr);
            }
        }
    }
}

TEST_CASE("Move Figure", "[board] [move]"){
    GIVEN("A Figure on A3"){
        Board board;
        auto figure = Figure::fromNotation(Color::White, "A3", board);

        // WHEN("You move the Figure to D3"){
        //     board.move("A3", "D3");

        //     THEN("The Figure square index should change"){
        //         CHECK(figure->get_square().notation() == "D3");
        //     }
        //     THEN("The Figure should belong to the D3 (Index 26) of the Board"){
        //         CHECK(board.get_squares().at(26).get_figure() == figure.get());
        //     }
        // }
    }
}