#pragma once
#include "Player.h"
class CPUPlayer
	: public Player
{
public:
	CPUPlayer();
	~CPUPlayer();
	void resetGame();
	int move(MIBoard& b1, int rowOrCol, char playerIndex, int score);
private:
	int negamax(MIBoard& b1, int score, int depth, int rowOrCol, char playerIndex, bool isInitialCase);
};

