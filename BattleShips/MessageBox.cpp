#include "stdafx.h"
#include "MessageBox.h"

MessageBox::MessageBox(string message)
{
	Message = &message;

	cout << Edge << GenerateLine(Message->length(), '-') << Edge << "\n";
	cout << Column << GenerateLine(Message->length(), ' ') << Column << "\n";
	cout << Column << Margin << *Message << Margin << Column << "\n";
	cout << Column << GenerateLine(Message->length(), ' ') << Column << "\n";
	cout << Edge << GenerateLine(Message->length(), '-') << Edge << "\n";

	Length = Message->length();
}

MessageBox::MessageBox(string message, string title)
{
	Title = &title;
	Message = &message;

	ScaleString(Message->length(), Title->length(), Message);

	cout << Edge << Row << *Title << GenerateTitle(Message->length()) << Edge << "\n";
	cout << Column << GenerateLine(Message->length(), ' ') << Column << "\n";
	cout << Column << Margin << *Message << Margin << Column << "\n";
	cout << Column << GenerateLine(Message->length(), ' ') << Column << "\n";
	cout << Edge << GenerateLine(Message->length(), '-') << Edge << "\n";

	Length = Message->length() <= Title->length() ? Title->length() : Message->length();
}

MessageBox::MessageBox(string message, string title, bool wrap)
{
	Title = &title;
	Message = &message;

	if (wrap)
	{
		vector<string> wrappedText = BreakLines(Message);
		int id = FindLargest(wrappedText);

		ScaleString(wrappedText[id].length(), Title->length() - 2 * Margin.length() -2, &wrappedText[id]);
		cout << Edge << Row << *Title << GenerateTitle(wrappedText[id].length()) << Edge << "\n";
		cout << Column << GenerateLine(wrappedText[id].length(), ' ') << Column << "\n";

		for (int i = 0; i < wrappedText.size(); i++)
		{
			ScaleString(wrappedText[i].length(), wrappedText[id].length() - 2 * Margin.length(), &wrappedText[i]);
			cout << Column << Margin << wrappedText[i] << Margin << Column << "\n";
		}

		cout << Column << GenerateLine(wrappedText[id].length(), ' ') << Column << "\n";
		cout << Edge << GenerateLine(wrappedText[id].length(), '-') << Edge << "\n";

		Length = wrappedText[id].length();
	}
	else
	{
		ScaleString(Message->length(), Title->length(), Message);

		cout << Edge << Row << *Title << GenerateTitle(Message->length()) << Edge << "\n";
		cout << Column << GenerateLine(Message->length(), ' ') << Column << "\n";
		cout << Column << Margin << *Message << Margin << Column << "\n";
		cout << Column << GenerateLine(Message->length(), ' ') << Column << "\n";
		cout << Edge << GenerateLine(Message->length(), '-') << Edge << "\n";

		Length = Message->length() <= Title->length() ? Title->length() : Message->length();
	}
}

int MessageBox::FindLargest(vector<string> stringList)
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

vector<string> MessageBox::BreakLines(string* text)
{
	vector<string> wrappedText;
	istringstream ss(*text);
	string token;

	while (getline(ss, token, '\n')) {
		wrappedText.push_back(token);
	}

	return wrappedText;
}

string MessageBox::GenerateLine(int msgLength, char c)
{
	return string(2 * Margin.length() + msgLength, c);
}

string MessageBox::GenerateTitle(int msgLength)
{
	return string(2 * Margin.length() + msgLength - Title->length() - 1, '-');
}

void MessageBox::ScaleString(int a, int b, string* text)
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