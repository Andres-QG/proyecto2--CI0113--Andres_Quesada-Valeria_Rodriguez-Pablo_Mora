#include "Player.hh"
#include <gtest/gtest.h>

TEST(CellTest, BoxCheckTest) {
  Cell c1;
  EXPECT_FALSE(c1.boxChecker(PLAYER1));

  *(c1.getLine(0)) = PLAYER1;
  *(c1.getLine(1)) = PLAYER2;
  *(c1.getLine(2)) = PLAYER1;
  *(c1.getLine(3)) = PLAYER1;
  EXPECT_TRUE(c1.boxChecker(PLAYER1));
  EXPECT_EQ(c1.getBoxOwner(), PLAYER1);
  EXPECT_EQ(c1.availableMovesCount(), 0);
}

TEST(CellTest, LineOwnerTest) {
  Cell c1;
  *(c1.getLine(0)) = PLAYER1;
  EXPECT_EQ(*(c1.getLine(0)), PLAYER1);
  *(c1.getLine(1)) = PLAYER2;
  EXPECT_EQ(*(c1.getLine(1)), PLAYER2);
  *(c1.getLine(2)) = PLAYER1;
  EXPECT_EQ(*(c1.getLine(2)), PLAYER1);
  EXPECT_EQ(*(c1.getLine(3)), NO_OWNER);
  EXPECT_EQ(c1.availableMovesCount(), 1);
  Cell c2;
  EXPECT_EQ(c2.availableMovesCount(), 4);
  *(c2.getLine(0)) = PLAYER1;
  *(c2.getLine(3)) = PLAYER2;
  EXPECT_EQ(c2.availableMovesCount(), 2);
}

TEST(BoardTest, BoxesSizeTest) {
  Board b1(13, 6);
  EXPECT_EQ(b1.getBoardRowSize(), 12);
  EXPECT_EQ(b1.getBoardColSize(), 5);

  EXPECT_EQ(b1.getAvailableMoves().size(), 12 * 5 * 4);
  for (int i = 0; i < b1.getBoardRowSize(); i++) {
    for (int j = 0; j < b1.getBoardColSize(); j++) {
      *(b1.getCell(i, j)->getLine(0)) = PLAYER1;
      *(b1.getCell(i, j)->getLine(2)) = PLAYER1;
    }
  }
  EXPECT_EQ(b1.getAvailableMoves().size(), 12 * 5 * 2);
}

TEST(BoardTest, ScoreTest) {
  Board b1(15, 10);
  EXPECT_EQ(b1.getScoreP1(), 0);
  EXPECT_EQ(b1.getScoreP2(), 0);
  for (int i = 0; i < b1.getBoardRowSize(); i++) {
    for (int j = 0; j < b1.getBoardColSize() - 1; j++) {
      *(b1.getCell(i, j)->getLine(0)) = PLAYER1;
      *(b1.getCell(i, j)->getLine(1)) = PLAYER1;
      *(b1.getCell(i, j)->getLine(2)) = PLAYER1;
      *(b1.getCell(i, j)->getLine(3)) = PLAYER1;
      b1.getCell(i, j)->boxChecker(PLAYER1);
    }
  }
  for (int i = 0; i < b1.getBoardRowSize(); i++) {
    *(b1.getCell(i, b1.getBoardColSize() - 1)->getLine(0)) = PLAYER2;
    *(b1.getCell(i, b1.getBoardColSize() - 1)->getLine(1)) = PLAYER2;
    *(b1.getCell(i, b1.getBoardColSize() - 1)->getLine(2)) = PLAYER2;
    *(b1.getCell(i, b1.getBoardColSize() - 1)->getLine(3)) = PLAYER2;
    b1.getCell(i, b1.getBoardColSize() - 1)->boxChecker(PLAYER2);
  }
  b1.scoreUpdater();
  EXPECT_EQ(b1.getScoreP1(), 14 * 8);
  EXPECT_EQ(b1.getScoreP2(), 14);
}

TEST(BoardTest, SEGFPrevisionTest) {
  Board b1(14, 14);
  EXPECT_EQ(b1.getCell(500, 6), nullptr);
  EXPECT_EQ(b1.getCell(0, 789899), nullptr);
  EXPECT_EQ(b1.getCell(666, 777), nullptr);
  EXPECT_EQ(b1.getCell(14, 14), nullptr);
  EXPECT_NE(b1.getCell(0, 0), nullptr);
}

void modifyBoardTestMethod(Board board) {
  *(board.getCell(0, 0)->getLine(0)) = PLAYER1;
  *(board.getCell(0, 0)->getLine(1)) = PLAYER1;
  *(board.getCell(0, 0)->getLine(2)) = PLAYER1;
  *(board.getCell(0, 0)->getLine(3)) = PLAYER1;
  board.getCell(0, 0)->boxChecker(PLAYER1);
}

TEST(BoardTest, CopyTest) {
  Board b1(20, 5);
  modifyBoardTestMethod(b1);
  b1.scoreUpdater();
  EXPECT_EQ(b1.getScoreP1(), 0);
  *(b1.getCell(0, 1)->getLine(0)) = PLAYER2;
  Board b1copy = b1;
  EXPECT_EQ(*(b1copy.getCell(0, 1)->getLine(0)), PLAYER2);
  EXPECT_EQ(b1copy.getScoreP1(), 0);
}

bool duplicadeMovesTestMethod(vector<Movement>& moves){
	for (int i = 0; i < moves.size(); i++) {
		for (int j = 0; j < moves.size(); j++) {
			if (i != j && moves[i].getXPos() == moves[j].getXPos() &&
				moves[i].getYPos() == moves[j].getYPos() &&
				moves[i].getLineDirection() == moves[j].getLineDirection()) {
				return true;
			}
		}
	}
	return false;
}

TEST(BoardTest, AvailableMovesTest) {
  Board b1(12, 8);
  vector<Movement> moves = b1.getAvailableMoves();
  EXPECT_FALSE(duplicadeMovesTestMethod(moves));

	Board b2(15,15);
	for(int i = 0; i<3; i++){
		*(b2.getCell(i,i)->getLine(0)) = PLAYER2;
		*(b2.getCell(i,i)->getLine(1)) = PLAYER2;
		*(b2.getCell(i,i)->getLine(2)) = PLAYER2;
		*(b2.getCell(i,i)->getLine(3)) = PLAYER2;
		b2.getCell(i,i)->boxChecker(PLAYER2);
	}
	b2.scoreUpdater();
	EXPECT_EQ(b2.getScoreP2(), 3);
	moves = b2.getAvailableMoves();
	EXPECT_EQ(moves.size(), (14*14*4)-(3*4));
	EXPECT_FALSE(duplicadeMovesTestMethod(moves));
}

TEST(MovementTest, OnBoardPlayTest){
  Board b1(5,5);
  Movement m1(45,78, EAST);
  Movement m2(0,1,NORTH);
  Movement m3(1,1,NORTH);
  Movement m4(0,2,WEST);
  Movement m5(0,1,EAST);
  EXPECT_FALSE(m1.play(b1, PLAYER1));
  EXPECT_TRUE(m2.play(b1, PLAYER1));
  EXPECT_TRUE(m3.play(b1, PLAYER1));
  EXPECT_TRUE(m4.play(b1, PLAYER1));
  EXPECT_FALSE(m5.play(b1, PLAYER1));
  EXPECT_EQ(*(b1.getCell(0,2)->getLine(0)), PLAYER1);
  EXPECT_EQ(*(b1.getCell(0,1)->getLine(1)), PLAYER1);
}

//TODO(Andres): Pruebas Unitarias a Player::Random, PlayerMid y PlayerEasy.