#pragma once
#include <stdio.h> 
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <random>
#include "BattleGrid.h"

using namespace std;

// Tato třída řídí hru.
class Game
{
public:
	// Kontruktor 
	Game();

private:
	/* ¨enum¨ umožňuje jednoduše přivlastnit  
	 * názvu hodnotu. Bez enum by zápis vypadal:
	 *	const int KEY_ESC = 27;
	 *	const int KEY_ENTER = 13; ...
	 * POZOR! Není to úplně to samé. Enum má navíc další vlastnosti.
	*/
	enum
	{
		KEY_ESC = 27,
		KEY_ENTER = 13,
		ARROW_UP = 256 + 72,
		ARROW_DOWN = 256 + 80,
		ARROW_LEFT = 256 + 75,
		ARROW_RIGHT = 256 + 77,
		KEY_R = 82,
		KEY_r = 114
	};

	// Zde jsou vlastnosti
	#pragma region Properties
	const char Ship = 'x';
	const char Hit = '@';
	const char Miss = 'o';

	// Ovladač konzole, který je nutný pro změnu barvy a pozice kurzoru.
	const HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	// Velikost herního pole.
	const int gridSize = 7;

	int ScorePlayer;
	int ScoreCpu;
	int PlayerShips;
	int CPUShips;

	// Pole, do kterých se ukládaji pozice lodí.
	vector<COORD> PlayerShipCoordinates;
	vector<COORD> CPUShipCoordinates;

	vector<COORD> PlayerMissCoordinates;
	vector<COORD> CPUMissCoordinates;

	vector<COORD> PlayerHitCoordinates;
	vector<COORD> CPUHitCoordinates;

	COORD centerPos;	// Sem se ukládá středová pozice mřížky
	COORD lastPos;		// Sem se ukládá poslední nastavená pozice kurzoru
	#pragma endregion

	// Zde jsou metody (funkce)
	#pragma region Methods
	// Metoda vrací číselnou hodnotu zmáčknuté klávesy
	int GetCode();

	// Metoda vrací náhodné číslo
	int GetRandom(const int* max);

	// Metoda kontroluje zda existuje v poli pozice daná pozice.
	// Na základě rozhodnutí se vrací buď hodnota true nebo false
	bool CheckContains(vector<COORD>* grid, COORD* pos);

	// Metoda zahájí hru
	void Start();

	// Metoda ukočuje hru
	void End();

	// Metoda kreslí na herní pole jednu figurku
	void Draw(COORD * pos, int color, const char * c);

	// Metoda žádá uživatele o zaplnění pole loděmi
	void PlayerCreateShips(BattleGrid* grid);

	// Metoda náhodně zaplní pole loděmi
	void CPUCreateShips(BattleGrid* grid);

	// Metoda vykresluje na konzoli počet lodí
	void UpdateShipCount(int x, int y);

	// Metoda vykresluje na konzoli skóre
	void UpdateScoreboard(int x, int y);

	// Metoda žádá uživatele o zvolení místa utoku
	void AttackCPU(BattleGrid* grid);

	// Metoda náhodně zvolí místo útoku
	void AttackPlayer(BattleGrid* grid);
	#pragma endregion
};

