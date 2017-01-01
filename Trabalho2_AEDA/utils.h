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
* @brief converts  string into a T type
*
* @return the T type
*
*/
template <class T>
T fromString(const string& s) {
	stringstream ss(s);

	T t;
	ss >> t;

	return t;
}

/**
* @brief sequential search algorithm
*
* @param v the comparable vector
*
* @param x the comparable element
*
* @return i position of the element x in the vector v, -1 if the element does not exist
*
*/
template <class Comparable>
int sequentialSearch(const vector<Comparable> &v, Comparable x)
{
	for (unsigned int i = 0; i < v.size(); i++)
		if (v[i] == x)
			return i;   // encontrou
	return -1;     // não encontrou
}

/**
* @brief clears the Screen
*
*/
void clearScreen();

/**
* @brief pauses the Screen
*
*/
void pauseScreen();

/**
* @brief upcases a string 
*
* @param str the string to be converted
*
*/
void upCase(string &str);

/**
* @brief normalizes a string
*
* @param str the string to be normalized
*
*/
void normalize(string &str);

/**
* @brief removes the " " at the begining and at the end of a string 
*
* @param str the string to be 'trimed'
*
*/
void trim(string &str);

/**
* @brief shows the Options between first and last that you are able to choose
*
* @param first
*
* @param last
*
* @return the chosen option
*
*/
int showOptions(int first, int last);

/**
* @brief goes to a specific pair of coordenates on the screen
*
* @param x position
*
* @param y position
*
*/
void gotoXY(int x, int y);


// -------------------
//     EXCEPÇÕES
// -------------------


class WrongOption {
	unsInt min;
	unsInt max;
public:

	/**
	* @brief wrong option construtor
	*
	* @param min
	*
	* @param max
	*
	*/
	WrongOption(unsInt min, unsInt max) {
		this->min = min;
		this->max = max;
	}

	/**
	* @brief overload of << operator for wrong option exception
	*
	* @param out , the ostream used
	*
	* @param wo
	*
	*/
	friend ostream & operator << (ostream &out, WrongOption &wo) {
		out << endl;
		out << TAB_BIG << TAB_BIG << "Opção Inválida." << endl;
		out << TAB_BIG << TAB_BIG << "O número Introduzido deve estar entre " << wo.min << " e " << wo.max << "." << endl;

		return out;
	}
};

class InvalidInput {
public:

	/**
	* @brief Invalid Input construtor
	*
	*/
	InvalidInput() {}

	/**
	* @brief overload of << operator for invalid input exception
	*
	* @param out , the ostream used
	*
	* @param ii
	*
	*/
	friend ostream & operator << (ostream &out, InvalidInput &ii) {
		out << endl;
		out << TAB_BIG << TAB_BIG << "Erro na introdução dos dados." << endl;
		out << TAB_BIG << TAB_BIG << "Por favor volte a tentar." << endl;

		return out;
	}
};

class InvalidReservationID {
	unsigned int id;
public:
	
	/**
	* @brief invalid reservation id construtor
	*
	*/
	InvalidReservationID(unsigned int id) { this->id = id; }

	/**
	* @brief overload of << operator for invalid reseravtion id exception
	*
	* @param out , the ostream used
	*
	* @param ii
	*
	*/
	friend ostream & operator << (ostream &out, InvalidReservationID &ii) {
		out << endl << endl << endl << endl;
		out << TAB_BIG  << TAB_BIG << "                            || Reserva ||" << endl << endl << endl;
		out << TAB_BIG << TAB_BIG << "Não existe nenhuma reserva com o ID " << ii.id << "." << endl;
		out << TAB_BIG << TAB_BIG << "Por favor volte a tentar." << endl;

		return out;
	}
};



class InvalidDate {
public:
	/**
	* @brief invalid date construtor
	*
	*/
	InvalidDate() {}

	/**
	* @brief overload of << operator for invalid date exception
	*
	* @param out , the ostream used
	*
	* @param id
	*
	*/
	friend ostream & operator << (ostream &out, InvalidDate &id) {
		out << endl;
		out << TAB_BIG << TAB_BIG << "A data introduzida não é válida." << endl;
		out << TAB_BIG << TAB_BIG << "Por favor volte a tentar." << endl;

		return out;
	}
};

class InvalidLogIn {
public:
	
	/**
	* @brief invalid login construtor
	*
	*/
	InvalidLogIn() {}

	/**
	* @brief overload of << operator for invalid login exception
	*
	* @param out , the ostream used
	*
	* @param ili
	*
	*/
	friend ostream & operator << (ostream &out, InvalidLogIn &ili) {
		out << endl << endl << endl;
		out << TAB_BIG  << TAB_BIG << "Os dados de acesso estão incorretos." << endl;
		out << TAB_BIG << TAB_BIG << "Por favor volte a tentar." << endl;

		return out;
	}
};

class InvalidUsername {
public:

	/**
	* @brief invalid username construtor
	*
	*/
	InvalidUsername() {}

	/**
	* @brief overload of << operator for invalid username exception
	*
	* @param out , the ostream used
	*
	* @param iu
	*
	*/
	friend ostream & operator << (ostream &out, InvalidUsername &iu) {
		out << endl << endl << endl;
		out << TAB_BIG << TAB_BIG << "O nome de utilizador escolhido não se encontra disponível." << endl;
		out << TAB_BIG << TAB_BIG << "Por favor escolha um nome de utilizador diferente." << endl;

		return out;
	}
};

class ErrorOpeningFile {
private:
	string file_type;
public:
	
	/**
	* @brief error opening file construtor
	*
	* @param file type
	*
	*/
	ErrorOpeningFile(string file_type) { this->file_type = file_type; };

	/**
	* @brief overload of << operator for error openig file exception
	*
	* @param out , the ostream used
	*
	* @param eof
	*
	*/
	friend ostream & operator << (ostream &out, ErrorOpeningFile &eof) {
		out << endl << endl;
		out << TAB_BIG << TAB_BIG << "Não foi possível abrir o ficheiro de " << eof.file_type << "." << endl;

		return out;
	}
};




