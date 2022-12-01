#include "Game.h"

controllers::Game::Game(void)
{
	models::Board* b1 = new models::Board(7, 6);
	this->board = b1;
	this->gameOn = false;
	this->IAOn = false;
	this->exit = false;
	this->Player = new models::Player[2];
	this->difficulte = 1;
	Menu();
}

void controllers::Game::Menu(void)
{
	std::string menu;
	int rep;
	menu += "************************************\n";
	menu += "Menu :\n";
	menu += "1 : Commencer la partie à 2 joueur\n";
	menu += "2 : Commencer la partie contre l'ordinateur\n";
	menu += "3 : Exit\n";
	while (exit != true)
	{
		models::Board* b1 = new models::Board(7, 6);
		std::cout << menu << std::endl;
		std::cout << "Quel est votre choix : ";
		std::cin >> rep;
		std::cout << std::endl;
		switch (rep)
		{
		case 1:
			this->board = b1;
			CreatePlayer();
			this->gameOn = true;
			Play();
			break;
		case 2:
			this->board = b1;
			this->IAOn = true;
			CreatePlayer();
			this->gameOn = true;
			this->choixDiff();
			this->PlayIA();
			break;
		case 3:
			exit = true;
			break;
		default:
			std::cout << "Mauvais choix" << std::endl;
			break;
		}
	}
}

void controllers::Game::Play(void)
{
	models::Player* player = &this->Player[0];
	int col;
	while (gameOn)
	{
		this->board->Display();
		std::cout << player->GetNickname() << ", où placer votre pion : ";
		std::cin >> col;
		if (col <= 7 and col > 0)
		{
			if (this->board->compteR(col-1) <= 6)
			{
				if (player == &this->Player[0])
				{
					this->board->AddToken(col - 1, 'R');
					player = &this->Player[1];
				}
				else if (player == &this->Player[1])
				{
					this->board->AddToken(col - 1, 'Y');
					player = &this->Player[0];
				}
			}
			else
			{
				std::cout << "Cet emplacement n'est pas valide" << std::endl;
			}
		}
		else
		{
			std::cout << "Cet emplacement n'est pas valide" << std::endl;
		}
		this->gameOn = !this->board->WinRules();
	}
}

void controllers::Game::PlayIA(void)
{
	models::Player* player = &this->Player[0];
	int col;
	while (gameOn)
	{
		this->board->Display();
		if (player == &this->Player[0])
		{
			std::cout << player->GetNickname() << ", où placer votre pion : ";
			std::cin >> col;
			if (col <= 7 and col >= 0)
			{
				if (this->board->compteR(col - 1) <= 6)
				{
					this->board->AddToken(col - 1, 'R');
					player = &this->Player[1];
				}
				else
				{
					std::cout << "Cet emplacement n'est pas valide" << std::endl;
				}
			}
			else
			{
				std::cout << "Cet emplacement n'est pas valide" << std::endl;
			}
		}
		else if (player == &this->Player[1])
		{
			IA::Minimax* ia = new IA::Minimax(this->difficulte);
			models::Board* tmp = new models::Board(7, 6);
			tmp->copie(this->board);
			int colJouer = ia->alphaBeta(tmp, 1);
			this->board->AddToken(colJouer, 'Y');
			player = &this->Player[0];
		}
		this->gameOn = !this->board->WinRules();
	}
}

void controllers::Game::CreatePlayer(void)
{
	int nb = 2;
	if (this->IAOn == true)
	{
		nb--;
		std::string name = "IA";
		models::Player* ia = new models::Player(name);
		this->Player[1] = *ia;
	}
	for (int i = 0; i < nb; i++)
	{
		std::string name;
		std::cout << "Quel est le nom du joueur " << i + 1 << " : ";
		std::cin >> name;
		std::cout << std::endl;
		models::Player* player = new models::Player(name);
		this->Player[i] = *player;
	}
}

void controllers::Game::choixDiff(void)
{
	int diff = 1;
	std::cout << "Choisissez une difficulté (1, 2 ou 3) : ";
	std::cin >> diff;
	std::cout << std::endl;
	switch (diff)
	{
	case 1:
		this->difficulte = 1;
		break;
	case 2:
		this->difficulte = 4;
		break;
	case 3:
		this->difficulte = 7;
		break;
	default:
		break;
	}
}
