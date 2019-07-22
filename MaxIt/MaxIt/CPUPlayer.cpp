#include "CPUPlayer.h"
#include "array"


CPUPlayer::CPUPlayer(int depth)
	: Player(), maxdepth(depth)
{
}


CPUPlayer::~CPUPlayer()
{
}

int CPUPlayer::move(MIBoard& b1, int rowOrCol, char playerIndex, int score)
{
	const char* rcName[2] = { "row", "column" };
	const char rcID[2] = { '1', 'A' };
	int movePick;
	movePick = negamax(b1, score, maxdepth, rowOrCol, playerIndex, true);
	printf("\nCPU chose %s %c\n\n", rcName[1 - playerIndex], movePick + rcID[1 - playerIndex]);
	return movePick;
}

int CPUPlayer::negamax(MIBoard& b1, int score, int depth, int rowOrCol, char playerIndex, bool isInitialCase)
{
	int* validMoves = new int[b1.getRowSize()];
	int row, col, cellVal, numLegalMoves, value, bestmove = 0, bestvalue = -INT_MAX;

	if (depth == 0)
	{
		delete[] validMoves;
		return score;
	}
	numLegalMoves = b1.makeMoveList(validMoves, rowOrCol, playerIndex);
	if (numLegalMoves == 0)
	{
		delete[] validMoves;
		return (score == 0) ? 0 : (score / abs(score)) * depth * 1000;
	}

	for (int i = 0; i < numLegalMoves; i++)
	{
		if (isInitialCase)
		{
			int x = 0;
		}
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
		value = -negamax(b1, -(score + cellVal), depth - 1, validMoves[i], 1 - playerIndex, false);
		b1.undoMove(row, col);
		if (value > bestvalue)
		{
			bestvalue = value;
			bestmove = i;
		}
	}
	if (isInitialCase)
	{
		int temp = validMoves[bestmove];
		delete[] validMoves;
		return temp;
	}
	delete[] validMoves;
	return bestvalue;
}