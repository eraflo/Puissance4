#pragma once
#include <iostream>
#include "Minimax.h"
#include "Player.h"

namespace controllers
{
	class Game
	{
	private:
		models::Board* board;
		models::Player* Player;
		bool IAOn;
		bool gameOn;
		bool exit;
		int difficulte;
	public:
		Game(void);
		void Menu(void);
		void Play(void);
		void PlayIA(void);
		void CreatePlayer(void);
		void choixDiff(void);
	};
}


