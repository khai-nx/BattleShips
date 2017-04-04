#include "stdafx.h"
#include "BattleGrid.h"

BattleGrid::BattleGrid(int x, int y, const int* size)
{
	COORD destCoord;
	destCoord.X = x;
	destCoord.Y = y;

	SetConsoleTextAttribute(hStdout, ColorHighlight);
	SetConsoleCursorPosition(hStdout, destCoord);

	string delimiter((*size + 1) * 4 - 4, '-');

	for (int i = 0; i <= *size; i++) cout << i << "  ";

	destCoord.Y += 2;
	SetConsoleCursorPosition(hStdout, destCoord);

	for (int i = 0; i < *size; i++)
	{
		SetConsoleTextAttribute(hStdout, ColorHighlight);
		cout << char(i + 65) << ' ';

		SetConsoleTextAttribute(hStdout, ColorDefault);
		cout << ' ';

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

void BattleGrid::FillGrid(vector<COORD>* grid)
{
	for (int j = 0; j < grid->size(); j++)
	{
		SetConsoleCursorPosition(hStdout, (*grid)[j]);
		cout << 'x';
	}
}
