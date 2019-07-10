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

}

int CPUPlayer::move(MIBoard& b1, int rowOrCol, char playerIndex)
{
	return 0;
}

int CPUPlayer::negamax(MIBoard& b1, int score, int depth, int rowOrCol, char playerIndex, bool isInitialCase)
{
	char* validMoves = new char[b1.getRowSize()];
	int numLegalMoves, value, bestvalue = -INFINITY;

	if (depth == 0)
		return score;
	numLegalMoves = 0;
	delete(validMoves);
}