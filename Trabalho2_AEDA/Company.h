#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <cstdlib>

#include "User.h"
#include "utils.h"

using namespace std;

class Company {	//implementar nesta classe as funcionalidades gerais do programa, os metodos para gerir a empresa
private:

	string clientsFile;
	string supliersFile;
	string reservationsFile;

public:
	vector<Suplier> supliers; // precisa de ser pointer??????
	vector<Client> clients;
	vector <Reservation> reservations;
	priority_queue <Accomodation> accomodationsDiscounts;

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
	*/
	void addReservationComp(Accomodation *a, Date init_date, Date final_date);

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

	void updateDiscounts();
};


void gotoXY(int x, int y);
