#ifndef MINIMAX_HH
#define MINIMAX_HH

#include "Board.hh"
#include "Movement.hh"
#include "Cell.hh"
using namespace std;

class MiniMax{
    private: 
        bool maxPlayer;
        short deltaScore; 
        short probability;
        int myDepth; 
        Movement bestMove; 
        vector <Movement> availableMoves; 
        void setBestMove(Movement move);
        
        Board myBoard; 


    public:
        MiniMax(Board board, bool isMaxPlayer, int depth); 
        short performMiniMax(bool root); 
        Movement getBestMove();


        ~MiniMax(); 





}; 

#endif

