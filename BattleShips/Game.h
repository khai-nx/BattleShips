#pragma once

using namespace std;

class Game
{
public:
	Game();

private:
	const int gridSize = 8;

	int scorePlayer;
	int scoreCpu;

	void Start();
	void End();
	void CreateShip();
};

