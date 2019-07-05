#pragma once
#include "MIBoard.h"



class Player
{
public:
	Player();
	~Player();
	virtual void resetGame() = 0;
	virtual int move(MIBoard& b1, int rowOrCol, int isRow) = 0;
	virtual int getPlayerScore() { return playerScore; }
	virtual void addToScore(int num1) { playerScore += num1; }
private:
	int playerScore;
};

