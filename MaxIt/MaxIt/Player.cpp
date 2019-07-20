#include "Player.h"



Player::Player(int p)
	: playerScore(0), playerNum(p)
{
}


Player::~Player()
{
}


void Player::resetGame()
{
	playerScore = 0;
}
