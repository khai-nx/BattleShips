#include "stdafx.h"
#include "BattleGrid.h"

BattleGrid::BattleGrid(int x, int y, int size)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, ColorHighlight);

	string delimiter((size + 1) * 4 - 4, '-');

	for (int i = 0; i <= size; i++) cout << i << " | ";

	cout << "\n---" << delimiter << " \n";

	for (int i = 0; i <= size; i++)
	{
		SetConsoleTextAttribute(hStdout, ColorHighlight);
		cout << char(i + 65) << " |";

		SetConsoleTextAttribute(hStdout, ColorDefault);
		cout << " ";

		vector<COORD> row;

		for (int j = 0; j < size; j++)
		{
			COORD pos;
			pos.X = 4 * (j + 1);
			pos.Y = 2 * (i + 1);

			
			row.push_back(pos);
			cout << ' ' << " | ";
		}
		
		Grid.push_back(row);

		SetConsoleTextAttribute(hStdout, ColorHighlight);
		cout << "\n---";

		SetConsoleTextAttribute(hStdout, ColorDefault);
		cout << delimiter << "\n";
	}
 }