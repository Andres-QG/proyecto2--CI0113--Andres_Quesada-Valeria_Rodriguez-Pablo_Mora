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
        short remainingMoves = availableMoves.size(); 

    // Calculamos la diferencia de puntajes para saber quien va ganando el juego. 
        short deltaScore = myBoard.getScoreP1() - myBoard.getScoreP2(); 

    // Si es el final del juego:
       if (remainingMoves == 0){
            // Si Max gana, devuelva 1000
            if(deltaScore > 0){
                return 1000; 
            }
            // Si max pierde, devuelva -1000; 
            if(deltaScore < 0){
                return -1000;
            }
            // Si hay empate, devuelva 0; 
            return 0; 
       }

       // Devuelva el valor heuristico 
       if (myDepth == 0){
        return deltaScore;
       }

        short score; 
        // Si el jugador es max
        if(maxPlayer){
            score = -1000; 
            for (int i = 0; i < remainingMoves; i++)
            {
                //Creamos un nuevo tablero para no modificar el "original". 
                Board currentBoard = myBoard; 
                Movement currentMove = availableMoves[i]; 

                short childScore = -1000;
                //Si al jugar, se completó una celda entonces el jugador 1 tiene un turno extra. 
                if (currentMove.playAndAssignOwner(currentBoard, PLAYER1) == PLAYER1) {// TODO: debo agregar este método a clase Movement 
                    //El siguiente turno corresponde al jugador max. 
                    MiniMax childMiniMax = { currentBoard, true, myDepth - 1 };
                    childScore = childMiniMax.performMiniMax(false);
                }
                else {
                    //El siguiente turno corresponde al jugador min. 
                    MiniMax childMiniMax = { currentBoard, false, myDepth - 1 };
                    childScore = childMiniMax.performMiniMax(false);
                }
               
                if (childScore > score){
                    score = childScore;
                    // Unicamente guardamos el movimiento cuando estamos en el primer nivel del árbol. 
                    if (root) { setBestMove(currentMove); }
                }                
            } 
        // Si el jugador es mini 
        } else {
            score = 1000; 
            for (int i = 0; i < remainingMoves; i++)
            {
                Board currentBoard = myBoard; 
                Movement currentMove = availableMoves[i]; 

                short childScore = 1000;
                //Si al jugar, se completó una celda entonces el jugador 2 tiene un turno extra. 
                if (currentMove.playAndAssignOwner(currentBoard, PLAYER2) == PLAYER2) {// TODO: debo agregar este método a clase Movement 
                    //El siguiente turno corresponde al jugador min. 
                    MiniMax childMiniMax = { currentBoard, false, myDepth - 1 };
                    childScore = childMiniMax.performMiniMax(false);
                }
                else {
                    //El siguiente turno corresponde al jugador max. 
                    MiniMax childMiniMax = { currentBoard, true, myDepth - 1 };
                    childScore = childMiniMax.performMiniMax(false);
                }      
                
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
