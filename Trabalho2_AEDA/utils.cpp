#include "Menus.h"


void clearScreen() {
	system("cls");
}

void pauseScreen() {
	getchar();
}

void upCase(string &str) {
	size_t i = 0;

	while (i < str.length()) {
		str.at(i) = tolower(str.at(i));
		i++;
	}

	if (str == "de" || str == "do" || str == "da" || str == "das" || str == "dos" || str == "e") return;

	str.at(0) = toupper(str.at(0));
}

void normalize(string &str)
{
	istringstream iss(str);
	string final_str;

	while (iss >> str) {
		upCase(str);
		final_str = final_str + " " + str;
	}

	final_str.erase(0, 1);

	str = final_str;
}

void trim(string &str)
{
	int i = 0;
	int spacesBegin = 0;
	while (' ' == str[i++])
	{
		spacesBegin++;
	}

	i = str.length();
	int spacesEnd = 0;

	while (' ' == str[--i])
	{
		spacesEnd++;
	}

	int strLength;

	strLength = str.length() - spacesBegin - spacesEnd;

	str = str.substr(spacesBegin, strLength);
}


int showOptions(int first, int last)
{

	string option_str;
	int option_int;

	try {

		cout << endl << TAB << "Opção: ";

		getline(cin, option_str);

		if (cin.eof()) throw InvalidInput();

		option_int = stoi(option_str);

		if (option_int < first || option_int > last) throw WrongOption(1, 5);

		return option_int;
	}
	catch (WrongOption wp) {
		cout << endl << wp;
		return showOptions(first, last);
	}
	catch (InvalidInput ii) {
		cout << endl << ii;
		cin.clear();
		return showOptions(first, last);
	}
	catch (invalid_argument) {
		cout << endl << TAB << "Erro na introdução dos dados." << endl;
		cout << TAB << "Deve introduzir um número." << endl;
		return showOptions(first, last);
	}


}

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto

COORD CursorPosition; // used for goto


void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

string insertPassword() {
	string password;
	char pass[32];
	char x;
	int i = 0;

	for (i = 0;;) {
		x = _getch();
		if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') || (x >= '0'&& x <= '9')) {
			pass[i] = x;
			++i;
			cout << "*";
		}
		if (x == '\b' && i >= 1)
		{
			cout << "\b \b";
			--i;
		}
		if (x == '\r' && i >= 5)
		{
			pass[i] = '\0';
			break;
		}
	}
	password = pass;
	cin.clear();
	return password;
}