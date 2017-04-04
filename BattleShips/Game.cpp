#include "stdafx.h"
#include "Game.h"
#include "BattleGrid.h"
#include "TextMessage.h"

Game::Game()
{
	BattleGrid gridA(1, 0, &gridSize);
}

void Game::CreateShip()
{
}

void Game::Start()
{
	BattleGrid gridA(1, 0, &gridSize);
	//gridA.FillGrid();

	BattleGrid gridB(78 - gridSize * 3, 0, &gridSize);
	//gridB.FillGrid();

	TextMessage scoreTable(33, 8, "You   CPU\n 1  -  0 ", "Score", true);

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD destCoord;

	destCoord.X = 0;
	destCoord.Y = gridSize * 2 + 3;
	SetConsoleCursorPosition(hStdout, destCoord);
}

void Game::End()
{
	string msg = 
		scorePlayer > scoreCpu ? "You won!" :
		scorePlayer < scoreCpu ? "You lost!" : 
		"It's a tie!";

	TextMessage endGameMessage(0, 0, msg, "Game over!");
}