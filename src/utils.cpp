#include "Menus.h"


void clearScreen(){
	system("cls");
}

void pauseScreen(){
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
