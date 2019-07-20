#include "CPUPlayer.h"
#include "array"


using namespace std;

CPUPlayer::CPUPlayer(int pNum)
	: pNum(pNum)
{
}


CPUPlayer::~CPUPlayer()
{
}

void CPUPlayer::resetGame()
{
	playerScore = 0;
}

int CPUPlayer::move(MIBoard& b1, int rowOrCol, char playerIndex, int score)
{
	int movePick;
	string s1;
	char c1;
	if (playerIndex == 0)
	{
		s1 = "column";
		c1 = 'A';
	}
	else
	{
		s1 = "row";
		c1 = '1';
	}
	movePick = negamax(b1, score, 9, rowOrCol, playerIndex, true);
	printf("\nCPU chose %s %c\n\n", s1.c_str(), movePick + c1);
	return movePick;
}

int CPUPlayer::negamax(MIBoard& b1, int score, int depth, int rowOrCol, char playerIndex, bool isInitialCase)
{
	printf("%*sDepth: %d | Player: %d | Score: %d | \n", 10 - depth, " ", depth, playerIndex+1, score);
	int* validMoves = new int[b1.getRowSize()]; //create array to hold valid moves with max size being the row size of the board
	int row, col, cellVal, numLegalMoves, value, bestmove = 0, bestvalue = -INT_MAX; //declare and initialize variables

	if (depth == 0) //depth has been reached
	{
		delete[] validMoves;
		return score; //return final score of this series of moves
	}
	numLegalMoves = b1.makeMoveList(validMoves, rowOrCol, playerIndex); //initialize list of legal moves and store the number of them in variable
	if (numLegalMoves == 0) //if number of legal moves is 0, then the search thinks the game has ended
	{
		delete[] validMoves;
		if (score > 0) 
		{
			printf("Player %d has won\n", playerIndex+1);
			if (playerIndex == pNum)
			{
				return (depth) * 1000;  //INT_MAX;//score*100; // -INT_MAX;
			}
			else
			{
				return (10 - depth) * 1000;  //INT_MAX;//score*100; // -INT_MAX;
			}
		}
		else if (score < 0)
		{
			printf("Player %d has lost\n", playerIndex+1);
			if (playerIndex == pNum)
			{
				return (depth) * -1000;  //INT_MAX;//score*100; // -INT_MAX;
			}
			else
			{
				return (10 - depth) * 1000;  //INT_MAX;//score*100; // -INT_MAX;
			}
		}
		return 0;
	}

	for (int i = 0; i < numLegalMoves; i++)
	{
		if (playerIndex == 0)
		{
			row = rowOrCol;
			col = validMoves[i];
		}
		else
		{
			row = validMoves[i];
			col = rowOrCol;
		}
		cellVal = b1.doMove(row, col);
		printf("Trying move: %d\n", validMoves[i]);
		value = -negamax(b1, -(cellVal + score), depth - 1, validMoves[i], 1 - playerIndex, false);
		b1.undoMove(row, col);
		if (value > bestvalue)
		{
			printf("New best move found. player: %d | depth %d | move: %d | value: %d | oldValue: %d\n", playerIndex+1, depth, validMoves[i], value, bestvalue);
			bestvalue = value;
			bestmove = i;
		}
	}
	printf("Loop done\n");
	if (isInitialCase)
	{
		int temp = validMoves[bestmove];
		delete[] validMoves;
		return temp;
	}
	delete[] validMoves;
	return bestvalue;
}