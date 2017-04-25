#pragma once
#include <stdio.h> 
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <map>
#include "BattleGrid.h"

using namespace std;

class Game
{
public:
	Game();

private:
	enum
	{
		KEY_ESC = 27,
		KEY_ENTER = 13,
		ARROW_UP = 256 + 72,
		ARROW_DOWN = 256 + 80,
		ARROW_LEFT = 256 + 75,
		ARROW_RIGHT = 256 + 77,
		KEY_Q = 81,
		KEY_q = 113,
		KEY_E = 69,
		KEY_e = 101,
		KEY_R = 82,
		KEY_r = 114
	};

	#pragma region Properties
	const HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	const int gridSize = 7;

	int scorePlayer;
	int scoreCpu;
	int SelectedShip = 2;
	//map<int, short> Ships = { {4, 1}, {3, 2}, {2, 3}, {1, 4} };
	int Ships[2][4] = { { 4, 3, 2, 1 },
						{ 1, 2, 3, 4 } };

	bool IsHorizontal = true;

	vector<COORD> ShipCoordinates;
	COORD cursorPos;
	COORD centerPos;
	COORD lastPos;
	#pragma endregion

	#pragma region Methods
	int GetCode();
	bool CheckContains(vector<COORD>* grid, COORD* pos);

	void Start();
	void End();
	void Ship(COORD* pos, bool highlight);
	void CreateShips(BattleGrid* grid);
	void DrawShip(COORD* pos, vector<COORD>* existingShips);
	void UpdateShipCount(int x, int y);
	void UpdateCursor(int x, int y, char cursor);
	void UpdateScoreboard(int x, int y);
	#pragma endregion
};

