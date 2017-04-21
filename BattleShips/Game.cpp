#include "stdafx.h"
#include "Game.h"
#include "BattleGrid.h"
#include "TextMessage.h"

Game::Game()
{
	BattleGrid gridA(1, 0, &gridSize);
	TextMessage(55, 1, "Place your ships    \nusing arrow keys.   \n\nUse Q and E to\ncycle through ships.\n\nBATTLESHIP\nCRUISER\nSUBMARINE\nDESTROYER", "Instructions", true);

	cursorPos.X = 75;
	cursorPos.Y = 9;

	UpdateShipCount(71, 9, Ships);
	UpdateCursor(cursorPos.X, cursorPos.Y, '<');

	SetConsoleCursorPosition(hStdout, gridA.GetCenter());

	CreateShips();
}

void Game::CreateShips()
{
	int numberOfShips = 0;
	int character;

	for (int i = 0; i < 5; i++)
		numberOfShips += Ships[i];

	while (numberOfShips != 0)
	{
		character = GetCode();

		switch (character)
		{
		case ARROW_UP:
			break;
		case ARROW_DOWN:
			break;
		case ARROW_LEFT:
			break;
		case ARROW_RIGHT:
			break;
		case KEY_Q:
		case KEY_q:
			if (cursorPos.Y != 9)
			{
				SetConsoleCursorPosition(hStdout, cursorPos);
				cout << ' ';
				cursorPos.Y--;
				UpdateCursor(cursorPos.X, cursorPos.Y, '<');
				//SetConsoleCursorPosition(hStdout, gridA.GetCenter());
			}
			break;
		case KEY_E:
		case KEY_e:
			if (cursorPos.Y != 12)
			{
				SetConsoleCursorPosition(hStdout, cursorPos);
				cout << ' ';
				cursorPos.Y++;
				UpdateCursor(cursorPos.X, cursorPos.Y, '<');
				//SetConsoleCursorPosition(hStdout, gridA.GetCenter());
			}
			break;
		default:
			break;
		}
	}
}

int Game::GetCode()
{
	int code = getch();

	if (code == 0 || code == 224) code = 256 + getch();

	return code;
}

void Game::UpdateShipCount(int x, int y, int ships[])
{
	COORD destCoord;
	destCoord.X = x;
	destCoord.Y = y;

	SetConsoleCursorPosition(hStdout, destCoord);

	for (int i = 0; i < sizeof(ships); i++)
	{
		cout << ships[i] << 'x';

		destCoord.Y++;
		SetConsoleCursorPosition(hStdout, destCoord);
	}
}

void Game::UpdateCursor(int x, int y, char cursor)
{
	COORD destCoord;
	destCoord.X = x;
	destCoord.Y = y;
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << cursor;
}

void Game::UpdateScoreboard(int x, int y)
{
}

void Game::Start()
{
	BattleGrid gridA(1, 0, &gridSize);
	//gridA.FillGrid();

	BattleGrid gridB(78 - gridSize * 3, 0, &gridSize);
	//gridB.FillGrid();

	TextMessage scoreTable(33, 8, "You   CPU\n 1  -  0 ", "Score", true);

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD destCoord;

	destCoord.X = 0;
	destCoord.Y = gridSize * 2 + 3;
	SetConsoleCursorPosition(hStdout, destCoord);
}

void Game::End()
{
	string msg = 
		scorePlayer > scoreCpu ? "You won!" :
		scorePlayer < scoreCpu ? "You lost!" : 
		"It's a tie!";

	TextMessage endGameMessage(0, 0, msg, "Game over!");
}