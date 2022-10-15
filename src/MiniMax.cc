#include "MiniMax.hh"

MiniMax::MiniMax(Board board, bool isMaxPlayer, int depth) : myBoard(board), 
            maxPlayer(isMaxPlayer), myDepth(depth), bestMove(-1, -1, EMPTY) {
        availableMoves = myBoard.getAvailableMoves();
        myBoard.scoreUpdater();
    }

MiniMax::~MiniMax() {
}


short MiniMax::performMiniMax(bool root) {
    // Considerar al jugador 1 como max. 
        int remainingMoves = availableMoves.size(); 

    // Calculamos la diferencia de puntajes para saber quien va ganando el juego. 
        int deltaScore = myBoard.getScoreP1() - myBoard.getScoreP2(); 

    // Si es el final del juego:
       if (remainingMoves == 0){
        // Si Max gana, devuelva 10000
        if(deltaScore > 0){
            return 10000; 
        }
        // Si max pierde, devuelva -10000; 
        if(deltaScore < 0){
            return -10000;
        }
        // Si hay empate, devuelva 0; 
        return 0; 
       }

       // Devuelva el valor heuristico 
       if (myDepth == 0){
        return deltaScore;
       }

        int score; 
        // int childrenQuantity = children.size(); 
        // Si el jugador es max
        if(maxPlayer){
            score = -100000; 
            for (int i = 0; i < remainingMoves; i++)
            {
                Board currentBoard = myBoard; 

                Movement currentMove = availableMoves[i]; 
                
                currentMove.playAndAssignOwner(currentBoard, PLAYER1); // TODO: debo agregar este metodo a clase Movement 


                MiniMax childMiniMax = {currentBoard, false, myDepth-1}; 
                int childScore = childMiniMax.performMiniMax(false); 
                
                if (childScore > score){
                    score = childScore;  
                    if (root) { setBestMove(currentMove); }
                }                
            } 
        // Si el jugador es mini 
        } else {
            score = 100000; 
            for (int i = 0; i < remainingMoves; i++)
            {
                Board currentBoard = myBoard; 
                Movement currentMove = availableMoves[i]; 
                currentMove.playAndAssignOwner(currentBoard, PLAYER2);
                MiniMax childMiniMax = {currentBoard, true, myDepth-1}; 
                int childScore = childMiniMax.performMiniMax(false);
                
                if (childScore < score){
                    score = childScore; 
                    if (root) { setBestMove(currentMove); }
                } 
            } 
        }
        return score; 
}

void MiniMax::setBestMove(Movement move){
    bestMove = move; 
} 


Movement MiniMax::getBestMove(){
    return bestMove; 
}
