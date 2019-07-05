#pragma once

class MIBoard
{
public:
	MIBoard(int rows = 8, int cols = 8);
	~MIBoard();
	char deleteCell(int row, int col);
	void displayBoard();
	void initBoard();
	char getAt(int row, int col);
	int getRowSize();
	int getColSize();
	bool noMoves(char rowOrCol, bool isRow);
private:
	char** myBoard;
	int rowSize; //1 greater than the last index number of rows of board
	int colSize; //1 greater than the last index number of cols of board
};

