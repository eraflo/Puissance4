#include "Board.h"

models::Board::Board(void) : nbCol(0), nbRow(0), winner(-1)
{
	this->board = new Case * [0];
}

models::Board::Board(int cols, int rows) : nbCol(cols), nbRow(rows), winner(-1)
{
	this->board = new Case * [rows];
	for (int i = 0; i < rows; i++)
	{
		this->board[i] = new Case[cols];
	}
}

models::Board::Board(const Board& board)
{
	this->nbCol = board.nbCol;
	this->nbRow = board.nbRow;
	this->winner = board.winner;
	this->board = board.board;
}

int models::Board::getWinner(void)
{
	return this->winner;
}

int** models::Board::createMatrice(void)
{
	int** tab = new int* [nbRow];
	for (int i = 0; i < nbRow; i++)
	{
		tab[i] = new int[nbCol];
	}
	for (int i = 0; i < nbRow; i++)
	{
		for (int j = 0; j < nbCol; j++)
		{
			if (this->board[i][j].GetValue() == '.')
			{
				tab[i][j] = 0;
			}
			else if (this->board[i][j].GetValue() == 'R')
			{
				tab[i][j] = 1;
			}
			else if (this->board[i][j].GetValue() == 'Y')
			{
				tab[i][j] = -1;
			}
		}
	}
	return tab;
}

int* models::Board::detectLigne(int** matrice)
{
	int* result = new int[4];
	int* resultatFin = new int[4];

	for (int i = 0; i < 4; i++)
	{
		result = matrice[i];
		resultatFin[i] = 0;
		for (int j = 0; j < 4; j++)
		{
			resultatFin[i] += result[j];
		}
	}

	return resultatFin;
}

int* models::Board::detectCol(int** matrice)
{
	int* result = new int[4];
	int* resultatFin = new int[4];

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[j] = matrice[j][i];
		}
		resultatFin[i] = 0;
		for (int j = 0; j < 4; j++)
		{
			resultatFin[i] += result[j];
		}
	}

	return resultatFin;
}

int models::Board::detectDiagoPrin(int** matrice)
{
	int result = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
			{
				result += matrice[i][j];
			}
		}
	}

	return result;
}

int models::Board::detectAutreDiago(int **matrice)
{
	int** mat = this->SysM(matrice);
	int result = this->detectDiagoPrin(mat);

	return result;
}

int** models::Board::SysM(int** matrice)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			int temp = matrice[i][j];
			matrice[i][j] = matrice[i][3 - j];
			matrice[i][3 - j] = temp;
		}
	}

	return matrice;
}

bool models::Board::detect(int** matrice)
{
	bool resultFin = false;
	int** matInter = new int* [4];
	int* line;
	int* col;
	int diago;
	int diagoInvert;

	for (int i = 0; i < 4; i++)
	{
		matInter[i] = new int[4];
	}

	for (int i = 0; i < nbRow - 3; i++)
	{
		for (int j = 0; j < nbCol - 3; j++)
		{
			for (int h = 0; h < 4; h++)
			{
				for (int k = 0; k < 4; k++)
				{
					matInter[h][k] = matrice[i + h][j + k];
				}
			}
			line = this->detectLigne(matInter);
			col = this->detectCol(matInter);
			diago = this->detectDiagoPrin(matInter);
			diagoInvert = this->detectAutreDiago(matInter);
			for (int h = 0; h < 4; h++)
			{
				if (line[h] == 4)
				{
					this->winner = 0;
					resultFin = true;
				}
				else if (line[h] == -4)
				{
					this->winner = 1;
					resultFin = true;
				}
				if (col[h] == 4)
				{
					this->winner = 0;
					resultFin = true;
				}
				else if (col[h] == -4)
				{
					this->winner = 1;
					resultFin = true;
				}
			}
			if (diago == 4 || diagoInvert == 4)
			{
				this->winner = 0;
				resultFin = true;
			}
			else if (diago == -4 || diagoInvert == -4)
			{
				this->winner = 1;
				resultFin = true;
			}
		}
	}

	return resultFin;
}

void models::Board::dispMat(int** matrice)
{
	for (int i = 0; i < nbRow; i++)
	{
		for (int j = 0; j < nbCol; j++)
		{
			std::cout << matrice[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void models::Board::Display(void)
{
	std::string message = "";

	for (int m = 0; m < this->nbCol; m++)
	{
		message += "  " + std::to_string(m+1) + " ";
	}
	message += "\n";

	for (int j = 0; j < this->nbCol; j++)
	{
		message += "*---";
	}
	message += "*";
	message += "\n";

	int i = 0;
	for (i = 0; i < this->nbRow; i++)
	{
		message += "| ";
		for (int j = 0; j < this->nbCol; j++)
		{
			message += this->board[i][j].GetValue();
			message += " | ";
		}
		message += "\n";

	}

	for (int j = 0; j < this->nbCol; j++)
	{
		message += "*---";
	}
	message += "*";
	message += "\n";


	std::cout << message << std::endl;
}

bool models::Board::AddToken(int col, char val)
{
	bool rempli = false;
	for (int i = this->nbRow-1; i > -1; i--)
	{
		if (this->board[i][col].GetValue() == '.')
		{
			this->board[i][col].SetValue(val);
			this->board[i][col].SetX(i);
			this->board[i][col].SetY(col);
			rempli = true;
			break;
		}
	}
	return rempli;
}

bool models::Board::WinRules(void)
{
	bool win = false;
	win = this->detect(this->createMatrice());
	return win;
}

int models::Board::compteR(int col)
{
	int compte = 1;
	for (int i = 0; i < nbRow; i++)
	{
		if (this->board[i][col].GetValue() != '.')
		{
			compte++;
		}
	}
	return compte;
}

int models::Board::colonnePleine(int i)
{
	int indexMax = 0;
	for (int j = nbRow; j >= 1 && indexMax == 0; j--)
	{
		if (this->getValue()[i][j].GetValue() != '.')
		{
			indexMax = j;
		}
	}
	return indexMax;
}

models::Case** models::Board::getValue(void)
{
	return this->board;
}

void models::Board::copie(models::Board* _board)
{
	for (int i = 0; i < nbRow; i++)
	{
		for (int j = 0; j < nbCol; j++)
		{
			this->board[i][j].SetValue(_board->board[i][j].GetValue());
		}
	}
}


