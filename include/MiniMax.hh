#ifndef MINIMAX
#define MINIMAX

#include "Board.hh"
#include "Movement.hh"
#include "Cell.hh"
using namespace std;

/*struct MiniMaxMove {
    MiniMaxMove(0, 0); 
    Movement miniMaxMove; 
    int deltaScore; 
};*/


class MiniMax{
    private: 
        bool maxPlayer;
        short deltaScore; 
        int myDepth; 
        double probability;
        Movement bestMove; 
        vector <Movement> availableMoves; 
        //bool terminalNode; 
        
        Board myBoard; 
        vector <Board> childNodes;


    public:
        //MiniMax();  
        MiniMax(Board board, bool isMaxPlayer, int depth); 
        int performMiniMax(bool root); 
        void setBestMove(int score, Movement move);
        Movement getBestMove();


        ~MiniMax(); 





}; 

#endif

