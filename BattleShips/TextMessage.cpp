#include "stdafx.h"
#include "TextMessage.h"

TextMessage::TextMessage(int x, int y, string message)
{
	Message = &message;

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD destCoord;

	destCoord.X = x;
	destCoord.Y = y;
	SetConsoleCursorPosition(hStdout, destCoord);

	cout << Edge << GenerateLine(Message->length(), '-') << Edge;

	destCoord.X = x;
	destCoord.Y = y + 1;
	SetConsoleCursorPosition(hStdout, destCoord);

	cout << Column << GenerateLine(Message->length(), ' ') << Column;

	destCoord.X = x;
	destCoord.Y = y + 2;
	SetConsoleCursorPosition(hStdout, destCoord);

	cout << Column << Margin << *Message << Margin << Column;

	destCoord.X = x;
	destCoord.Y = y + 3;
	SetConsoleCursorPosition(hStdout, destCoord);

	cout << Column << GenerateLine(Message->length(), ' ') << Column;

	destCoord.X = x;
	destCoord.Y = y + 4;
	SetConsoleCursorPosition(hStdout, destCoord);

	cout << Edge << GenerateLine(Message->length(), '-') << Edge << "\n";

	Length = Message->length();
}

TextMessage::TextMessage(int x, int y, string message, string title)
{
	Title = &title;
	Message = &message;

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD destCoord;

	ScaleString(Message->length(), Title->length(), Message);

	destCoord.X = x;
	destCoord.Y = y;
	SetConsoleCursorPosition(hStdout, destCoord);

	cout << Edge << Row << *Title << GenerateTitle(Message->length()) << Edge;

	destCoord.X = x;
	destCoord.Y = y + 1;
	SetConsoleCursorPosition(hStdout, destCoord);

	cout << Column << GenerateLine(Message->length(), ' ') << Column;

	destCoord.X = x;
	destCoord.Y = y + 2;
	SetConsoleCursorPosition(hStdout, destCoord);

	cout << Column << Margin << *Message << Margin << Column;

	destCoord.X = x;
	destCoord.Y = y + 3;
	SetConsoleCursorPosition(hStdout, destCoord);

	cout << Column << GenerateLine(Message->length(), ' ') << Column;

	destCoord.X = x;
	destCoord.Y = y + 4;
	SetConsoleCursorPosition(hStdout, destCoord);

	cout << Edge << GenerateLine(Message->length(), '-') << Edge << "\n";

	Length = Message->length() <= Title->length() ? Title->length() : Message->length();
}

TextMessage::TextMessage(int x, int y, string message, string title, bool wrap)
{
	Title = &title;
	Message = &message;

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD destCoord;

	if (wrap)
	{
		vector<string> wrappedText = BreakLines(Message);
		int id = FindLargest(wrappedText);

		ScaleString(wrappedText[id].length(), Title->length() - 2 * Margin.length() - 2, &wrappedText[id]);

		destCoord.X = x;
		destCoord.Y = y;
		SetConsoleCursorPosition(hStdout, destCoord);
		
		cout << Edge << Row << *Title << GenerateTitle(wrappedText[id].length()) << Edge;
		
		destCoord.X = x;
		destCoord.Y = y + 1;
		SetConsoleCursorPosition(hStdout, destCoord);
		
		cout << Column << GenerateLine(wrappedText[id].length(), ' ') << Column;

		int i = 0;

		while(i < wrappedText.size())
		{
			ScaleString(wrappedText[i].length(), wrappedText[id].length() - 2 * Margin.length(), &wrappedText[i]);		

			destCoord.X = x;
			destCoord.Y = y + 2 + i;
			SetConsoleCursorPosition(hStdout, destCoord);
			
			cout << Column << Margin << wrappedText[i] << Margin << Column;

			i++;
		}

		destCoord.X = x;
		destCoord.Y = y + 2 + i;
		SetConsoleCursorPosition(hStdout, destCoord);

		cout << Column << GenerateLine(wrappedText[id].length(), ' ') << Column;

		destCoord.X = x;
		destCoord.Y = y + 3 + i;
		SetConsoleCursorPosition(hStdout, destCoord);

		cout << Edge << GenerateLine(wrappedText[id].length(), '-') << Edge << "\n";

		Length = wrappedText[id].length();
	}
	else
	{
		ScaleString(Message->length(), Title->length(), Message);

		destCoord.X = x;
		destCoord.Y = y;
		SetConsoleCursorPosition(hStdout, destCoord);

		cout << Edge << Row << *Title << GenerateTitle(Message->length()) << Edge;

		destCoord.X = x;
		destCoord.Y = y + 1;
		SetConsoleCursorPosition(hStdout, destCoord);

		cout << Column << GenerateLine(Message->length(), ' ') << Column;

		destCoord.X = x;
		destCoord.Y = y + 2;
		SetConsoleCursorPosition(hStdout, destCoord);

		cout << Column << Margin << *Message << Margin << Column;

		destCoord.X = x;
		destCoord.Y = y + 3;
		SetConsoleCursorPosition(hStdout, destCoord);

		cout << Column << GenerateLine(Message->length(), ' ') << Column;

		destCoord.X = x;
		destCoord.Y = y + 4;
		SetConsoleCursorPosition(hStdout, destCoord);

		cout << Edge << GenerateLine(Message->length(), '-') << Edge << "\n";

		Length = Message->length() <= Title->length() ? Title->length() : Message->length();
	}
}

int TextMessage::FindLargest(vector<string> stringList)
{
	int maximum = 0;
	int id = 0;

	for (int i = 0; i < stringList.size(); i++)
	{
		if (stringList[i].size() > maximum)
		{
			maximum = stringList[i].size();
			id = i;
		}
	}

	return id;
}

vector<string> TextMessage::BreakLines(string* text)
{
	vector<string> wrappedText;
	istringstream ss(*text);
	string token;

	while (getline(ss, token, '\n')) {
		wrappedText.push_back(token);
	}

	return wrappedText;
}

string TextMessage::GenerateLine(int msgLength, char c)
{
	return string(2 * Margin.length() + msgLength, c);
}

string TextMessage::GenerateTitle(int msgLength)
{
	return string(2 * Margin.length() + msgLength - Title->length() - 1, '-');
}

void TextMessage::ScaleString(int a, int b, string* text)
{
	if (a < b)
	{
		int length = b - a + 2 * Margin.length();

		for (int i = 0; i < length; i++)
		{
			text->append(" ");
		}
	}
}