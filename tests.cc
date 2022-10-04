// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}

/////////////////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Check") {
  Board student;  // NOLINT
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
}


TEST_CASE("Horizontal T") {
  Board student;  // NOLINT
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  REQUIRE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kVertical));
}

TEST_CASE("Vertical T") {
  Board student;  // NOLINT
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  REQUIRE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kHorizontal));
}

TEST_CASE("Right Diag T") {
  Board student;  // NOLINT
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);

  REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  REQUIRE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kHorizontal));
}

TEST_CASE("Left Diag T") {
  Board student;  // NOLINT
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);

  REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  REQUIRE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kHorizontal));
}

TEST_CASE("Out of Bounds") {
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(BoardLocationInBounds(1,2));
  REQUIRE(BoardLocationInBounds(2,1));
  REQUIRE_FALSE(BoardLocationInBounds(-1,10));
  REQUIRE_FALSE(BoardLocationInBounds(10,-1));
  REQUIRE_FALSE(BoardLocationInBounds(1,10));
  REQUIRE_FALSE(BoardLocationInBounds(10,1));
}

TEST_CASE("Row filled or incorrect error") {
  Board student;  // NOLINT
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 2), std::runtime_error);
  REQUIRE_THROWS(DropDiskToBoard(student, DiskType::kPlayer2, 2));
  REQUIRE_THROWS(DropDiskToBoard(student, DiskType::kPlayer2, -1));
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 10), std::runtime_error);
  REQUIRE_THROWS(DropDiskToBoard(student, DiskType::kPlayer2, 8));
  REQUIRE_THROWS(DropDiskToBoard(student, DiskType::kPlayer2, -3));
}

TEST_CASE("Row filled or incorrect error 2") {
  Board student;  // NOLINT
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  REQUIRE_THROWS(DropDiskToBoard(student, DiskType::kPlayer2, 10));
  REQUIRE_THROWS(DropDiskToBoard(student, DiskType::kPlayer2, -1));
  REQUIRE_THROWS(DropDiskToBoard(student, DiskType::kPlayer1, 4));
  REQUIRE_THROWS(DropDiskToBoard(student, DiskType::kPlayer2, 4));
  REQUIRE_THROWS(DropDiskToBoard(student, DiskType::kPlayer1, -2));
  REQUIRE_THROWS(DropDiskToBoard(student, DiskType::kPlayer1, 9));
  REQUIRE_NOTHROW(DropDiskToBoard(student, DiskType::kPlayer1, 0));
  REQUIRE_NOTHROW(DropDiskToBoard(student, DiskType::kPlayer2, 1));
  REQUIRE_NOTHROW(DropDiskToBoard(student, DiskType::kPlayer1, 2));
  REQUIRE_NOTHROW(DropDiskToBoard(student, DiskType::kPlayer2, 3));
  REQUIRE_NOTHROW(DropDiskToBoard(student, DiskType::kPlayer1, 3));
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, -1), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 4), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 10), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 10), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, -2), std::runtime_error);
  
}

TEST_CASE("Board initialization 2", "[board_init]2") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  REQUIRE(AreEqual(solution, student.board));

}

TEST_CASE("Board initialization 3", "[board_init]3") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  REQUIRE_FALSE(AreEqual(solution, student.board));
}

TEST_CASE("Board initialization complete", "[board_init]complete") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1}, 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2}, 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  for(int i = 0; i < Board::kBoardHeight; i++) {
    for(int j = 0; j < Board::kBoardWidth; j++) {
      student.board[i][j] = solution[i][j];
    }
  }
  REQUIRE(AreEqual(student.board, solution));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
}