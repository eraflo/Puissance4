#include "Case.h"

models::Case::Case(void) 
{
    this->value = '.';
}

models::Case::Case(int _x, int _y, char val) : x(_x), y(_y), value(val)
{
}

char models::Case::GetValue(void)
{
    return this->value;
}

void models::Case::SetValue(char val)
{
    this->value = val;
}

int models::Case::GetX(void)
{
    return this->x;
}

void models::Case::SetX(int _x)
{
    this->x = _x;
}

int models::Case::GetY(void)
{
    return this->y;
}

void models::Case::SetY(int _y)
{
    this->y = _y;
}
