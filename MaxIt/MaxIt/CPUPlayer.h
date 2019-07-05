#pragma once
#include "Player.h"
class CPUPlayer
	: public Player
{
public:
	CPUPlayer();
	~CPUPlayer();
	void resetGame();
	int move(MIBoard& b1, int rowOrCol, int isRow);
};

