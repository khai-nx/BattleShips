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

/*
MessageBox::MessageBox(string message, bool wrap)
{
	cout << "2 METHOD\n";
	Message = &message;

	if (wrap)
	{
		vector<string> wrappedText = BreakLines(*Message);
		int msgLength = FindLargest(&wrappedText);

		cout << Edge << GenerateLine(msgLength, '-') << Edge << "\n";
		cout << Column << GenerateLine(msgLength, ' ') << Column << "\n";
		for (int i = 0; i < wrappedText.size(); i++)
		{
			cout << Column << Margin << wrappedText[i] << Margin << Column << "\n";
		}		
		cout << Column << GenerateLine(msgLength, ' ') << Column << "\n";
		cout << Edge << GenerateLine(msgLength, '-') << Edge << "\n";
	}
	else
	{
		cout << Edge << GenerateLine(Message->length(), '-') << Edge << "\n";
		cout << Column << GenerateLine(Message->length(), ' ') << Column << "\n";
		cout << Column << Margin << *Message << Margin << Column << "\n";
		cout << Column << GenerateLine(Message->length(), ' ') << Column << "\n";
		cout << Edge << GenerateLine(Message->length(), '-') << Edge << "\n";
	}
	
}
*/

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

	ScaleString(Message->length(), Title->length(), Message);
}

int MessageBox::FindLargest(vector<string>* stringList)
{
	int maximum = 0;

	for (int i = 0; i < stringList->size(); i++)
	{
		if ((*stringList)[i].size() > maximum)
		{
			maximum = (*stringList)[i].size();
		}
	}

	return maximum;
}

vector<string> MessageBox::BreakLines(string text)
{
	return vector<string>();
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