#include "stdafx.h"
#include "BattleGrid.h"

BattleGrid::BattleGrid(int x, int y, const int* size)
{
	COORD destCoord;
	destCoord.X = x;
	destCoord.Y = y;

	X = x;
	Y = y;

	SetConsoleTextAttribute(hStdout, ColorHighlight);
	SetConsoleCursorPosition(hStdout, destCoord);

	for (int i = 0; i <= *size; i++)
	{
		if (i == 0)	cout << "   ";
		else cout << i << "  ";
	}

	destCoord.Y += 2;
	SetConsoleCursorPosition(hStdout, destCoord);

	for (int i = 0; i < *size; i++)
	{
		SetConsoleTextAttribute(hStdout, ColorHighlight);
		cout << char(i + 65) << ' ';

		vector<COORD> row;

		for (int j = 0; j < *size; j++)
		{
			COORD pos;
			pos.X = x + (3 * (j + 1));
			pos.Y = y + (2 * (i + 1));
			
			row.push_back(pos);
			cout << ' ';
		}
		
		Grid.push_back(row);

		destCoord.Y += 2;
		SetConsoleCursorPosition(hStdout, destCoord);
	}
 }

void BattleGrid::FillGrid(vector<COORD>* grid, const char* c, int color)
{
	SetConsoleTextAttribute(hStdout, color);
	for (int j = 0; j < grid->size(); j++)
	{
		SetConsoleCursorPosition(hStdout, (*grid)[j]);
		cout << *c;
	}
}

void BattleGrid::ClearGrid()
{
	for (int x = 0; x < Grid.size(); x++)
	{
		for (int y = 0; y < Grid.size(); y++)
		{
			SetConsoleCursorPosition(hStdout, Grid[y][x]);
			cout << ' ';
		}
	}
}

COORD BattleGrid::GetCenter()
{
	int index = (int)(Grid.size() / 2 - 1);

	return Grid[index][index];
}

