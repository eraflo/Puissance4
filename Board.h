#pragma once
#include "Case.h"
#include <iostream>
#include <string>

namespace models
{
    class Board
    {
    private:
        int nbCol;
        int nbRow;
        Case** board;
        int winner;
        int** createMatrice(void);
        int* detectLigne(int**);
        int* detectCol(int**);
        int detectDiagoPrin(int**);
        int detectAutreDiago(int**);
        int** SysM(int**);
        bool detect(int**);
        void dispMat(int**);
    public:
        Board(void);
        Board(int, int);
        Board(const Board&);
        int getWinner(void);
        void Display(void);
        bool AddToken(int, char);
        bool WinRules(void);
        int compteR(int);
        int colonnePleine(int);
        Case** getValue(void);
        void copie(models::Board*);
    };
}

