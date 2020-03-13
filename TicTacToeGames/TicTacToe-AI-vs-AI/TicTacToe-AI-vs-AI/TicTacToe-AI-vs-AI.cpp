// TicTacToe-vs-AI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

char **BOARD, PLAYER = 'x', AI = 'o';

void printRow(int row)
{
	for (int i = row; i < row + 1; i++)
	{
		cout << "|     |     |     |\n";
		cout << "|";
		for (int j = 0; j < 3; j++)
			cout << "  " << BOARD[i][j] << "  |";
		cout << "\n|_____|_____|_____|\n";
	}
}

void printBOARD()
{
	cout << " _________________\n";

	printRow(0);
	printRow(1);
	printRow(2);
}

void makeBOARD()
{
	for (int i = 0; i < 3; i++)
		BOARD[i] = new char[3];

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			BOARD[i][j] = '*';

	printBOARD();
}

void changeBOARD(int row, int col, char letter)
{
	BOARD[row][col] = letter;
	printBOARD();
}

bool checkPos(int row, int col)
{
	return (BOARD[row][col] == '*') ? true : false;
}

bool checkRow(int row, char letter)
{
	int counter = 0;
	for (int i = 0; i < 3; i++)
		if (BOARD[row][i] != '*' && BOARD[row][i] == letter)
			counter++;

	return counter == 3 ? (true && cout << "\nPlayer " << letter << " wins\n") : false;
}

bool checkCol(int col, char letter)
{
	int counter = 0;
	for (int i = 0; i < 3; i++)
		if (BOARD[i][col] != '*' && BOARD[i][col] == letter)
			counter++;

	return counter == 3 ? (true && cout << "\nPlayer " << letter << " wins\n") : false;
}

bool checkDiag(int row, char letter)
{
	int counter = 0;
	if (row == 0)
	{
		for (int i = 0; i < 3; i++)
			if (BOARD[row + i][i] != '*' && BOARD[row + i][i] == letter)
				counter++;
	}
	else
	{
		for (int i = 0; i < 3; i++)
			if ((BOARD[row - i][i] != '*') && (BOARD[row - i][i] == letter))
				counter++;
	}

	return counter == 3 ? (true && cout << "\nPlayer " << letter << " wins\n") : false;
}

bool checkTie()
{
	int counter = 0;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (BOARD[i][j] != '*')
				counter++;
	return counter == 9 ? (true && cout << "\nTie Game\n") : false;
}

bool checkBOARD()
{
	for (int i = 0; i < 3; i++)
		if (checkRow(i, PLAYER) || checkRow(i, AI))
			return false;

	for (int i = 0; i < 3; i++)
		if (checkCol(i, PLAYER) || checkCol(i, AI))
			return false;

	if ((checkDiag(0, PLAYER) || checkDiag(2, PLAYER))
		|| (checkDiag(0, AI) || checkDiag(2, AI)))
		return false;

	if (checkTie())
		return false;

	return true;
}

void computerTurn()
{
	int row, col;

	srand(time(0));

	row = rand() % 3;
	col = rand() % 3;

	while (!checkPos(row, col))
	{
		row = rand() % 3;
		col = rand() % 3;
	}

	changeBOARD(row, col, AI);
}


int main()
{
	cout << "Tic Tac Toe Game vs AI Made with C++\n"
		<< "\nIntstructions: Choose a number between 0 - 2"
		<< "\nfor the row and column then press enter.\n"
		<< "To end game press -1 and enter.\n";

	int num = 1, row, col;

	BOARD = new char*[3];

	makeBOARD();

	while (1)
	{
		cout << "\nPress anything to start/continue game or -1 to end and enter.\n";
		cin >> num;

		if (num != -1)
		{
			while (checkBOARD())
			{
				cout << "\nChoose a row, column.\n";

				cin >> row >> col;

				if (checkPos(row, col))
				{
					changeBOARD(row, col, PLAYER);
				}
				else
				{
					cout << "\nPick a different position.\n";
					continue;
				}

				if (!checkBOARD())
					break;

				cout << "\n AI's turn to pick ";

				for (int i = 0; i < 3; i++)
				{
					cout << ".";
					std::this_thread::sleep_for(std::chrono::seconds(1));
				}

				cout << "\n";

				computerTurn();
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
