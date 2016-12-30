#pragma once

#include "BST.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <queue>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <unordered_set>
#include <algorithm>

#include "User.h"
#include "utils.h"


using namespace std;

struct eqcli {
	bool operator() (const Client &c1, const Client &c2) const {
		return c1 == c2;
	}
};

struct hcli {
	int operator() (const Client &c1) const {
		int v = 0;
		for (unsigned int i = 0; i < c1.getName().size(); i++)
			v = 37 * v + c1.getName()[i];
		return v;
	}
};


class Company {	//implementar nesta classe as funcionalidades gerais do programa, os metodos para gerir a empresa
private:
	vector<Suplier> supliers; 
	vector<Client> clients;
	//vector<Accomodation> accomodations;
	tr1::unordered_set<Client, hcli, eqcli> inactiveClients;
	BST<Reservation> reservationsBST;
	//static priority_queue <Accomodation> accomodationsDiscounts;

	string clientsFile;
	string supliersFile;
	string reservationsFile;

public:
	
	/**
	* @brief constructor for the Company based on the files provided
	*
	* @param clientsFile file of clients
	*
	* @param supliersFile file of supliers
	*
	* @param revervationsFile file of reservations
	*
	*/
	Company(string clientsFile, string supliersFile, string reservationsFile);

	/**
	* @brief initializes the vector supliers
	*
	* @param supliersFile file of supliers
	*
	*/
	void supliersInicialization(string supliersFile);

	/**
	* @brief initializes the vector reservations and updates the reservations of each suplier
	*
	* @param reservationsFile file of reservations
	*
	*/
	void reservationsInicialization(string reservationsFile);

	/**
	* @brief initializes the vector of clients
	*
	* @param clientsFile file of clients
	*
	*/
	void clientsInicialization(string clientsFile);

	/**
	* @brief handles the registantion of a suplier
	*
	*
	*/
	void registerSuplier();

	/**
	* @brief handles the registantion of a client
	*
	*
	*/
	void registerClient();

	/**
	* @brief verifies if the username and password of a suplier are correct
	*
	* @param username username of the suplier
	*
	* @param password password of the suplier
	*
	* @return iterator for the suplier with the username and password given
	*
	*/
	vector<Suplier>::iterator verifyLogInSup(string username, string password);

	/**
	* @brief displays the Company's supliers in alphabetic order
	*
	*
	*/

	void showSupliers();

	/**
	* @brief verifies if the username and password of a client are correct
	*
	* @param username username of the client
	*
	* @param password password of the client
	*
	* @return iterator for the client with the username and password given
	*
	*/
	vector<Client>::iterator verifyLogInCli(string username, string password);

	/**
	* @brief display the accomodations that correspond to the restrictions given by the client and asks him to choose onde of them
	*
	* @param location location of the accomodations that must be displayed
	*
	* @param initial_date check in date
	*
	* @param final_date check out date
	*
	* @return pointer to the accomodation chooe by the client or NULL pointer if there is no accomodation that respect the restrictions or if the id that the client chose does no exist
	*
	*/
	Accomodation* displayOffers(string location, Date initial_date, Date final_Date);

	/**
	* @brief adds a reservations to the reservations vector and to the suplier that owns tha accomodation a
	*
	* @param a accomodation linked to the reservation to add
	*
	* @param init_date check in date
	*
	* @param final_date check out date
	*
	* @param client clients name
	*
	*/
	void addReservationComp(Accomodation *a, Reservation res);

	/**
	* @brief ask the client wich reservation he wants to to cancel removes it from the vectors and displays the amount that the client must receive
	*
	* @return id of the reservation deleeted
	*/
	int cancelReservation();

	/**
	* @brief asks for the id of the reservation and displays it on the screen
	*
	*/
	void showReservation()const;

	/**
	* @brief saves changes of supliers, clients and reservations on the respective files
	*
	*/
	void saveChanges() const;

	/**
	* @brief saves changes in clients file
	*
	*/
	void saveClientsChanges() const;

	/**
	* @brief saves changes in supliers file
	*
	*/
	void saveSupliersChanges() const;

	/**
	* @brief saves changes in reservtaions file
	*
	*/
	void saveReservationsChanges() const;


	void showReservations() const;

	void showInactiveClients() const;
	
	void showActiveClients() const;

	bool isClientInactive(string username);

	unordered_set<Client, hcli, eqcli>::iterator verifyInactiveCliLogin(string username, string password);

	unordered_set<Client, hcli, eqcli>::iterator replaceHashClient(unordered_set<Client, hcli, eqcli>::iterator ith, int pos);

	vector<Client>::iterator reservationHash(unordered_set<Client, hcli, eqcli>::iterator ith, Reservation res);
  
  void updateDiscounts();

  void showInactiveClientsAdresses() const;
  
  void Company::updateAdresses();

	void updateDiscounts(Accomodation acc);

  
};


void gotoXY(int x, int y);