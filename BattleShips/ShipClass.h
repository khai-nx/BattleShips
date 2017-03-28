#pragma once
#include <vector>
using namespace std;

class ShipClass
{
public:
	vector<char> Body;

private:
	const char Alive = 'x';
	const char Dead = '@';
};

