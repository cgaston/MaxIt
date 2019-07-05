// MaxIt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "GlobalFunctions.h"
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include "HumanPlayer.h"
#include "CPUPlayer.h"

void playGame(Player& p1, Player& p2, MIBoard& b1);

int main()
{
	srand(time(NULL));
	int boardSize = getUserResponse("Enter a board size(4-9): ", "456789") + 4;
	MIBoard m1(boardSize, boardSize);
	Player* p1;
	Player* p2;
	int numPlayer = getUserResponse("How many players do you want (1-2)?: ", "012");
	if (numPlayer == 0)
	{
		p1 = new CPUPlayer;
		p2 = new CPUPlayer;
	}
	else if (numPlayer == 1)
	{
		p1 = new HumanPlayer;
		p2 = new CPUPlayer;
	}
	else
	{
		p1 = new HumanPlayer;
		p2 = new HumanPlayer;
	}

	do
	{
		m1.initBoard();
		playGame(*p1, *p2, m1);

		int paResp = getUserResponse("Do you want to play again Y/N: ", "YN");
		if (paResp == 1)
			break;
	} while (true);
	delete(p1);
	delete(p2);
}

void playGame(Player& p1, Player& p2, MIBoard& b1)
{
	p1.resetGame();
	p2.resetGame();
	Player* players[2]{ &p1, &p2 };
	bool p1Moves = true;
	int move = rand() % b1.getRowSize();
	char curPlayer = 0;
	int row, col, currRowOrCol;
	do
	{
		b1.displayBoard();
		printf("Player 1 score: %d | Player 2 score: %d\n", p1.getPlayerScore(), p2.getPlayerScore());
		currRowOrCol = move;
		move = players[curPlayer]->move(b1, currRowOrCol, p1Moves);
		if (p1Moves)
		{
			row = currRowOrCol;
			col = move;
		}
		else
		{
			row = move;
			col = currRowOrCol;
		}
		players[curPlayer]->addToScore(b1.deleteCell(row, col));
		curPlayer = 1 - curPlayer;
		p1Moves = !p1Moves;
	} while (!b1.noMoves(currRowOrCol, p1Moves));
	b1.displayBoard();
	printf("       Player 1      Player 2\n");
	printf("Score:   %3d           %3d  \n", p1.getPlayerScore(), p2.getPlayerScore());
	if (p1.getPlayerScore() == p2.getPlayerScore())
		printf("It was a tie\n");
	else
		printf("Player %d wins!\n", (int)(p1.getPlayerScore() < p2.getPlayerScore()) + 1);
}
