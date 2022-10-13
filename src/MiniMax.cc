#include "MiniMax.hh"

MiniMax::MiniMax(Board board, bool isMaxPlayer, int depth) : myBoard(board), 
            maxPlayer(isMaxPlayer), myDepth(depth), bestMove(-1, -1, EMPTY) {
        availableMoves = myBoard.getAvailableMoves();
        myBoard.scoreUpdater();
    }

MiniMax::~MiniMax() {
}


int MiniMax::performMiniMax(bool root) {
    cout << "------------------------------" << endl;
    // Considerar al jugador 1 como max. 
        int remainingMoves = availableMoves.size(); 
        cout << "remainingMoves calculated" << endl; //TODO: delete
        cout << "remainingMoves value is: " << remainingMoves << endl;
         /*
        while (!availableMoves.empty()) {
            Movement currentMove = availableMoves.back();
            availableMoves.pop_back();
            cout << "Posicion X: " << currentMove.getXPos() << " Posicion Y: " <<
                currentMove.getXPos() << " Direccion: " << currentMove.getLineDirection() << endl;
        }
        for (int i = 0; i < availableMoves.size(); i++) {
            cout << "i value: " << i;
            Movement currentMove = availableMoves[i];
            cout << "Posicion X: " << currentMove.getXPos() << " Posicion Y: " <<
                currentMove.getXPos() << " Direccion: " << currentMove.getLineDirection() << endl;
        
        }*/ 

    
    // Calculamos la diferencia de puntajes para saber quien va ganando el juego. 
        int deltaScore = myBoard.getScoreP1() - myBoard.getScoreP2(); 
        cout << "deltaScore calulated" << endl; //TODO: delete 
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
           cout << "myDepth value es 0. "<< endl; //TODO: delete 
           cout << "deltaScore value is: " << deltaScore << endl; //TODO: delete
        return deltaScore;
       }

        int score; 
        // int childrenQuantity = children.size(); 
        // Si el jugador es max
        if(maxPlayer){
            score = -100000; 
            for (int i = 0; i < remainingMoves; i++)
            {
                cout << "Inicio for" << endl;
                cout << "MAX................" << endl;
                Board currentBoard = myBoard; //¿Se borra del stack el objeto anterior? 
                cout << "El tamaño de availableMoves es: " << availableMoves.size() << endl;
                cout << "El valor de i es " << i << endl;  

                
                Movement currentMove = availableMoves[i]; 
                cout << "Current move x:" << currentMove.getXPos() << endl;

                for (int i = 0; i < availableMoves.size(); i++) {
                    cout << "i value: " << i;
                    Movement currentMove = availableMoves[i];
                    cout << " Posicion X: " << currentMove.getXPos() << " Posicion Y: " <<
                        currentMove.getYPos() << " Direccion: " << currentMove.getLineDirection() << endl;

                }


                cout << currentBoard.getAvailableMoves().size() << endl;
                cout << "Antes de jugar" << endl;
                
                currentMove.play(currentBoard, PLAYER1); 

                cout << "Despues de jugar" << endl; 
                cout << "childMiniMax called with Depth-1 = " << myDepth-1 << endl; //TODO: delete 
                MiniMax childMiniMax = {currentBoard, false, myDepth-1}; 
                int childScore = childMiniMax.performMiniMax(false); 
                cout << "Minimax Finished " << endl; //TODO: delete 
                
                if (childScore > score){
                    score = childScore;  
                    if (root) { setBestMove(score, currentMove); }
                }
                cout << "score value: " << score << endl; 

                
            } 
        // Si el jugador es mini 
        } else {
            score = 100000; 
            for (int i = 0; i < remainingMoves; i++)
            {
                cout << "MIN................" << endl; 
                Board currentBoard = myBoard; //¿Se borra del stack el objeto anterior? 
                Movement currentMove = availableMoves[i]; 
                currentMove.play(currentBoard, PLAYER2); 
                cout << "childMiniMax called with Depth-1 = " << myDepth - 1 << endl; //TODO: delete 
                MiniMax childMiniMax = {currentBoard, true, myDepth-1}; 
                int childScore = childMiniMax.performMiniMax(false);
                
                if (childScore < score){
                    score = childScore; 
                    if (root) { setBestMove(score, currentMove); }
                } 
                cout << "score value: " << score << endl;
            } 
        }

        return score; 

}

void MiniMax::setBestMove(int score, Movement move){

    bestMove = move; 
} 


Movement MiniMax::getBestMove(){
    return bestMove; 
}
