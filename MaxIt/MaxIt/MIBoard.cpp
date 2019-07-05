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

char MIBoard::deleteCell(int row, int col) //replaces value in board at given [row][col] with max char and returns value that was in it
{
	char cellVal = myBoard[row][col];
	myBoard[row][col] = CHAR_MAX;
	return cellVal;
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
			if (myBoard[r][c] == CHAR_MAX)
				printf("|    ");
			else
				printf("| %2d ", myBoard[r][c]);
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
			myBoard[r][c] = (char)(rand() % 16);
		}
	}
}

bool MIBoard::noMoves(char rowOrCol, bool isRow)
{
	for (int i = 0; i < rowSize; i++) //run loop to see if a space is possible for current row and column and indicate if there was or not
	{
		if (isRow)
		{
			if (myBoard[rowOrCol][i] != CHAR_MAX)
				return false;
		}
		else
		{
			if (myBoard[i][rowOrCol] != CHAR_MAX)
				return false;
		}
	}
	return true; //return true indicating no moves left in current row or column
}
