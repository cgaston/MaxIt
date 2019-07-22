#include "HumanPlayer.h"
#include "GlobalFunctions.h"
#include <stdio.h>

using namespace std;

HumanPlayer::HumanPlayer()
	: Player()
{
}


HumanPlayer::~HumanPlayer()
{
}

int HumanPlayer::move(MIBoard& b1, int rowOrCol, char playerIndex, int /*score*/)
{
	const char *s1, *s2; //two strings formatted for user messages
	char c1; // holds row or column index they must pick from
	string accResp; // will hold list of acceptable user responses
	int rowInd, colInd;
	if (playerIndex == 0) //set variables used to format user messages (0 indicates player 1)
	{
		s1 = "column";
		s2 = "row";
		c1 = rowOrCol + '1';
		accResp = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		rowInd = rowOrCol;
	}
	else
	{
		s1 = "row";
		s2 = "column";
		c1 = rowOrCol + 'A';
		accResp = "123456789";
		colInd = rowOrCol;
	}
	char str[200]; //holds question for user response
	sprintf_s(str, "Choose a %s from %s %c: ", s1, s2, c1); //format question based on who's turn it is
	int selection;
	do
	{
		selection = getUserResponse(str, accResp.substr(0, b1.getRowSize())); //get user selection
		if (playerIndex == 0) // set variable not initialized already to user pick
			colInd = selection;
		else
			rowInd = selection;
		if (b1.isValidMove(rowInd, colInd) ) //break out of loop if selection is valid
			break;
		cout << "Cell has already been taken\n";
	} while(true);
	return selection; //return row number or column letter chosen by user
}