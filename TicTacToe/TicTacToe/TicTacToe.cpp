// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
// Made by Carl Antoine

#include <iostream>
using namespace std;

void printRow(char **board, int row)
{
	for (int i = row; i < row + 1; i++)
	{
		cout << "|     |     |     |" << endl;
		cout << "|";
		for (int j = 0; j < 3; j++)
			cout << "  " << board[i][j] << "  |";
		cout << "\n|_____|_____|_____|" << endl;
	}
}

void printBoard(char **board)
{
	cout << " _________________" << endl;

	printRow(board, 0);
	printRow(board, 1);
	printRow(board, 2);
}

void makeBoard(char **board)
{
	for (int i = 0; i < 3; i++)
		board[i] = new char[3];

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			board[i][j] = '*';

	printBoard(board);
}

void changeBoard(char **board, int row, int col, char player)
{
	board[row][col] = player;
	printBoard(board);
}

bool checkPos(char **board, int row, int col)
{
	return (board[row][col] == '*') ? true : false;
}

bool checkRow(char **board, int row, char player)
{
	int counter = 0;
	for (int i = 0; i < 3; i++)
		if (board[row][i] != '*' && board[row][i] == player)
			counter++;

	return counter == 3 ? (true && cout << "\nPlayer " << player << " wins\n") : false;
}

bool checkCol(char **board, int col, char player)
{
	int counter = 0;
	for (int i = 0; i < 3; i++)
		if (board[i][col] != '*' && board[i][col] == player)
			counter++;

	return counter == 3 ? (true && cout << "\nPlayer " << player << " wins\n") : false;
}

bool checkDiag(char **board, int row, char player)
{
	int counter = 0;
	if (row == 0)
	{
		for (int i = 0; i < 3; i++)
			if (board[row + i][i] != '*' && board[row + i][i] == player)
				counter++;
	}
	else
	{
		for (int i = 0; i < 3; i++)
			if ((board[row - i][i] != '*') && (board[row - i][i] == player))
				counter++;
	}

	return counter == 3 ? (true && cout << "\nPlayer " << player << " wins\n") : false;
}

bool checkTie(char **board)
{
	int counter = 0;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (board[i][j] != '*')
				counter++;
	return counter == 9 ? (true && cout << "\nTie Game\n") : false;
}

bool checkBoard(char **board)
{
	for (int i = 0; i < 3; i++)
		if (checkRow(board, i, 'x') || checkRow(board, i, 'o'))
			return false;

	for (int i = 0; i < 3; i++)
		if (checkCol(board, i, 'x') || checkCol(board, i, 'o'))
			return false;

	if ((checkDiag(board, 0, 'x') || checkDiag(board, 2, 'x'))
		|| (checkDiag(board, 0, 'o') || checkDiag(board, 2, 'o')))
		return false;

	if (checkTie(board))
		return false;

	return true;
}

int main()
{
	cout << "Tic Tac Toe Game Made with C++\n" << endl;
	cout << "Choose a number between 0 - 2 for row and column"
		<< " and either x or o then press enter.\n" << endl;
	cout << "To end game press -1 and enter.\n" << endl;

	char **board = new char*[3], player;

	makeBoard(board);

	int num = 1, row, col;

	while (1)
	{
		cout << "\nPress anything to start/continue game or -1 to end and enter.\n" << endl;
		cin >> num;

		if (num != -1)
		{
			while (checkBoard(board))
			{
				cout << "\nChoose a row, column, and x or o.\n" << endl;

				cin >> row >> col >> player;

				if (checkPos(board, row, col))
					changeBoard(board, row, col, player);
				else
					cout << "\nPick a different position.\n" << endl;
			}
		}

		cout << "\nGame Ended!" << endl;
		break;
	}

	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
