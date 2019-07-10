#include "MIBoard.h"
#include <utility>
#include <iostream>

using namespace std;

MIBoard::MIBoard(int rows, int cols) //set row and col size to given inputs otherwise they are default set to 8x8
	: rowSize(rows) , colSize(cols)
{
	myBoard = new char*[rows]; //allocate array to hold rows
	for (int i = 0; i < rows; i++)
	{
		myBoard[i] = new char[cols]; //allocate each row to the array
	}
	initBoard();
}


MIBoard::~MIBoard()
{
	for (int i = 0; i < rowSize; i++)
	{
		delete[] myBoard[i];
	}
	delete[] myBoard;
}

int MIBoard::getRowSize()
{
	return rowSize;
}

int MIBoard::getColSize()
{
	return colSize;
}

char MIBoard::getAt(int row, int col)
{
	return myBoard[row][col];
}

char MIBoard::doMove(int row, int col) //replaces value in board at given [row][col] and returns value that was in it
{
	char cellVal = myBoard[row][col];
	myBoard[row][col] |= 0x80; //turn topmost bit on to indicate that cell has been deleted
	return cellVal - 9; //return value as an offset by 9 (we will change this value to some variable in the future)
}

char MIBoard::undoMove(int row, int col) //undos most recent move by turnin topmost bit of value in the cell off
{
	myBoard[row][col] &= 0x7f; //turn off topmost bit
	return myBoard[row][col] - 9;
}

void MIBoard::displayBoard()
{
	printf("   ");
	for (int c = 0; c < colSize; c++)
	{
		printf("   %c ", 'A'+c);
	}
	cout << endl;
	for (int r = 0; r < rowSize; r++)
	{
		printf("   ");
		for (int c = 0; c < colSize; c++)
		{
			printf("+----");
		}
		printf("+\n");
		printf("%2d ", (r + 1));
		for (int c = 0; c < colSize; c++)
		{
			if (myBoard[r][c] < 0)
				printf("|    ");
			else
				printf("| %2d ", (myBoard[r][c] - 9) );
		}
		printf("|\n");
	}
	printf("   ");
	for (int c = 0; c < colSize; c++)
	{
		printf("+----");
	}
	printf("+\n");
	cout << endl;
}

void MIBoard::initBoard() //this function initializes the game board to random numbers 0-15
{
	for (int r = 0; r < rowSize; r++)
	{
		for (int c = 0; c < colSize; c++)
		{
			myBoard[r][c] = (char)(rand() % 31);
		}
	}
}

bool MIBoard::noMoves(char rowOrCol, char playerIndex)
{
	for (int i = 0; i < rowSize; i++) //run loop to see if a space is possible for current row and column and indicate if there was or not
	{
		if (playerIndex == 0) // do code if player 1's turn else do code for player 2's turn
		{
			if (myBoard[rowOrCol][i] >= 0)
				return false;
		}
		else
		{
			if (myBoard[i][rowOrCol] >= 0)
				return false;
		}
	}
	return true; //return true indicating no moves left in current row or column
}

bool MIBoard::isValidMove(int row, int col)
{
	return getAt(row, col) >= 0; //break out of loop if selection is valid
}

int MIBoard::makeMoveList(char* moveList, int rowOrCol, char playerIndex)
{
	int numMoves;
	for (int i = 0; i < rowSize; i++)
	{
		if (playerIndex == 0) // do code if player 1's turn else do code for player 2's turn
		{
			if (myBoard[rowOrCol][i] >= 0)
			{
				moveList[numMoves++] = i;
			}
		}
		else
		{
			if (myBoard[i][rowOrCol] >= 0)
				moveList[numMoves++] = i;
		}
	}
	return numMoves;
}