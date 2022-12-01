#pragma once
#include <iostream>
#include <string>

namespace models
{
	class Player
	{
	private:
		int id;
		std::string nickname;
	public:
		Player(void);
		Player(std::string);
		std::string GetNickname(void);
	};
}

