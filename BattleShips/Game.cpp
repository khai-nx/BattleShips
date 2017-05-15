#include "stdafx.h"
#include "Game.h"
#include "BattleGrid.h"
#include "TextMessage.h"

Game::Game()
{
	// Vykreslení uživatelského rozhraní
	BattleGrid gridA(1, 0, &gridSize);
	TextMessage(53, 1, "Place your ships    \nusing arrow keys.   \n\nRestart using R\n\nShips:", "Instructions", true);

	PlayerShips = 10;
	CPUShips = 10;

	UpdateShipCount(68, 8);
	
	centerPos = gridA.GetCenter();
	lastPos = centerPos;
	
	// Volba pozic lodí
	PlayerCreateShips(&gridA);

	// Vyčistí obrazovku
	system("cls");
	
	// Zahájí hru
	Start();
}

int Game::GetCode()
{
	int code = _getch();

	if (code == 0 || code == 224) code = 256 + _getch();

	return code;
}

int Game::GetRandom(const int * max)
{
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution<int> uni(0, *max - 1); 

	return uni(rng);
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

void Game::Draw(COORD* pos, int color, const char* c)
{
	SetConsoleCursorPosition(hStdout, *pos);
	SetConsoleTextAttribute(hStdout, color);
	cout << *c;
}

void Game::PlayerCreateShips(BattleGrid* grid)
{
	int character;

	Draw(&centerPos, 14, &Ship);

	while (true)
	{
		goto Start;

	UpdateScreen:
		grid->ClearGrid();
		grid->FillGrid(&PlayerShipCoordinates, &Ship, (int)COLOR_WHITE);
		int color = CheckContains(&PlayerShipCoordinates, &lastPos) == true ? 12 : 14;
		Draw(&lastPos, color, &Ship);
		Beep(523, 120);

		if (PlayerShips != 0) goto Start;
		else break;
	
	Start:
		character = GetCode();

		switch (character)
		{
		case KEY_ENTER:
			if (!CheckContains(&PlayerShipCoordinates, &lastPos) && PlayerShips!= 0)
			{
				PlayerShipCoordinates.push_back(lastPos);

				Draw(&lastPos, 15, &Ship);

				lastPos = centerPos;

				int color = CheckContains(&PlayerShipCoordinates, &lastPos) == true ? 12 : 14;
				Draw(&centerPos, color, &Ship);

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
				lastPos.Y -= 2;
				goto UpdateScreen;
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
				lastPos.Y += 2;
				goto UpdateScreen;
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
				lastPos.X -= 3;
				goto UpdateScreen;
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
				lastPos.X += 3;
				goto UpdateScreen;
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
			UpdateShipCount(68, 8);
			grid->ClearGrid();		
			break;
		}
	}
}

void Game::CPUCreateShips(BattleGrid * grid)
{
	COORD* save;

	for (int i = 0; i < CPUShips; i++)
	{
		save = &grid->Grid[GetRandom(&gridSize)][GetRandom(&gridSize)];

		if (!CheckContains(&CPUShipCoordinates, save))
			CPUShipCoordinates.push_back(*save);
		else i--;
	}
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
	COORD destCoord;
	destCoord.X = x;
	destCoord.Y = y;

	SetConsoleCursorPosition(hStdout, destCoord);
	SetConsoleTextAttribute(hStdout, 15);
	cout << ScorePlayer << "  -  " << ScoreCpu;
}

#pragma endregion

#pragma region Game Logic

void Game::AttackCPU(BattleGrid* grid)
{
	bool selected = false;
	int character;

	Draw(&centerPos, 14, &Ship);

	while (!selected)
	{
		goto Start;

	UpdateScreen:
		grid->ClearGrid();
		grid->FillGrid(&CPUHitCoordinates, &Hit, (int)COLOR_RED);
		grid->FillGrid(&CPUMissCoordinates, &Miss, (int)COLOR_BLUE);
		int color = CheckContains(&CPUHitCoordinates, &lastPos) ||
					CheckContains(&CPUMissCoordinates, &lastPos) ? 
					(int)COLOR_RED : (int)COLOR_YELLOW;
		Draw(&lastPos, color, &Ship);
		Beep(523, 120);
		if (!selected) goto Start;
		else break;


	Start:
		character = GetCode();

		switch (character)
		{
		case KEY_ENTER:
			if (CheckContains(&CPUShipCoordinates, &lastPos) && !CheckContains(&CPUHitCoordinates, &lastPos))
			{
				ScorePlayer++;
				CPUShips--;
				CPUHitCoordinates.push_back(lastPos);
				Draw(&lastPos, (int)COLOR_RED, &Hit);
				UpdateScoreboard(37, 11);
				lastPos = centerPos;
				Beep(523, 120);
				selected = true;
			}
			else if (!CheckContains(&CPUMissCoordinates, &lastPos)
				 && !CheckContains(&CPUHitCoordinates, &lastPos))
			{
				CPUMissCoordinates.push_back(lastPos);
				Draw(&lastPos, (int)COLOR_BLUE, &Miss);
				Beep(523, 120);
				lastPos = centerPos;
				selected = true;
			}
			else
			{
				Beep(440, 100);
				Beep(395, 125);
			}
			break;
		case ARROW_UP:
			if (lastPos.Y != grid->Y + 2)
			{
				lastPos.Y -= 2;
				goto UpdateScreen;
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
				lastPos.Y += 2;
				goto UpdateScreen;
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
				lastPos.X -= 3;
				goto UpdateScreen;
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
				lastPos.X += 3;
				goto UpdateScreen;
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
	COORD* pos;
	
	while (true)
	{
		pos = &grid->Grid[GetRandom(&gridSize)][GetRandom(&gridSize)];

		if (CheckContains(&PlayerShipCoordinates, pos) && 
			!(CheckContains(&PlayerHitCoordinates, pos)))
		{
			PlayerShips--;
			ScoreCpu++;
			PlayerHitCoordinates.push_back(*pos);
			UpdateScoreboard(37, 11);
			break;
		}
		else if (!CheckContains(&PlayerMissCoordinates, pos) &&
				!(CheckContains(&PlayerHitCoordinates, pos)))
		{
			PlayerMissCoordinates.push_back(*pos);
			break;
		}		
	}
	
	grid->ClearGrid();
	grid->FillGrid(&PlayerShipCoordinates, &Ship, (int)COLOR_WHITE);
	grid->FillGrid(&PlayerHitCoordinates, &Hit, (int)COLOR_RED);
	grid->FillGrid(&PlayerMissCoordinates, &Miss, (int)COLOR_BLUE);
}

#pragma endregion

#pragma region Game Controllers

void Game::Start()
{
	ScorePlayer, ScoreCpu = 0, 0;

	BattleGrid gridA(1, 0, &gridSize);
	CPUShips = 10;
	gridA.FillGrid(&PlayerShipCoordinates, &Ship, (int)COLOR_WHITE);

	BattleGrid gridB(78 - gridSize * 3, 0, &gridSize);
	CPUCreateShips(&gridB);
	//gridB.FillGrid(&CPUShipCoordinates, &Ship); //Uncomment this line to check if grid was filled.
	//cin.get();
	TextMessage scoreTable(33, 8, "You   CPU\n         ", "Score", true);
	UpdateScoreboard(37, 11);

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD destCoord;

	destCoord.X = 0;
	destCoord.Y = gridSize * 2 + 3;
	SetConsoleCursorPosition(hStdout, destCoord);

	centerPos = gridB.GetCenter();
	lastPos = centerPos;

	while (true)
	{
		AttackCPU(&gridB);		// The user attacks the CPU's grid.

		if (ScorePlayer == 10) break;

		AttackPlayer(&gridA);	// The CPU attacks the user's grid.

		if (ScoreCpu == 10) break;
	}

	End();
}

void Game::End()
{
	system("cls");
	SetConsoleTextAttribute(hStdout, (int)COLOR_WHITE);
	string msg =
		ScorePlayer > ScoreCpu ? "You won!" :
		ScorePlayer < ScoreCpu ? "You lost!" :
		"It's a tie!";

	TextMessage endGameMessage(0, 0, msg, "Game over!");
}

#pragma endregion

