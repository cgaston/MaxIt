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
	int changeSettings = 0;
	Player* p1 = 0;
	Player* p2 = 0;
	MIBoard* m1 = 0;
	do
	{
		if (changeSettings == 0)
		{
			int boardSize = getUserResponse("Enter a board size(4-9): ", "3456789") + 3;
			m1 = new MIBoard(boardSize, boardSize);
			int numPlayer = getUserResponse("How many players do you want (1-2)?: ", "012");
			if (numPlayer == 0)
			{
				p1 = new CPUPlayer(9);
				p2 = new CPUPlayer(9);
			}
			else if (numPlayer == 1)
			{
				int whoFirst = getUserResponse("Do you want to go first?: ", "YN");
				int difficulty = getUserResponse("How good do you want the computer to play (1-9): ", "123456789");
				if (whoFirst == 0)
				{
					p1 = new HumanPlayer();
					p2 = new CPUPlayer(difficulty + 1);
				}
				else
				{
					p1 = new CPUPlayer(difficulty + 1);
					p2 = new HumanPlayer();
				}
			}
			else
			{
				p1 = new HumanPlayer();
				p2 = new HumanPlayer();
			}
		}
		m1->initBoard();
		playGame(*p1, *p2, *m1);
		int paResp = getUserResponse("Do you want to play again Y/N: ", "YN");
		if (paResp == 1)
			break;	
		changeSettings = getUserResponse("Do you want to change the settings Y/N: ", "YN");
		if (changeSettings == 0)
		{
			delete(p1);
			delete(p2);
			delete(m1);
		}
	} while (true);
	delete(p1);
	delete(p2);
	delete(m1);
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
																	//pass in relative score based on who's turn it is
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
