#pragma once
#include "Player.h"
class HumanPlayer
	: public Player
{
public:
	HumanPlayer(int p);
	~HumanPlayer();
	int move(MIBoard& b1, int rowOrCol, char playerIndex, int /*score*/);
};

