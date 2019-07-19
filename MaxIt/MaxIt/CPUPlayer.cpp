#include "CPUPlayer.h"
#include "array"


using namespace std;

CPUPlayer::CPUPlayer()
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
	int* validMoves = new int[b1.getRowSize()];
	int row, col, cellVal, numLegalMoves, value, bestmove = 0, bestvalue = -INT_MAX;

	if (depth == 0)
	{
		delete[] validMoves;
		return score;
	}
	numLegalMoves = b1.makeMoveList(validMoves, rowOrCol, playerIndex);
	if (numLegalMoves == 0) //if number of legal moves is 0, then the game has ended
	{
		delete[] validMoves;
		if (score > 0)
		{
			printf("Player %d has won\n", playerIndex+1);
			return score*100; // (10 - depth) * 1000;  //-INT_MAX;
		}
		else if (score < 0)
		{
			printf("Player %d has lost\n", playerIndex+1);
			return score*100; // (10 - depth) * -1000; //INT_MAX;
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
			printf("New best move found. move: %d | value: %d | oldValue: %d\n", validMoves[i], value, bestvalue);
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