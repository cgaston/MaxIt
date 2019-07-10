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
	return ;
}

int CPUPlayer::negamax(MIBoard& b1, int score, int depth, char playerIndex, bool isInitialCase)
{
	char* validMoves = new char[b1.getRowSize()];
	delete(validMoves);
}