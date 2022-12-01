#pragma once
#include <string>

namespace models
{
    class Case
    {
    private:
        int x;
        int y;
        char value;
    public:
        Case(void);        
        Case(int _x, int _y, char val);
        char GetValue(void);
        void SetValue(char val); 
        int GetX(void);
        void SetX(int _x); 
        int GetY(void);
        void SetY(int _y);
    };
}

