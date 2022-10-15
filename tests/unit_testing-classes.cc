#include <gtest/gtest.h>
#include "MiniMax.hh"

// Para miniMax voy a usar una matriz de 2x2 celdas. 
// TODO: cuando se tenga un método que no devuelva jugadas repetidas, es posible que haya que reconstruir las pruebas. 
TEST(MiniMaxTest, FirstTwoMovements ) {
	//Matriz 2x2 celdas 
	Board board = { 3,3 };
	MiniMax miniMax = { board, true, 4 };
	miniMax.performMiniMax(true);
	Movement bestMove = miniMax.getBestMove();
	bestMove.play(board, PLAYER1);

	// Primer movimiento 
	EXPECT_TRUE(bestMove.getXPos() == 0 && bestMove.getYPos() == 0 && bestMove.getLineDirection() == EAST); //TODO: puede cambiar con nuevo método getMovements(). 


	MiniMax secondMiniMax = { board, false, 4 };
	secondMiniMax.performMiniMax(true);
	bestMove = secondMiniMax.getBestMove();

	// Segundo Movimiento
	EXPECT_TRUE(bestMove.getXPos() == 0 && bestMove.getYPos() == 0 && bestMove.getLineDirection() == WEST);
}

// Básicamente que no regale una caja al completar una tercera línea. 
TEST(MiniMaxTest, NotCompleteThirdLine) {
	Board board = { 3,3 };
	Movement moveN = { 0,0, NORTH }; 
	moveN.play(board, PLAYER1);
	Movement moveS = { 0,0, SOUTH };
	moveS.play(board, PLAYER2);

	MiniMax miniMax = { board, false, 4 };
	miniMax.performMiniMax(true);
	Movement bestMove = miniMax.getBestMove(); 

	EXPECT_FALSE(bestMove.getXPos() == 0 && bestMove.getYPos() == 0 && bestMove.getLineDirection() == WEST);
	EXPECT_FALSE(bestMove.getXPos() == 0 && bestMove.getYPos() == 0 && bestMove.getLineDirection() == EAST);
	EXPECT_FALSE(bestMove.getXPos() == 0 && bestMove.getYPos() == 1 && bestMove.getLineDirection() == WEST);
	EXPECT_TRUE(bestMove.getXPos() == 0 && bestMove.getYPos() == 1 && bestMove.getLineDirection() == EAST); //TODO: puede cambiar con nuevo método getMovements(). 
}

// Que complete una celda 
TEST(MiniMaxTest, CompleteCell) {
	Board board = { 3,3 };
	Movement moveN = { 0,0, NORTH };
	moveN.play(board, PLAYER1);
	Movement moveS = { 0,0, SOUTH };
	moveS.play(board, PLAYER2);
	Movement moveE = { 0,0, EAST };
	moveE.play(board, PLAYER1);

	MiniMax miniMax = { board, false, 4 };
	miniMax.performMiniMax(true);
	Movement bestMove = miniMax.getBestMove();

	EXPECT_TRUE(bestMove.getXPos() == 0 && bestMove.getYPos() == 0 && bestMove.getLineDirection() == WEST);//TODO: puede cambiar con nuevo método getMovements(). 
}

TEST(MiniMaxTest, CompleteTwoCell) {
	Board board = { 3,3 };
	Movement moveN = { 0,1, NORTH };
	moveN.play(board, PLAYER1);
	Movement moveS = { 0,1, SOUTH };
	moveS.play(board, PLAYER2);
	Movement moveO = { 0,1, WEST };
	moveO.play(board, PLAYER1);
	Movement moveN2 = { 1,1, NORTH };
	moveN2.play(board, PLAYER2);
	Movement moveS2 = { 1,1, SOUTH };
	moveS2.play(board, PLAYER1);
	Movement moveE = { 1,1, EAST };
	moveE.play(board, PLAYER2);

	MiniMax miniMax = { board, true, 4 };
	miniMax.performMiniMax(true);
	Movement bestMove = miniMax.getBestMove();

	EXPECT_TRUE(bestMove.getXPos() == 1 && bestMove.getYPos() == 1 && bestMove.getLineDirection() == WEST); //TODO: puede cambiar con nuevo método getMovements(). 
}

