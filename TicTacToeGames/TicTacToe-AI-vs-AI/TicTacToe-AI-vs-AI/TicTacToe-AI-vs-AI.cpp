// TicTacToe-vs-AI.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

void printRow(int row)
{
	for (int i = row; i < row + 1; i++)
	{
		cout << "      |     |      \n";
		cout << " ";
		for (int j = 0; j < 3; j++)
		{
			if (BOARD[i][j] == AI1)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			else if (BOARD[i][j] == AI2)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cout << "  " << BOARD[i][j];

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

			if (j < 2)
				cout << "  |";
		}
		if (i < 2)
			cout << "\n _____|_____|_____ \n";
	}
}

void printBOARD()
{
	cout << "\n";

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

	return counter == 3 ? (true && cout << "\n\nAI " << letter << " wins\n") : false;
}

bool checkCol(int col, char letter)
{
	int counter = 0;
	for (int i = 0; i < 3; i++)
		if (BOARD[i][col] != '*' && BOARD[i][col] == letter)
			counter++;

	return counter == 3 ? (true && cout << "\n\nAI " << letter << " wins\n") : false;
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

	return counter == 3 ? (true && cout << "\n\nAI " << letter << " wins\n") : false;
}

bool checkTie()
{
	int counter = 0;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (BOARD[i][j] != '*')
				counter++;
	return counter == 9 ? (true && cout << "\n\nTie Game\n") : false;
}

bool checkBOARD()
{
	for (int i = 0; i < 3; i++)
		if (checkRow(i, AI1) || checkRow(i, AI2))
			return false;

	for (int i = 0; i < 3; i++)
		if (checkCol(i, AI1) || checkCol(i, AI2))
			return false;

	if ((checkDiag(0, AI1) || checkDiag(2, AI1))
		|| (checkDiag(0, AI2) || checkDiag(2, AI2)))
		return false;

	if (checkTie())
		return false;

	return true;
}

bool pickRow(int * arr, int row, char ai)
{
	if (BOARD[row][0] == BOARD[row][1] && BOARD[row][0] == ai)
	{
		if (checkPos(row, 2))
		{
			arr[0] = row;
			arr[1] = 2;
			return true;
		}
	}
	else if (BOARD[row][1] == BOARD[row][2] && BOARD[row][1] == ai)
	{
		if (checkPos(row, 0))
		{
			arr[0] = row;
			arr[1] = 0;
			return true;
		}
	}
	else if (BOARD[row][0] == BOARD[row][2] && BOARD[row][0] == ai)
	{
		if (checkPos(row, 1))
		{
			arr[0] = row;
			arr[1] = 1;
			return true;
		}
	}
	return false;
}

bool pickCol(int * arr, int col, char ai)
{
	if (BOARD[0][col] == BOARD[1][col] && BOARD[0][col] == ai)
	{
		if (checkPos(2, col))
		{
			arr[0] = 2;
			arr[1] = col;
			return true;
		}
	}
	else if (BOARD[2][col] == BOARD[1][col] && BOARD[2][col] == ai)
	{
		if (checkPos(0, col))
		{
			arr[0] = 0;
			arr[1] = col;
			return true;
		}
	}
	else if (BOARD[0][col] == BOARD[2][col] && BOARD[0][col] == ai)
	{
		if (checkPos(1, col))
		{
			arr[0] = 1;
			arr[1] = col;
			return true;
		}
	}
	return false;
}

void pickDiag(int * arr, char ai)
{
	if (BOARD[0][0] == BOARD[1][1] && BOARD[0][0] == ai)
	{
		if (checkPos(2, 2))
		{
			arr[0] = 2;
			arr[1] = 2;
			return;
		}
	}
	else if (BOARD[2][0] == BOARD[1][1] && BOARD[2][0] == ai)
	{
		if (checkPos(0, 2))
		{
			arr[0] = 0;
			arr[1] = 2;
			return;
		}
	}
	else if (BOARD[2][2] == BOARD[1][1] && BOARD[2][2] == ai)
	{
		if (checkPos(0, 0))
		{
			arr[0] = 0;
			arr[1] = 0;
			return;
		}
	}
	else if (BOARD[0][2] == BOARD[1][1] && BOARD[0][2] == ai)
	{
		if (checkPos(2, 2))
		{
			arr[0] = 2;
			arr[1] = 2;
			return;
		}
	}
	else if ((BOARD[2][0] == BOARD[0][2] && BOARD[2][0] == ai)
		|| (BOARD[0][0] == BOARD[2][2] && BOARD[0][0] == ai))
	{
		if (checkPos(1, 1))
		{
			arr[0] = 1;
			arr[1] = 1;
			return;
		}
	}
}

void pickPositions(int * arr, char ai)
{
	for (int i = 0; i < 3; i++)
		if (pickRow(arr, i, ai))
			return;

	for (int i = 0; i < 3; i++)
		if (pickCol(arr, i, ai))
			return;
	
	pickDiag(arr, ai);
}

void computerTurnAI1()
{
	int arr[2] = { -1, -1 }, row, col;

	pickPositions(arr, AI1);

	if (arr[0] != -1)
	{
		changeBOARD(arr[0], arr[1], AI1);
		return;
	}

	srand(time(0));

	row = rand() % 3;
	col = rand() % 3;

	while (!checkPos(row, col))
	{
		row = rand() % 3;
		col = rand() % 3;
	}

	changeBOARD(row, col, AI1);
}

void computerTurnAI2()
{
	int arr[2] = { -1, -1 }, row, col;

	pickPositions(arr, AI2);

	if (arr[0] != -1)
	{
		changeBOARD(arr[0], arr[1], AI2);
		return;
	}

	srand(time(0));

	row = rand() % 3;
	col = rand() % 3;

	while (!checkPos(row, col))
	{
		row = rand() % 3;
		col = rand() % 3;
	}

	changeBOARD(row, col, AI2);
}

int main()
{
	cout << "Tic-Tac-Toe Game AI vs AI Made with C++\n"
		<< "\nTo end game press -1 and enter.\n";

	int num = 1, row = -1, col = -1;

	BOARD = new char*[3];

	while (1)
	{
		cout << "\nPress anything to start/continue game or -1 to end and enter.\n";
		cin >> num;

		if (num != -1)
		{
			makeBOARD();

			while (checkBOARD())
			{
				cout << "\n\nAI1's turn to pick ";

				for (int i = 0; i < 3; i++)
				{
					cout << ".";
					std::this_thread::sleep_for(std::chrono::seconds(1));
				}

				cout << "\n";

				computerTurnAI1();

				if (!checkBOARD())
					break;

				cout << "\n\nAI2's turn to pick ";

				for (int i = 0; i < 3; i++)
				{
					cout << ".";
					std::this_thread::sleep_for(std::chrono::seconds(1));
				}

				cout << "\n";

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
