#pragma once
#include "Board.h"
#include "Rand.h"
#include <iostream>
#include <math.h>

namespace IA
{
	const int MAX_VALUE = 100000;
	const int MIN_VALUE = -100000;
	class Minimax
	{
	private:
		models::Board* board;
		int profondeur;
	public:
		Minimax(int);
		int alphaBeta(models::Board*, int);
		double minimax(models::Board*, int, int);
		double min(models::Board*, int, int, double, double);
		double max(models::Board*, int, int, double, double);

		void retirerJeton(models::Board*, int);

		//heuristique
		double noteGrille(models::Board*, int);
		double chercheAlignementDeJeton(models::Board*, int, int, int, int, int, int);
	};
}


