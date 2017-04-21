#pragma once
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

class BattleGrid
{
public:
	BattleGrid(int x, int y, const int *size);
	void FillGrid(vector<COORD>* grid);
	void ClearGrid();
	COORD GetCenter();
	vector<vector<COORD>> Grid;

	int X;
	int Y;

private:
	const HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	const int ColorHighlight = 10;
	const int ColorDefault = 15;
};

