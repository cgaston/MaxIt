#pragma once
#include "Player.h"
class HumanPlayer
	: public Player
{
public:
	HumanPlayer();
	~HumanPlayer();
	int move(MIBoard& b1, int rowOrCol, char playerIndex, int /*score*/);
};

