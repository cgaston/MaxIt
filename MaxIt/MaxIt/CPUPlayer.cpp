#include "CPUPlayer.h"
#include "array"

using namespace std;

CPUPlayer::CPUPlayer(int depth)
	: maxdepth(depth)
{
}


CPUPlayer::~CPUPlayer()
{
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
	movePick = negamax(b1, score, maxdepth - 1, rowOrCol, playerIndex, true);
	printf("\nCPU chose %s %c\n\n", s1.c_str(), movePick + c1);
	return movePick;
}

int CPUPlayer::negamax(MIBoard& b1, int score, int depth, int rowOrCol, char playerIndex, bool isInitialCase)
{
	int* validMoves = new int[b1.getRowSize()];
	int row, col, cellVal, numLegalMoves, value, bestmove = 0, bestvalue = -INT_MAX;

//	printf("%*sNegamax: p%i Score: %i\n", maxdepth - depth, " ", playerIndex + 1, score);
	if (depth == 0)
	{
//		printf("%*sScore = %i\n", maxdepth - depth, "-", -score);
		delete[] validMoves;
		return score;
	}
	numLegalMoves = b1.makeMoveList(validMoves, rowOrCol, playerIndex);
	if (numLegalMoves == 0)
	{
		delete[] validMoves;
		if (score > 0)
		{
//			printf("%*sPlayer %i wins\n", maxdepth - depth, "-", playerIndex + 1);
			return (maxdepth - depth) * 1000; //score * 100; // INT_MAX;
		}
		else if (score < 0)
		{
//			printf("%*sPlayer %i loses\n", maxdepth - depth, "-", playerIndex + 1);
			return (maxdepth - depth) * -1000; // score * 100; // INT_MAX;
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
//		printf("%*sExamine move: p%i (%c, %c)\n", maxdepth-depth, "-", playerIndex + 1, '1' + row, 'A' + col);
		value = -negamax(b1, -(score + cellVal), depth - 1, validMoves[i], 1 - playerIndex, false);
		b1.undoMove(row, col);
		if (value > bestvalue)
		{
//			printf("%*sNew best score: %i. Old = %i\n", maxdepth - depth, "-", value, bestvalue);
			bestvalue = value;
			bestmove = i;
		}
	}
	if (isInitialCase)
	{
		int temp = validMoves[bestmove];
//		printf("%*sBest overall score for p%i: %i\n", maxdepth - depth, "-", playerIndex + 1, bestvalue);
		delete[] validMoves;
		return temp;
	}
	delete[] validMoves;
//	printf("%*sBest score for p%i at this depth: %i\n", maxdepth - depth, "-", playerIndex + 1, bestvalue);
	return bestvalue;
}