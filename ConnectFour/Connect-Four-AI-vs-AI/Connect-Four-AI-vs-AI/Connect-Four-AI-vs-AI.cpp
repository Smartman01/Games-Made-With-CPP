// Connect-Four-AI-vs-AI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <Windows.h>

using namespace std;

char **BOARD, AI1 = 'x', AI2 = 'o';
static int numRow = 6, numCol = 7;

// 9 12 15

void printRow(int row)
{
	for (int i = row; i < row + 1; i++)
	{
		cout << "|     |     |     |     |     |     |     |\n";
		cout << "|";
		for (int j = 0; j < numCol; j++)
		{
			if (BOARD[i][j] == AI1)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			else if (BOARD[i][j] == AI2)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cout << "  " << BOARD[i][j];

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

			cout << "  |";
		}
		cout << "\n|_____|_____|_____|_____|_____|_____|_____|\n";
	}
}

void printBOARD()
{
	for (int i = 0; i < numRow; i++)
		printRow(i);

	cout << "   ";
	for (int i = 0; i < numCol; i++)
		cout << i << "     ";
	cout << "\n";
}

void makeBOARD()
{
	for (int i = 0; i < numRow; i++)
		BOARD[i] = new char[numCol];

	for (int i = 0; i < numRow; i++)
		for (int j = 0; j < numCol; j++)
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

bool checkRow(int row, int col, char letter)
{
	int counter = 0;
	for (int i = 0; i < 4; i++)
		if (BOARD[row][col + i] == letter)
			counter++;

	return counter == 4 ? (true && cout << "\n\nAI " << letter << " wins\n") : false;
}

bool checkCol(int row, int col, char letter)
{
	int counter = 0;
	for (int i = 0; i < 4; i++)
		if (BOARD[row - i][col] == letter)
			counter++;

	return counter == 4 ? (true && cout << "\n\nAI " << letter << " wins\n") : false;
}

bool checkDiag(int row, int col, char letter)
{
	int counter = 0;

	if (col < 3)
	{
		for (int i = 0; i < 4; i++)
		{
			if (BOARD[row - i][col + i] == letter)
				counter++;
		}
	}
	else if (col == 3)
	{
		for (int i = 0; i < 4; i++)
		{
			if (BOARD[row - i][col + i] == letter)
				counter++;
		}

		if (counter == 4)
			return counter == 4 ? (true && cout << "\n\nAI " 
				<< letter << " wins\n") : false;
		counter = 0;

		for (int i = 0; i < 4; i++)
		{
			if (BOARD[row - i][col - i] == letter)
				counter++;
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			if (BOARD[row - i][col - i] == letter)
				counter++;
		}
	}

	return counter == 4 ? (true && cout << "\n\nAI " << letter << " wins\n") : false;
}

bool checkTie()
{
	int counter = 0;

	for (int i = 0; i < numRow; i++)
		for (int j = 0; j < numCol; j++)
			if (BOARD[i][j] != '*')
				counter++;
	return counter == 42 ? (true && cout << "\n\nTie Game\n") : false;
}

bool checkBOARD()
{
	for (int i = numRow - 1; i >= 0; i--)
		for (int j = 0; j < numCol - 3; j++)
			if (checkRow(i, j, AI1) || checkRow(i, j, AI2))
				return false;

	for (int i = numRow - 1; i >= 3; i--)
		for (int j = 0; j < numCol; j++)
			if (checkCol(i, j, AI1) || checkCol(i, j, AI2))
				return false;

	for (int i = numRow - 1; i >= 3; i--)
		for (int j = 0; j < numCol; j++)
			if (checkDiag(i, j, AI1) || checkDiag(i, j, AI2))
				return false;

	if (checkTie())
		return false;

	return true;
}

bool rowFull(int row)
{
	for (int i = 0; i < numCol; i++)
		if (BOARD[row][i] == '*')
			return false;
	return true;
}

void computerTurnAI1()
{
	int row = numRow - 1, col = -1;

	/*pickPositions(col, AI1);

	if (col != -1)
	{
		changeBOARD(col, AI1);
		return;
	}*/

	srand(time(0));

	col = rand() % numCol;

	while (!checkPos(row, col))
	{
		if (rowFull(row))
			row--;

		col = rand() % numCol;
	}

	changeBOARD(row, col, AI1);
}

void computerTurnAI2()
{
	int row = numRow - 1, col = -1;

	/*pickPositions(col, AI2);

	if (col != -1)
	{
		changeBOARD(col, AI2);
		return;
	}*/

	srand(time(0));

	col = rand() % numCol;

	while (!checkPos(row, col))
	{
		if (rowFull(row))
			row--;

		col = rand() % numCol;
	}

	changeBOARD(row, col, AI2);
}

int main()
{
	cout << "Connect Four Game AI vs AI Made with C++\n"
		<< "\nTo end game press -1 and enter.\n";

	int num = 1, row = -1, col = -1;
	BOARD = new char*[numRow];

	while (1)
	{
		cout << "\nPress anything to start/continue game or -1 to end and enter.\n";
		cin >> num;

		if (num != -1)
		{
			makeBOARD();

			while (checkBOARD())
			{
				cout << "\nAI1's turn to pick ";

				for (int i = 0; i < 3; i++)
				{
					cout << ".";
					std::this_thread::sleep_for(std::chrono::seconds(1));
				}

				cout << "\n\n";

				computerTurnAI1();

				if (!checkBOARD())
					break;

				cout << "\nAI2's turn to pick ";

				for (int i = 0; i < 3; i++)
				{
					cout << ".";
					std::this_thread::sleep_for(std::chrono::seconds(1));
				}

				cout << "\n\n";

				computerTurnAI2();
			}
		}

		cout << "\nGame Ended!" << endl;

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
