#pragma once

#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <cstdlib>

#include "defs.h"
#include "utils.h"
#include "Company.h"



using namespace std;


class Menu {
private:
	bool exit;

public:
	Menu() { exit = 0; }



	/**
	* @brief displays initial Menu
	*
	* @param comp Company created
	*
	*/
	void start(Company & comp);

	/**
	* @brief displays clients Menu
	*
	* @param comp Company created
	*
	* @param it iterator to the specific Client
	*/
	void clientMenu(Company & comp, vector<Client>::iterator it);

	/**
	* @brief treats both Client and Suplier log in
	*
	* @param comp Company created
	*
	* @param user,' c' if the user is a client,' s' if the user is a suplier
	*/
	void logIn(Company &comp, char user);

	/**
	* @brief displays a Menu that allows the user either to register or log in
	*
	* @param comp Company created
	*
	* @param user,' c' if the user is a client,' s' if the user is a suplier
	*/
	void mainMenu(Company & comp, char user);

	/**
	* @brief displays the menu for clients hat are not registed
	*
	* @param comp Company created
	*
	*/
	void guestMenu(Company & comp);

	/**
	* @brief displays supliers menu
	*
	* @param comp Company created
	*
	* @param it itearator to the specific suplier
	*/
	void suplierMenu(Company & comp, vector<Suplier>::iterator it);



	///////////////////////////////////////////////////////
	void writeClientMenu(int x);

	void writeGuestMenu(int x);

	void writeOptionMainMenu(int);

	void writeOptionStartMenu(int);

	void writeSuplierMenu(int);

	void writeAdminMenu(int x);

	void mainMenu2(Company & comp, char user);
	void adminMenu(Company & comp);

	void novoMenu(Company & comp);

	// Por aqui todas as funções de Menu.h
	// na função "novoMenu()" inicializar exit =0;
	bool getExit() { return exit; }

};


/**
* @brief displays initial Menu
*
* @param comp Company created
*
*/
void start(Company & comp);

/**
* @brief displays clients Menu
*
* @param comp Company created
*
* @param it iterator to the specific Client
*/
void clientMenu(Company & comp, vector<Client>::iterator it);

/**
* @brief treats both Client and Suplier log in
*
* @param comp Company created
*
* @param user,' c' if the user is a client,' s' if the user is a suplier
*/
void logIn(Company &comp, char user);

/**
* @brief displays a Menu that allows the user either to register or log in
*
* @param comp Company created
*
* @param user,' c' if the user is a client,' s' if the user is a suplier
*/
void mainMenu(Company & comp, char user);

/**
* @brief displays the menu for clients hat are not registed
*
* @param comp Company created
*
*/
void guestMenu(Company & comp);

/**
* @brief displays supliers menu
*
* @param comp Company created
*
* @param it itearator to the specific suplier
*/
void suplierMenu(Company & comp, vector<Suplier>::iterator it);



///////////////////////////////////////////////////////
void writeClientMenu(int x);

void writeGuestMenu(int x);

void writeOptionMainMenu(int);

void writeOptionStartMenu(int);

void writeSuplierMenu(int);

void writeAdminMenu(int x);

void novoMenu(Company & comp);
