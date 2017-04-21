#include "stdafx.h"
#include "Game.h"
#include "BattleGrid.h"
#include "TextMessage.h"

Game::Game()
{
	BattleGrid gridA(1, 0, &gridSize);
	TextMessage(53, 1, "Place your ships    \nusing arrow keys.   \n\nUse Q and E to\ncycle through ships.\n\nBATTLESHIP\nCRUISER\nSUBMARINE\nDESTROYER", "Instructions", true);

	cursorPos.X = 73;
	cursorPos.Y = 9;

	UpdateShipCount(68, 9, Ships);
	UpdateCursor(cursorPos.X, cursorPos.Y, '<');

	centerPos = gridA.GetCenter();
	lastPos = centerPos;
	SetConsoleCursorPosition(hStdout, centerPos);

	CreateShips(&gridA);
}

int Game::GetCode()
{
	int code = getch();

	if (code == 0 || code == 224) code = 256 + getch();

	return code;
}

bool operator ==(COORD const& lhs, COORD const& rhs)
{
	return lhs.X == rhs.X && lhs.Y == rhs.Y;
}

bool Game::CheckContains(vector<COORD>* grid, COORD * pos)
{
	if (count(grid->begin(), grid->end(), *pos) != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Game::CreateShips(BattleGrid* grid)
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
		case KEY_ENTER:
			if (!CheckContains(&ShipCoordinates, &lastPos))
			{
				ShipCoordinates.push_back(lastPos);
				lastPos = centerPos;
				SetConsoleCursorPosition(hStdout, centerPos);
			}
			break;

		case ARROW_UP:
			// Move ship up
			if (lastPos.Y != grid->Y + 2)
			{
				grid->ClearGrid();
				grid->FillGrid(&ShipCoordinates);
				lastPos.Y -= 2;
				DrawShip(&lastPos, &ShipCoordinates);
			}
			break;

		case ARROW_DOWN:
			// Move ship down
			if (lastPos.Y != grid->Y + grid->Grid.size() * 2)
			{
				grid->ClearGrid();
				grid->FillGrid(&ShipCoordinates);
				lastPos.Y += 2;
				DrawShip(&lastPos, &ShipCoordinates);
			}
			break;

		case ARROW_LEFT:
			// Move ship left
			if (lastPos.X != grid->X + 3)
			{
				grid->ClearGrid();
				grid->FillGrid(&ShipCoordinates);
				lastPos.X -= 3;
				DrawShip(&lastPos, &ShipCoordinates);
			}
			break;

		case ARROW_RIGHT:
			// Move ship right
			if (lastPos.X != grid->X + grid->Grid.size() * 3)
			{
				grid->ClearGrid();
				grid->FillGrid(&ShipCoordinates);
				lastPos.X += 3;
				DrawShip(&lastPos, &ShipCoordinates);
			}
			break;

		case KEY_Q:
		case KEY_q:
			if (cursorPos.Y != 9)
			{
				SetConsoleCursorPosition(hStdout, cursorPos);
				cout << ' ';
				cursorPos.Y--;
				UpdateCursor(cursorPos.X, cursorPos.Y, '<');
				SetConsoleCursorPosition(hStdout, lastPos);
				Beep(523, 120);
			}
			else
			{
				Beep(440, 100);
				Beep(395, 125);
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
				SetConsoleCursorPosition(hStdout, lastPos);
				Beep(523, 120);
			}
			else
			{
				Beep(440, 100);
				Beep(395, 125);
			}
			break;

		case KEY_R:
		case KEY_r:
			// Rotate ship
			lastPos = centerPos;
			break;
		}
	}
}

void Game::DrawShip(COORD* pos, vector<COORD>* existingShips)
{
	SetConsoleCursorPosition(hStdout, *pos);
	SetConsoleTextAttribute(hStdout, CheckContains(existingShips, pos) == true ? 12 : 14);
	cout << "x";
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

