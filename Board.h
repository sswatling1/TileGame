#pragma once

struct coord
{
	int erow;
	int ecol;
};

class GameBoard
{
private:
	char board[3][3];
	coord blankCoord;
	char boardValues[3][3] = {
		{ '1','2','3' },
		{ '4','5','6' },
		{ '7','8',' ' } };

	void DisplayBoard();

	void FindEmpty();

	void MoveTile(char move);

	bool isBoardSolved();

	void ScrambleBoard();

	bool PlayAgain();

public:

	GameBoard();

	void Play();
};