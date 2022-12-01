#include "Player.h"

models::Player::Player(void)
{
	this->id = 0;
	this->nickname = "Unknown";
}

models::Player::Player(std::string name)
{
	this->id = 0;
	this->nickname = name;
}

std::string models::Player::GetNickname(void)
{
	return this->nickname;
}
