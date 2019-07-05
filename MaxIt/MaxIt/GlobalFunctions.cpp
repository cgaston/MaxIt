#include "GlobalFunctions.h"

int getUserResponse(string question, string accResp) //take input of a question and list of acceptable responses and output question to user and only let them continue with acceptable response
{
	string input;
	int result;
	do
	{
		cout << question;
		getline(cin, input);
		result = accResp.find(toupper(input[0])); //run loop until user enters a response that can be found in accResp and return index where it was found (case insensitive)
	} while (result == string::npos);
	return result;
}