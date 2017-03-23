#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class MessageBox
{
public:
	MessageBox(string message);
	//MessageBox(string message, bool wrap);
	MessageBox(string message, string title);
	MessageBox(string message, string title, bool wrap);

	int Length;

private:
	const char Edge = '+';
	const char Row = '-';
	const char Column = '|';
	const string Margin = "  ";

	string* Title;
	string* Message;

	int FindLargest(vector<string>* stringList);
	vector<string> BreakLines(string text);

	string GenerateLine(int msgLength, char c);
	string GenerateTitle(int msgLength);

	void ScaleString(int a, int b, string* text);
};

