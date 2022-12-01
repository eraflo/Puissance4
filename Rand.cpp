#include "Rand.h"


int Structure::Rand::cnt = 0;
void Structure::Rand::checkSeed(void)
{
    if ((!cnt) || (cnt > 10000))
    {
        srand(time(NULL));
        cnt = 0;
    }
}

void Structure::Rand::newSeed(int s)
{
    srand(s);
}

int Structure::Rand::randi(void)
{
    checkSeed();
    return rand();
}

int Structure::Rand::randi(int max)
{
    checkSeed();
    if (max)
        return rand() % max;
    return 0;
}
