#pragma once
#include <windows.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// Tato třída vykresluje do konzole rámečku s textem.
class TextMessage
{
public:
	/* Zde se nachází konstruktory, které se volají při 
	 * tvorbě nového objektu třídy TextMessage.
	 * Je tu více kontruktoru pro poskytnutí více možností
	 * nastavení v případě, že se tato třída bude využívat v 
	 * jiném programu. */
	#pragma region Constructors
	/* int x, int y nastavují pozici rámečku v konzoli.
	 * X určuje posun rámečku podle horizontální roviny - mezery.
	 * Y určuje posun rámečku podle vertikální roviny - nové řádky.
	 *
	 * string message nastavuje text zprávy, který bude obklopen rámečkem.
	 *
	 * string title nastavuje záhlaví rámečku.
	 * 
	 * bool wrap nastavuje zarovnání textu. 
	 *  - V případě, že text nemá nové řádk musí byt nastavený na hodnotu false. 
	 *  - V opačném případě, kdy text má nové řádky musí byt nastavený na hodnotu true.	*/
	TextMessage(int x, int y, string message);
	TextMessage(int x, int y, string message, string title);
	TextMessage(int x, int y, string message, string title, bool wrap);
	#pragma endregion

	// Sem se ukládá výsledná délka rámečku.
	int Length;

private:
	// Zde jsou vlastnosti.
	#pragma region Properties
	/* Následující 4 hodnoty mají vlastnost ¨const¨, 
	 * protože jsou konstantní - nemění se. */
	const char Edge = '+';				// Hrana
	const char Row = '-';				// Řádek
	const char Column = '|';			// Sloupec
	const string Margin = "  ";			// Mezera

	/* Následující 2 hodnoty mají po datovém typu ¨*¨,
	 * která říká, že to nejsou proměnné, ale odkazy. */
	string* Title;
	string* Message;
	#pragma endregion

	// Zde jsou metody (funkce).
	#pragma region Methods
	/* Metoda hledá největší hodnotu v poli textů.
	 * Velikost hodnoty se určuje podle počtu písmen.
	 * Po naléznutí největší hodnotu, metoda vrací
	 * pozici (index) prvku s největší hodnotou v poli. */
	int FindLargest(vector<string> stringList);

	/* Metoda hledá v textu nové řádky ¨\n¨. Tam, kde
	 * najde nový řádek, text rozpůlí a uloží polovinu
	 * do pole textů. Následující process se opakuje dokud
	 * se nenajdou všechny nové řádky. Po ukončení hledání
	 * metoda vrací pole textů. */
	vector<string> BreakLines(string* text);

	// Metoda kreslí rovnou čáru.
	string GenerateLine(int msgLength, char c);
	
	// Metoda kreslí záhlaví, které má před sebou dvě čáry a po sobě x čar.
	string GenerateTitle(int msgLength);

	// Přidává mezery po textu.
	void ScaleString(int a, int b, string* text);
	#pragma endregion
};