#include "../include/catch.hpp"
#include "../include/figure.h"
#include "../include/board.h"

TEST_CASE("Create Figure", "[figure]"){
    GIVEN("An empty board"){
        Board board;

        WHEN("You construct a white Figure on Square 8"){
            Figure figure(Color::White, board.get_square_at(8), Type::None, board);

            THEN("All the members should be set"){
                CHECK(figure.get_color() == Color::White);
                CHECK(figure.get_square() == board.get_square_at(8));
                CHECK(figure.get_has_moved() == 0);
                CHECK(figure.get_opposite_color() == Color::Black);
                CHECK(figure.get_type() == Type::None);
            }
        }

        WHEN("You construct a Figure with an invalid color"){
            THEN("An exception should be thrown"){
                CHECK_THROWS(Figure(Color::Any, board.get_square_at(8), Type::None, board));
            }
        }
    }

}

TEST_CASE("Color should match opposite color", "[figure]"){
    GIVEN("An empty Board"){
        Board board;

        WHEN("You construct a black Figure"){
            Figure figure(Color::Black, board.get_square_at("H3"), Type::None, board);

            THEN("The colors should be opposite"){
                CHECK(figure.get_color() == Color::Black);
                CHECK(figure.get_opposite_color() == Color::White);
            }
        }

        WHEN("You construct a white Figure"){
            Figure figure(Color::White, board.get_square_at("H3"), Type::None, board);

            THEN("The colors should be opposite"){
                CHECK(figure.get_color() == Color::White);
                CHECK(figure.get_opposite_color() == Color::Black);
            }
        }
    }
}

TEST_CASE("fromNotation: Create different Classes from Types", "[figure]")
{
  GIVEN("An empty Board")
  {
    Board board;
    WHEN("You create Figures of different types")
    {
      auto pawn = Figure::fromNotation(Color::White, "D2", Type::Pawn, board);
      auto rook = Figure::fromNotation(Color::White, "A1", Type::Rook, board);
      auto knight =
        Figure::fromNotation(Color::White, "B1", Type::Knight, board);
      auto bishop =
        Figure::fromNotation(Color::White, "C1", Type::Bishop, board);
      auto queen = Figure::fromNotation(Color::White, "D1", Type::Queen, board);
      auto king = Figure::fromNotation(Color::White, "E1", Type::King, board);

      THEN("The correct derived classes should be instantiated")
      {
        CHECK(dynamic_cast<Pawn*>(pawn.get()) != nullptr);
        CHECK(dynamic_cast<Rook*>(rook.get()) != nullptr);
        CHECK(dynamic_cast<Knight*>(knight.get()) != nullptr);
        CHECK(dynamic_cast<Bishop*>(bishop.get()) != nullptr);
        CHECK(dynamic_cast<Queen*>(queen.get()) != nullptr);
        CHECK(dynamic_cast<King*>(king.get()) != nullptr);
      }
    }
  }
}

TEST_CASE("Test setters", "[figure]"){
    GIVEN("A white figure on C3"){
        Board board;
        auto figure = Figure::fromNotation(Color::White, "C3", board);

        REQUIRE(figure->get_square() == board.get_square_at("C3"));
        REQUIRE(figure->get_has_moved() == 0);
        REQUIRE(figure->get_type() == Type::None);

        WHEN("You set different members"){
            figure->set_square(board.get_square_at(31));
            figure->set_has_moved(1);
            figure->set_type(Type::King);

            THEN("The all the members should change"){
                CHECK(figure->get_square() == board.get_square_at(31));
                CHECK(figure->get_has_moved() == 1);
                CHECK(figure->get_type() == Type::King);
            }
        }
    }
}

// TEST_CASE("Move Figure", "[figure]"){
//     Figure figure = Figure::fromNotation(Color::White, "B6");
//     Figure figureBlack = Figure::fromNotation(Color::Black, "D1");
//     Figure figureWhite = Figure::fromNotation(Color::White, "A2");

//     SECTION("Move to a free Square"){
//         figure.move("A3");

//         CHECK(figure.get_has_moved() == 1);
//         CHECK(figure.get_square()->index() == 2);
//     }

//     SECTION("Move to occupied Square"){
//         CHECK_THROWS(figure.move("D1")); //Black Piece
//         CHECK_THROWS(figure.move("A2")); //White Piece
//     }

//     SECTION("Move out of board"){
//         CHECK_THROWS(figure.move("A9"));
//     }

//     /*
//     TODO: Check for swap
//     i.e. if figure moves to empty square or captures 
//     piece the old square should be empty now
//     */

// }
//TODO: move
//TODO: get squares