#pragma once
#include "Player.h"
class CPUPlayer
	: public Player
{
public:
	CPUPlayer(int depth = 4);
	~CPUPlayer();
	int move(MIBoard& b1, int rowOrCol, char playerIndex, int score);
private:
	int negamax(MIBoard& b1, int score, int depth, int rowOrCol, char playerIndex, bool isInitialCase);
	int bestscore;
	int maxdepth;
//	int bestline[maxdepth];
};

