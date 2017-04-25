#pragma once
#include <windows.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class TextMessage
{
public:
	#pragma region Constructors
	TextMessage(int x, int y, string message);
	TextMessage(int x, int y, string message, string title);
	TextMessage(int x, int y, string message, string title, bool wrap);
#pragma endregion

	int Length;

private:
	#pragma region Properties
	const char Edge = '+';
	const char Row = '-';
	const char Column = '|';
	const string Margin = "  ";

	string* Title;
	string* Message;

	int FindLargest(vector<string> stringList);
	vector<string> BreakLines(string* text);

	string GenerateLine(int msgLength, char c);
	string GenerateTitle(int msgLength);
#pragma endregion

	void ScaleString(int a, int b, string* text);
};