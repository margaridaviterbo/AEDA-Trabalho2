#pragma once


#include <fstream>
#include <sstream> 
#include <vector>
#include <stdlib.h>
#include <iomanip>
#include <conio.h>

#include "defs.h"

using namespace std;

/**
* @brief converts
*
* @return
*
*/
template <class T>
T fromString(const string& s) {
	stringstream ss(s);

	T t;
	ss >> t;

	return t;
}


template <class Comparable>
int sequentialSearch(const vector<Comparable> &v, Comparable x)
{
	for (unsigned int i = 0; i < v.size(); i++)
		if (v[i] == x)
			return i;   // encontrou
	return -1;     // n�o encontrou
}


// -------------------
//     EXCEP��ES
// -------------------


class WrongOption {
	unsInt min;
	unsInt max;
public:
	WrongOption(unsInt min, unsInt max) {
		this->min = min;
		this->max = max;
	}

	friend ostream & operator << (ostream &out, WrongOption &wo) {
		out << endl;
		out << TAB << "Op��o Inv�lida." << endl;
		out << TAB << "O n�mero Introduzido deve estar entre " << wo.min << " e " << wo.max << "." << endl;

		return out;
	}
};

class InvalidInput {
public:
	InvalidInput() {}

	friend ostream & operator << (ostream &out, InvalidInput &ii) {
		out << endl;
		out << TAB << "Erro na introdu��o dos dados." << endl;
		out << TAB << "Por favor volte a tentar." << endl;

		return out;
	}
};

class InvalidReservationID {
	unsigned int id;
public:
	InvalidReservationID(unsigned int id) { this->id = id; }

	friend ostream & operator << (ostream &out, InvalidReservationID &ii) {
		out << endl << endl << endl << endl;
		out << TAB_BIG  << TAB_BIG << "                            || Reserva ||" << endl << endl << endl;
		out << TAB << "N�o existe nenhuma reserva com o ID " << ii.id << "." << endl;
		out << TAB << "Por favor volte a tentar." << endl;

		return out;
	}
};



class InvalidDate {
public:
	InvalidDate() {}

	friend ostream & operator << (ostream &out, InvalidDate &id) {
		out << endl;
		out << TAB << "A data introduzida n�o � v�lida." << endl;
		out << TAB << "Por favor volte a tentar." << endl;

		return out;
	}
};

class InvalidLogIn {
public:
	InvalidLogIn() {}

	friend ostream & operator << (ostream &out, InvalidLogIn &ili) {
		out << endl;
		out << TAB << "Os dados de acesso est�o incorretos." << endl;
		out << TAB << "Por favor volte a tentar." << endl;

		return out;
	}
};

class InvalidUsername {
public:
	InvalidUsername() {}

	friend ostream & operator << (ostream &out, InvalidUsername &iu) {
		out << endl;
		out << TAB << "O nome de utilizador escolhido n�o se encontra dispon�vel." << endl;
		out << TAB << "Por favor escolha um nome de utilizador diferente." << endl;

		return out;
	}
};

class ErrorOpeningFile {
private:
	string file_type;
public:
	ErrorOpeningFile(string file_type) { this->file_type = file_type; };

	friend ostream & operator << (ostream &out, ErrorOpeningFile &eof) {
		out << endl;
		out << TAB << "N�o foi poss�vel abrir o ficheiro de " << eof.file_type << "." << endl;

		return out;
	}
};


void clearScreen();
void pauseScreen();
void upCase(string &str);
void normalize(string &str);
void trim(string &str);

int showOptions(int first, int last);

void gotoXY(int x, int y);

