#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

class BattleGrid
{
public:
	BattleGrid(int x, int y, int size);
	vector<vector<COORD>> Grid;

private:
	int ColorHighlight = 10;
	int ColorDefault = 15;
};

