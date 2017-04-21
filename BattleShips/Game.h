#pragma once
#include <stdio.h> 
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <algorithm>
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

	const int gridSize = 8;
	
	int scorePlayer;
	int scoreCpu;
	int Ships[4]{ 1, 2, 3, 4 };

	vector<COORD> ShipCoordinates;

	const HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos;
	COORD centerPos;
	COORD lastPos;

	int GetCode();
	bool CheckContains(vector<COORD>* grid, COORD* pos);

	void Start();
	void End();
	void CreateShips(BattleGrid* grid);
	void DrawShip(COORD* pos, vector<COORD>* existingShips);
	void UpdateShipCount(int x, int y, int ships[]);
	void UpdateCursor(int x, int y, char cursor);
	void UpdateScoreboard(int x, int y);
};

