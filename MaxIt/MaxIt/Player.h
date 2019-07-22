#pragma once
#include "MIBoard.h"

class Player
{
public:
	Player();
	~Player();
	virtual void resetGame();
	virtual int move(MIBoard& b1, int rowOrCol, char playerIndex, int score) = 0;
	virtual int getPlayerScore() { return playerScore; }
	virtual void addToScore(int num1) { playerScore += num1; }
protected:
	int playerScore;
};

