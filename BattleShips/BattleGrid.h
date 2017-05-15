#pragma once
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

class BattleGrid
{
public:
	BattleGrid(int x, int y, const int *size);

	#pragma region Methods
	void FillGrid(vector<COORD>* grid, const char* c, int color);
	void ClearGrid();
	#pragma endregion

	#pragma region Properties
	COORD GetCenter();
	vector<vector<COORD>> Grid;

	int X;
	int Y;
	#pragma endregion

private:
	#pragma region Properties
	const HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	const int ColorHighlight = 10;
	const int ColorDefault = 15;
	#pragma endregion
};

