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
		KEY_R = 82,
		KEY_r = 114
	};

	#pragma region Properties
	const HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	const int gridSize = 7;

	int scorePlayer;
	int scoreCpu;
	int PlayerShips;
	int CPUShips;

	vector<COORD> PlayerShipCoordinates;
	vector<COORD> CPUShipCoordinates;
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
	void UpdateScoreboard(int x, int y);

	void AttackCPU(BattleGrid* grid);
	void AttackPlayer(BattleGrid* grid);
	#pragma endregion
};

