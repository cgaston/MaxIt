#pragma once
#include "Player.h"
class HumanPlayer
	: public Player
{
public:
	HumanPlayer();
	~HumanPlayer();
	void resetGame();
	int move(MIBoard& b1, int rowOrCol, char playerIndex);
};

