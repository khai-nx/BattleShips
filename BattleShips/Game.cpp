#include "stdafx.h"
#include "Game.h"
#include "BattleGrid.h"
#include "TextMessage.h"

Game::Game()
{
	BattleGrid gridA(1, 0, &gridSize);
	TextMessage(53, 1, "Place your ships    \nusing arrow keys.   \n\nUse Q and E to\ncycle through ships.\n\nBATTLESHIP\nCRUISER\nDESTROYER\nSUBMARINE", "Instructions", true);

	cursorPos.X = 73;
	cursorPos.Y = 11;

	UpdateShipCount(68, 9);
	UpdateCursor(cursorPos.X, cursorPos.Y, '<');

	centerPos = gridA.GetCenter();
	lastPos = centerPos;
	Ship(&centerPos, false);

	CreateShips(&gridA);
}

int Game::GetCode()
{
	int code = _getch();

	if (code == 0 || code == 224) code = 256 + _getch();

	return code;
}

bool operator ==(COORD const& lhs, COORD const& rhs)
{
	return lhs.X == rhs.X && lhs.Y == rhs.Y;
}

bool Game::CheckContains(vector<COORD>* grid, COORD * pos)
{
	if (count(grid->begin(), grid->end(), *pos) != 0) return true;
	else return false;
}

#pragma region Ship Methods
void Game::Ship(COORD* pos, bool highlight)
{
	switch (SelectedShip)
	{
	case 2:
		COORD a = *pos;

		if (IsHorizontal)
		{
			SetConsoleCursorPosition(hStdout, *pos);
			SetConsoleTextAttribute(hStdout, highlight == true ? (CheckContains(&ShipCoordinates, pos) == true ? 12 : 14) : 15);
			cout << 'x';

			a.X += 3;

			SetConsoleCursorPosition(hStdout, a);
			SetConsoleTextAttribute(hStdout, highlight == true ? (CheckContains(&ShipCoordinates, pos) == true ? 12 : 14) : 15);
			cout << 'x';
		}
		else
		{

		}
		break;
	case 3:
		SetConsoleCursorPosition(hStdout, *pos);
		SetConsoleTextAttribute(hStdout, highlight == true ? (CheckContains(&ShipCoordinates, pos) == true ? 12 : 14) : 15);
		cout << 'x';
		break;
	default:
		break;
	}
}

void Game::CreateShips(BattleGrid* grid)
{
	int numberOfShips = 8;
	int character;

	while (numberOfShips != 0)
	{
		character = GetCode();

		switch (character)
		{
		case KEY_ENTER:
			if (!CheckContains(&ShipCoordinates, &lastPos) && Ships[1][SelectedShip] != 0)
			{
				switch (SelectedShip)
				{
				case 0:
					ShipCoordinates.push_back(lastPos);
					if (IsHorizontal)
					{
						ShipCoordinates.push_back(COORD{ lastPos.X + 3, lastPos.Y });
						ShipCoordinates.push_back(COORD{ lastPos.X + 6, lastPos.Y });
						ShipCoordinates.push_back(COORD{ lastPos.X + 9, lastPos.Y });
					}
					else
					{
						ShipCoordinates.push_back(COORD{ lastPos.X, lastPos.Y + 3 });
						ShipCoordinates.push_back(COORD{ lastPos.X, lastPos.Y + 6 });
						ShipCoordinates.push_back(COORD{ lastPos.X, lastPos.Y + 9 });
					}
					break;
				case 1:
					ShipCoordinates.push_back(lastPos);
					if (IsHorizontal)
					{
						ShipCoordinates.push_back(COORD{ lastPos.X + 3, lastPos.Y });
						ShipCoordinates.push_back(COORD{ lastPos.X + 6, lastPos.Y });
					}
					else
					{
						ShipCoordinates.push_back(COORD{ lastPos.X, lastPos.Y + 3 });
						ShipCoordinates.push_back(COORD{ lastPos.X, lastPos.Y + 6 });
					}
					break;
				case 2:
					ShipCoordinates.push_back(lastPos);
					if (IsHorizontal)
					{
						ShipCoordinates.push_back(COORD{ lastPos.X + 3, lastPos.Y });
					}
					break;
				case 3:
					ShipCoordinates.push_back(lastPos);
					break;
				}
				Ship(&lastPos, true);

				lastPos = centerPos;
				Ship(&centerPos, false);

				Ships[1][SelectedShip]--;
				UpdateShipCount(68, 9);

				Beep(523, 50);
				Beep(659, 50);
				Beep(1046, 50);
			}
			else
			{
				Beep(440, 100);
				Beep(395, 125);
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
				Beep(523, 120);
			}
			else
			{
				Beep(440, 100);
				Beep(395, 125);
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
				Beep(523, 120);
			}
			else
			{
				Beep(440, 100);
				Beep(395, 125);
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
				Beep(523, 120);
			}
			else
			{
				Beep(440, 100);
				Beep(395, 125);
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
				Beep(523, 120);
			}
			else
			{
				Beep(440, 100);
				Beep(395, 125);
			}
			break;

		case KEY_Q:
		case KEY_q:
			if (cursorPos.Y != 9)
			{
				SetConsoleCursorPosition(hStdout, cursorPos);
				cout << ' ';
				cursorPos.Y--;
				SelectedShip--;
				UpdateCursor(cursorPos.X, cursorPos.Y, '<');
				grid->ClearGrid();
				grid->FillGrid(&ShipCoordinates);
				Ship(&lastPos, true);
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
				SelectedShip++;
				UpdateCursor(cursorPos.X, cursorPos.Y, '<');
				grid->ClearGrid();
				grid->FillGrid(&ShipCoordinates);
				Ship(&lastPos, true);
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
			IsHorizontal = !IsHorizontal;
			break;
		}
	}
}

void Game::DrawShip(COORD* pos, vector<COORD>* existingShips)
{
	/*SetConsoleCursorPosition(hStdout, *pos);
	SetConsoleTextAttribute(hStdout, CheckContains(existingShips, pos) == true ? 12 : 14);
	cout << "x";*/
	Ship(pos, true);
}
#pragma endregion

#pragma region Updaters
void Game::UpdateShipCount(int x, int y)
{
	COORD destCoord;
	destCoord.X = x;
	destCoord.Y = y;

	SetConsoleCursorPosition(hStdout, destCoord);
	SetConsoleTextAttribute(hStdout, 10);

	for (int i = 0; i < 4; i++)
	{
		cout << Ships[1][i] << 'x';

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
#pragma endregion

#pragma region Game Logic

#pragma endregion

#pragma region Game Controllers
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
#pragma endregion

