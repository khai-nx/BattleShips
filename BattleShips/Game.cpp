#include "stdafx.h"
#include "Game.h"
#include "BattleGrid.h"
#include "TextMessage.h"

Game::Game()
{
	BattleGrid gridA(1, 0, &gridSize);
	TextMessage(53, 1, "Place your ships    \nusing arrow keys.   \n\nRestart using R\n\nShips:", "Instructions", true);

	PlayerShips = 10;

	UpdateShipCount(68, 8);

	centerPos = gridA.GetCenter();
	lastPos = centerPos;
	Ship(&centerPos, false);

	CreateShips(&gridA);

	system("cls");

	Start();
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
	SetConsoleCursorPosition(hStdout, *pos);
	SetConsoleTextAttribute(hStdout, highlight == true ? (CheckContains(&PlayerShipCoordinates, pos) == true ? 12 : 14) : 15);
	cout << 'x';
}

void Game::CreateShips(BattleGrid* grid)
{
	int numberOfShips = 8;
	int character;

	while (PlayerShips!= 0)
	{
		character = GetCode();

		switch (character)
		{
		case KEY_ENTER:
			if (!CheckContains(&PlayerShipCoordinates, &lastPos) && PlayerShips!= 0)
			{
				PlayerShipCoordinates.push_back(lastPos);

				Ship(&lastPos, true);

				lastPos = centerPos;
				Ship(&centerPos, false);

				PlayerShips--;
				UpdateShipCount(68, 8);

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
				grid->FillGrid(&PlayerShipCoordinates);
				lastPos.Y -= 2;
				DrawShip(&lastPos, &PlayerShipCoordinates);
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
				grid->FillGrid(&PlayerShipCoordinates);
				lastPos.Y += 2;
				DrawShip(&lastPos, &PlayerShipCoordinates);
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
				grid->FillGrid(&PlayerShipCoordinates);
				lastPos.X -= 3;
				DrawShip(&lastPos, &PlayerShipCoordinates);
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
				grid->FillGrid(&PlayerShipCoordinates);
				lastPos.X += 3;
				DrawShip(&lastPos, &PlayerShipCoordinates);
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
			PlayerShipCoordinates.clear();
			PlayerShips = 10;
			grid->ClearGrid();		
			break;
		}
	}
}

void Game::DrawShip(COORD* pos, vector<COORD>* existingShips)
{
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
	cout << "   ";

	SetConsoleCursorPosition(hStdout, destCoord);
	cout << PlayerShips<< 'x';
}

void Game::UpdateScoreboard(int x, int y)
{

}
#pragma endregion

#pragma region Game Logic
void Game::AttackCPU(BattleGrid* grid)
{
	int character;

	while (true)
	{
		character = GetCode();

		switch (character)
		{
		case KEY_ENTER:
			if (CheckContains(&CPUShipCoordinates, &lastPos))
			{

			}
			else
			{

			}
			break;
		case ARROW_UP:
			if (lastPos.Y != grid->Y + 2)
			{
				grid->ClearGrid();
				lastPos.Y -= 2;
				Ship(&lastPos, false);
				Beep(523, 120);
			}
			else
			{
				Beep(440, 100);
				Beep(395, 125);
			}
			break;
		case ARROW_DOWN:
			if (lastPos.Y != grid->Y + grid->Grid.size() * 2)
			{
				grid->ClearGrid();
				lastPos.Y += 2;
				Ship(&lastPos, false);
				Beep(523, 120);
			}
			else
			{
				Beep(440, 100);
				Beep(395, 125);
			}
			break;
		case ARROW_LEFT:
			if (lastPos.X != grid->X + 3)
			{
				grid->ClearGrid();
				lastPos.X -= 3;
				Ship(&lastPos, false);
				Beep(523, 120);
			}
			else
			{
				Beep(440, 100);
				Beep(395, 125);
			}
			break;
		case ARROW_RIGHT:
			if (lastPos.X != grid->X + grid->Grid.size() * 3)
			{
				grid->ClearGrid();
				lastPos.X += 3;
				Ship(&lastPos, false);
				Beep(523, 120);
			}
			else
			{
				Beep(440, 100);
				Beep(395, 125);
			}
			break;
		}
	}
}

void Game::AttackPlayer(BattleGrid* grid)
{

}
#pragma endregion

#pragma region Game Controllers
void Game::Start()
{
	BattleGrid gridA(1, 0, &gridSize);
	gridA.FillGrid(&PlayerShipCoordinates);

	BattleGrid gridB(78 - gridSize * 3, 0, &gridSize);
	gridB.FillGrid(&CPUShipCoordinates);

	TextMessage scoreTable(33, 8, "You   CPU\n 1  -  0 ", "Score", true);

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD destCoord;

	destCoord.X = 0;
	destCoord.Y = gridSize * 2 + 3;
	SetConsoleCursorPosition(hStdout, destCoord);

	centerPos = gridB.GetCenter();
	lastPos = centerPos;

	while (PlayerShips != 0 || CPUShips != 0)
	{
		AttackCPU(&gridB);
		//AttackPlayer(&gridA);
	}
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

