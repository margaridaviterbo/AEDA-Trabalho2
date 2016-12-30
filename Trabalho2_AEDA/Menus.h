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

public:

	/**
	* @brief constructor for the Main Menu, it starts the program
	*
	*/
	Menu(){};

	/**
	* @brief displays initial Menu
	*
	* @param comp Company created
	*
	*/
	void novoMenu(Company & comp);

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


	/**
	* @brief displays Administrator menu
	*
	* @param comp Company created
	*
	*/
	void adminMenu(Company & comp);


	/**
	* @brief displays Inactive Clients menu
	*
	* @param comp Company created
	*
	* @param ith itearator to the specific client
	*/
	void clientMenuHash(Company & comp, unordered_set<Client, hcli, eqcli>::iterator ith);
	
	/**
	* @brief writes Client Menu Options
	*
	* @param x option that is selected
	*
	*/
	void writeClientMenu(int x);

	/**
	* @brief writes Guest Menu Options
	*
	* @param x option that is selected
	*
	*/
	void writeGuestMenu(int x);

	/**
	* @brief writes Main Menu Options
	*
	* @param x option that is selected
	*
	*/
	void writeOptionMainMenu(int);

	/**
	* @brief writes Start Menu Options
	*
	* @param x option that is selected
	*
	*/
	void writeOptionStartMenu(int);

	/**
	* @brief writes Suplier Menu Options
	*
	* @param x option that is selected
	*
	*/
	void writeSuplierMenu(int);

	/**
	* @brief writes Administrator Menu Options
	*
	* @param x option that is selected
	*
	*/
	void writeAdminMenu(int x);

	/**
	* @brief executes the Suplier Add Accomodation Option
	*
	* @param comp Company created
	*
	* @param it itearator to the specific suplier
	*
	*/
	void OptionSuplierAddAccomodation(Company & comp, vector<Suplier>::iterator it);

	/**
	* @brief executes the Suplier Show Accomodations Option
	*
	* @param comp Company created
	*
	* @param it itearator to the specific suplier
	*
	*/
	void OptionSuplierShowAccomodations(Company & comp, vector<Suplier>::iterator it);

	/**
	* @brief executes the Suplier Information Option
	*
	* @param comp Company created
	*
	* @param it itearator to the specific suplier
	*
	*/
	void OptionSuplierInformation(Company & comp, vector<Suplier>::iterator it);

	/**
	* @brief executes the Suplier Reservations Option
	*
	* @param comp Company created
	*
	* @param it itearator to the specific suplier
	*
	*/
	void OptionSuplierReservations(Company & comp, vector<Suplier>::iterator it);

	/**
	* @brief executes the Suplier Show Fees Option
	*
	* @param comp Company created
	*
	* @param it itearator to the specific suplier
	*
	*/
	void OptionSuplierShowFees(Company & comp, vector<Suplier>::iterator it);

	/**
	* @brief executes the Client Add Reservation Option
	*
	* @param comp Company created
	*
	* @param it itearator to the specific client
	*
	*/
	void OptionClientAddReservation(Company & comp, vector<Client>::iterator it);

	/**
	* @brief executes the Client Show Reservations Option
	*
	* @param comp Company created
	*
	* @param it itearator to the specific client
	*
	*/
	void OptionClientShowReservations(Company & comp, vector<Client>::iterator it);

	/**
	* @brief executes the Client Cancel Reservation Option
	*
	* @param comp Company created
	*
	* @param it itearator to the specific client
	*
	*/
	void OptionClientCancelReservation(Company & comp, vector<Client>::iterator it);

	/**
	* @brief executes the Client Information Option
	*
	* @param comp Company created
	*
	* @param it itearator to the specific client
	*
	*/
	void OptionClientInformation(Company & comp, vector<Client>::iterator it);

	/**
	* @brief executes the Inactive Client Add Reservation Option
	*
	* @param comp Company created
	*
	* @param ith itearator to the specific inactive client
	*
	*/
	void OptionInaClientAddReservation(Company & comp, unordered_set<Client, hcli, eqcli>::iterator ith);

	/**
	* @brief executes the Inactive Client Show Reservations Option
	*
	* @param comp Company created
	*
	* @param ith itearator to the specific inactive client
	*
	*/
	void OptionInaClientShowReservations(Company & comp, unordered_set<Client, hcli, eqcli>::iterator ith);

	/**
	* @brief executes the Inactive Client Add Reservation Option
	*
	* @param comp Company created
	*
	* @param ith itearator to the specific inactive client
	*
	*/
	void OptionInaClientCancelReservation(Company & comp, unordered_set<Client, hcli, eqcli>::iterator ith);

	/**
	* @brief executes the Inactive Client Inforamation Option
	*
	* @param comp Company created
	*
	* @param ith itearator to the specific inactive client
	*
	*/
	void OptionInaClientInformation(Company & comp, unordered_set<Client, hcli, eqcli>::iterator ith);

	/**
	* @brief executes the Guest Add Reservation Option
	*
	* @param comp Company created
	*
	*/
	void OptionGuestAddAccomodation(Company & comp);

	/**
	* @brief executes the Guest Cancel Reservation Option
	*
	* @param comp Company created
	*
	*/
	void OptionGuestCancelReservation(Company & comp);

	/**
	* @brief executes the Guest Show Reservation Option
	*
	* @param comp Company created
	*
	*/
	void OptionGuestShowReservations(Company & comp);

	/**
	* @brief executes the Main Menu Register Option
	*
	* @param comp Company created
	*
	*/
	void OptionRegister(Company &comp, char user);

	/**
	* @brief executes the Main Menu Login Option
	*
	* @param comp Company created
	*
	*/
	void OptionLogin(Company &comp, char user);

	/**
	* @brief executes the Main Menu Login Option
	*
	* @return exit state, whereas you should exit the program
	*
	*/
	bool getExit() { return exit; }

};

