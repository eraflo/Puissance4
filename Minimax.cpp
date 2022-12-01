#include "Minimax.h"
#include <list>
#include <array>
#include <algorithm>
#include <iostream>

IA::Minimax::Minimax(int prof) : profondeur(prof)
{
}

int IA::Minimax::alphaBeta(models::Board* board, int joueur)
{
	int colonneOpti = 0;
	
	double valeurJeu = MIN_VALUE;
	for (int i = 0; i < 6; i++)
	{
		if (!board->colonnePleine(i))
		{
			models::Board* copie = new models::Board(7, 6);
			copie->copie(board);
			if (joueur == 0)
			{
				copie->AddToken(i, 'R');
				joueur = 1;
			}
			else
			{
				copie->AddToken(i, 'Y');
				joueur = 0;
			}
			copie->WinRules();
			double valeurJeuCour = minimax(copie, joueur, this->profondeur);
			if (valeurJeuCour > valeurJeu)
			{
				colonneOpti = i;
				valeurJeu = valeurJeuCour;
			}
		}
	}

	return colonneOpti;

}

double IA::Minimax::minimax(models::Board* board, int depth, int joueur)
{
	double alpha = MIN_VALUE;
	double beta = MAX_VALUE;
	return this->min(board, joueur, depth, alpha, beta);
}

double IA::Minimax::min(models::Board* board, int joueur, int depth, double alpha, double beta)
{
	if (depth != 0)
	{
		double valeurJeu = MAX_VALUE;
		for (int i = 0; i < 6; i++)
		{
			if (!board->colonnePleine(i))
			{
				models::Board* copie = new models::Board(7, 6);
				copie->copie(board);
				if (joueur == 0)
				{
					copie->AddToken(i, 'R');
					joueur = 1;
				}
				else
				{
					copie->AddToken(i, 'Y');
					joueur = 0;
				}
				copie->WinRules();
				valeurJeu = std::min(valeurJeu, this->max(copie, joueur, depth - 1, alpha, beta));

				if (alpha >= valeurJeu)
				{
					return valeurJeu;
				}
				beta = std::min(beta, valeurJeu);
			}
		}
		return valeurJeu;
	}
	else
	{
		return this->noteGrille(board, joueur);
	}
}

double IA::Minimax::max(models::Board* board, int joueur, int depth, double alpha, double beta)
{
	if (depth != 0)
	{
		double valJeu = MIN_VALUE;
		for (int i = 0; i < 7; i++)
		{
			if (!board->colonnePleine(i))
			{
				models::Board* copie = new models::Board(7, 6);
				copie->copie(board);
				if (joueur == 0)
				{
					copie->AddToken(i, 'R');
					joueur = 1;
				}
				else
				{
					copie->AddToken(i, 'Y');
					joueur = 0;
				}
				copie->WinRules();
				valJeu = std::max(valJeu, this->min(copie, joueur, depth - 1, alpha, beta));

				if (beta <= valJeu)
				{
					return valJeu;
				}
				beta = std::max(alpha, valJeu);
			}
		}
		return valJeu;
	}
	else
	{
		return this->noteGrille(board, joueur);
	}
}

void IA::Minimax::retirerJeton(models::Board* board, int col)
{
	for (int i = 0; i <= 5; i++)
	{
		if (board->getValue()[col][i].GetValue() != '.')
		{
			board->getValue()[col][i].SetValue('.');
			break;
		}
	}
}

double IA::Minimax::noteGrille(models::Board* board, int joueur)
{
	if (board->getWinner() == 0)
		return MIN_VALUE;
	if (board->getWinner() == 1)
		return MAX_VALUE;

	double resultat = 0;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			resultat += this->chercheAlignementDeJeton(board, 4, joueur, i, j, 0, 1);
			resultat += this->chercheAlignementDeJeton(board, 4, joueur, i, j, 1, 1);
			resultat += this->chercheAlignementDeJeton(board, 4, joueur, i, j, 1, 0);
			resultat += this->chercheAlignementDeJeton(board, 4, joueur, i, j, 1, -1);
			resultat += this->chercheAlignementDeJeton(board, 4, joueur, i, j, 0, -1);
			resultat += this->chercheAlignementDeJeton(board, 4, joueur, i, j, -1, -1);
			resultat += this->chercheAlignementDeJeton(board, 4, joueur, i, j, -1, 0);
			resultat += this->chercheAlignementDeJeton(board, 4, joueur, i, j, -1, 1);
		}
	}
	return resultat;
}

double IA::Minimax::chercheAlignementDeJeton(models::Board* board, int taille, int joueur, int i, int j, int declineH, int declinV)
{
	double resultat = 1;
	while (taille != 0 && resultat != 0)
	{
		int jeton = -1;

		if (i < 6 and i >= 0)
		{
			if (j < 7 and j >= 0)
			{
				if (board->getValue()[i][j].GetValue() == 'R')
				{
					jeton = 0;
				}
				else if (board->getValue()[i][j].GetValue() == 'Y')
				{
					jeton = 1;
				}
			}
			else
			{
				resultat = 0;
			}
		}
		else
		{
			resultat = 0;
		}
		
		if (jeton == -1)
		{
			resultat *= 0.5;
		}
		else if (jeton == joueur)
		{
			resultat *= 1.0;
		}
		else
		{
			resultat *= 0;
		}

		i += declineH;
		j += declinV;
		taille--;

	}
	return resultat;
}
