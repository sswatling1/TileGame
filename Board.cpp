#include"Board.h"
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>

using namespace std;

GameBoard::GameBoard()
{
	int count = 0;

	
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			board[row][col] = boardValues[row][col];
		}
	}

}

void GameBoard::DisplayBoard()
{
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << "+---+---+---+" << endl;
	for (int row = 0; row < 3; row++)
	{

		for (int col = 0; col < 3; col++)
		{
			cout << "|";
			if (board[row][col] != boardValues[row][col])
			{
				SetConsoleTextAttribute(hConsole, 4);
			}
			else
			{
				SetConsoleTextAttribute(hConsole, 2);
			}
			cout <<" "<<board[row][col]<<" ";
			SetConsoleTextAttribute(hConsole, 15);
		}
		cout << "|" << endl;
		cout << "+---+---+---+" << endl;
	}
	
	cout << endl;

}

void GameBoard::MoveTile(char move)
{
	int movecol;
	int moverow;

	FindEmpty();

	movecol = blankCoord.ecol;
	moverow = blankCoord.erow;


	//Switches the tile according to the users input
	switch (move)
	{
	case 'w':
	case 'W':
		moverow += 1;
		break;
	case 's':
	case 'S':
		moverow -= 1;
		break;
	case 'a':
	case 'A':
		movecol += 1;
		break;
	case 'd':
	case 'D':
		movecol -= 1;
		break;
	}

	if (moverow >= 0 && moverow <= 2 && movecol >= 0 && movecol <= 2)
	{
		board[blankCoord.erow][blankCoord.ecol] = board[moverow][movecol];
		board[moverow][movecol] = ' ';
	}
}

void GameBoard::ScrambleBoard()
{
	int direction;
	srand(time(NULL));

	for (int moves = 0; moves < 1000; moves++)
	{
		direction = rand() % 4;

		switch (direction)
		{
		case 0:
			MoveTile('s');
			break;
		case 1:
			MoveTile('w');
			break;
		case 2:
			MoveTile('a');
			break;
		case 3:
			MoveTile('d');
			break;
		}
	}
}

void GameBoard::FindEmpty()
{
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			if (board[row][col] == ' ')
			{
				blankCoord.erow = row;
				blankCoord.ecol = col;
			}
		}
	}
}

bool GameBoard::isBoardSolved()
{
	bool isSolved = true;

	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			if (board[row][col] != boardValues[row][col])
			{
				isSolved = false;
			}
		}
	}
	
	return isSolved;
}

bool GameBoard::PlayAgain()
{
	char playAgain;
	bool play = false;

	cout << "Would you like to play again (Y = yes, N = no)?" << endl;
	cout << "Play Again: ";
	playAgain = _getch();

	if (playAgain == 'y' || playAgain == 'Y')
	{
		play = true;
	}
	else if (playAgain == 'n' || playAgain == 'N')
	{
		play = false;
	}
	else
	{
		cout << "Invalid Response." << endl;
		play = PlayAgain();
	}

	return play;
}

void GameBoard::Play()
{
	GameBoard board;
	char move;
	bool playAgain = true;

	while (playAgain)
	{
		while (board.isBoardSolved())
		{
			board.ScrambleBoard();
		}

		while (!board.isBoardSolved())
		{
			system("CLS");
			board.DisplayBoard();

			cout << "(W = up, S = down, A = left, D = right)" << endl;
			cout << "Enter your move: ";
			move = _getch();
			cout << endl;

			board.MoveTile(move);

		}

		system("CLS");
		cout << "CONGRATULATIONS!!" << endl;
		cout << endl;
		board.DisplayBoard();
		cout << endl;

		playAgain = board.PlayAgain();
		system("CLS");
	}
}