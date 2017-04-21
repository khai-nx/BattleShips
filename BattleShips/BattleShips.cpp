#include "stdafx.h"
#include "Game.h"

void ShowConsoleCursor(bool showFlag);

int main()
{
	ShowConsoleCursor(false);

	Game a;

	cin.get();
    return 0;
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}