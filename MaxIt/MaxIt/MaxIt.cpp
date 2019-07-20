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
//	srand(time(NULL));
	int boardSize = getUserResponse("Enter a board size(4-9): ", "3456789") + 3;
	MIBoard m1(boardSize, boardSize);
	Player* p1;
	Player* p2;
	int numPlayer = getUserResponse("How many players do you want (1-2)?: ", "012");
	if (numPlayer == 0)
	{
		p1 = new CPUPlayer(0, 10);
		p2 = new CPUPlayer(1, 10);
	}
	else if (numPlayer == 1)
	{
		int whoFirst = getUserResponse("Do you want to go first?: ", "YN");
		if (whoFirst == 0)
		{
			p1 = new HumanPlayer(0);
			p2 = new CPUPlayer(1, 3);
		}
		else
		{
			p1 = new CPUPlayer(0, 3);
			p2 = new HumanPlayer(1);
		}
	}
	else
	{
		p1 = new HumanPlayer(0);
		p2 = new HumanPlayer(1);
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
	Player* players[2]{ &p1, &p2 }; //holds player references
	int move = rand() % b1.getRowSize(); //sets initial row to a random pick (0 based)
	char curPlayer = 0; //used to keep track of whose turn it is
	int row, col, currRowOrCol;
	do
	{
		b1.displayBoard();
		printf("Player 1 score: %d | Player 2 score: %d\n", p1.getPlayerScore(), p2.getPlayerScore()); //Print player score before each move
		currRowOrCol = move;
		move = players[curPlayer]->move(b1, currRowOrCol, curPlayer, players[curPlayer]->getPlayerScore() - players[1-curPlayer]->getPlayerScore()); //Get move from player whos turn it is as a row or column index (0-based)
		if (curPlayer == 0) //player 1 chooses columns
		{
			row = currRowOrCol;
			col = move;
		}
		else //player 2 chooses rows
		{
			row = move;
			col = currRowOrCol;
		}
		players[curPlayer]->addToScore(b1.doMove(row, col)); //make the move and add score to current players total based on return value from move function
		curPlayer = 1 - curPlayer; //change current player from 0 to 1 or vice versa
	} while (!b1.noMoves(move, curPlayer)); //play game until there are not moves left
	b1.displayBoard(); //display board and players final score
	printf("       Player 1      Player 2\n");
	printf("Score:   %3d           %3d  \n", p1.getPlayerScore(), p2.getPlayerScore());
	if (p1.getPlayerScore() == p2.getPlayerScore()) //display end result of the game and player that won if applicable
		printf("It was a tie\n");
	else
		printf("Player %d wins!\n", (int)(p1.getPlayerScore() < p2.getPlayerScore()) + 1);
}
