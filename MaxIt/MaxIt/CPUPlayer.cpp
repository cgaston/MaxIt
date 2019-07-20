#include "CPUPlayer.h"
#include "array"


CPUPlayer::CPUPlayer(int p, int depth)
	: Player(p), maxdepth(depth)
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
	string moves;
	printf("Selecting a %s from %s %c\n", rcName[1 - playerIndex], rcName[playerIndex], rcID[playerIndex] + rowOrCol);
	movePick = negamax(b1, score, maxdepth - 1, rowOrCol, playerIndex, true, moves);
//	printf("Moves: %s\n", moves.c_str());
	printf("\nCPU %d chose %s %c\n\n", playerNum+1, rcName[1 - playerIndex], movePick + rcID[1 - playerIndex]);
	return movePick;
}

int CPUPlayer::negamax(MIBoard& b1, int score, int depth, int rowOrCol, char playerIndex, bool isInitialCase, string& moves)
{
	int* validMoves = new int[b1.getRowSize()];
	int row, col, cellVal, numLegalMoves, value, bestmove = 0, bestvalue = -INT_MAX;
	string bestline;

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
		return (score == 0) ? 0 : (score / abs(score)) * depth * 1000;
		/*
		if (score > 0)
		{
			if (playerIndex == playerNum)
			{
//				printf("%*sPlayer %i (wins\n", maxdepth - depth, "-", playerIndex + 1);
				printf("%*sI win on my move\n", maxdepth - depth, "-");
				return (depth) * 1000; //score * 100; // INT_MAX;
			}
			else
			{
//				printf("%*sPlayer %i wins\n", maxdepth - depth, "-", playerIndex + 1);
				printf("%*sOpponent wins on opponent's move\n", maxdepth - depth, "-");
				return (depth) * 1001; //score * 100; // INT_MAX;
			}
		}
		else if (score < 0)
		{
			if (playerIndex == playerNum)
			{
				//				printf("%*sPlayer %i (wins\n", maxdepth - depth, "-", playerIndex + 1);
				printf("%*sI lose on my move\n", maxdepth - depth, "-");
				return (depth) * -1002; // score * 100; // INT_MAX;
			}
			else
			{
				//				printf("%*sPlayer %i wins\n", maxdepth - depth, "-", playerIndex + 1);
				printf("%*sOpponent loses on opponent's move\n", maxdepth - depth, "-");
				return (depth) * -1003; // score * 100; // INT_MAX;
			}
//			printf("%*sPlayer %i loses\n", maxdepth - depth, "-", playerIndex + 1);
		}
		return 0;
		*/
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
		string thismove;
		thismove = "[" + to_string(row) + ", " + to_string(col) + "] ";
		string submoves;
//		printf("%*sExamine move: p%i (%c, %c)\n", maxdepth-depth, "-", playerIndex + 1, '1' + row, 'A' + col);
		value = -negamax(b1, -(score + cellVal), depth - 1, validMoves[i], 1 - playerIndex, false, submoves);
		b1.undoMove(row, col);
		if (isInitialCase)
		{
			string imoves = thismove + submoves;
			printf("Moves: %s, Score: %d\n", imoves.c_str(), value);
		}
		if (value > bestvalue)
		{
//			printf("%*sNew best score: %i. Old = %i\n", maxdepth - depth, "-", value, bestvalue);
			moves = thismove + submoves;
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