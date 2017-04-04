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
	vector<vector<COORD>> Grid;

private:
	const HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	const int ColorHighlight = 10;
	const int ColorDefault = 15;
};

