#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

#include "defs.h"
#include "utils.h"
#include "Accomodation.h"
#include "Date.h"
#include "Reservation.h"


using namespace std;

typedef vector<Accomodation* >::iterator itAccomodation;

class User {
private:
	string username;
	string password;
	string name;
	vector<Reservation> reservations;

public:
	
	/**
	* @brief User constructor
	*
	* @param username
	*
	* @param password
	*
	* @param name
	*
	*/
	User(string username, string password, string name);

	/**
	*
	* @return name of the user
	*
	*/
	string getName() const { return name; }


	/**
	* @brief changes the name of the user
	*
	* @param name
	*
	*/
	void setName(string name) { this->name = name; }

	/**
	*
	* @return  password of the user
	*
	*/
	string getPassword() const { return password; }

	/**
	* @brief changes user password
	*
	* @param password
	*
	*/
	void setPassword(string password) { this->password = password; }

	/**
	*
	* @return username
	*
	*/
	string getUsername() const { return username; }

	/**
	* @brief changes username
	*
	* @param username
	*
	*/
	void setUsername(string username) { this->username = username; }
	
	/**
	* @brief shows reservations
	*
	*
	*/
	void showReservations()const;
	
	/**
	*
	* @return reservations
	*
	*/
	vector<Reservation> getReservations() const { return reservations; };
	
	/**
	* @brief shows reservations
	*
	*
	*/
	void setReservations(vector<Reservation> res) { this->reservations = res; };
	
	/**
	* @brief deletes reservations
	*
	* @param position
	*/
	void deleteReservation(int position);
	
	/**
	* @brief equal operator
	*
	* @param user
	*
	* @return if it went well
	*/
	bool operator== (const User & usr) const;
};


class Suplier : public User {
private:
	int nif;
	string adress;
	vector <Accomodation*> accomodations;

public:
	
	/**
	* @brief creates a new suplier
	*
	* @param user
	*
	* @param password
	*
	* @param name
	*
	* @param nif
	*
	* @adress
	*/
	Suplier(string username, string password, string name, int nif, string adress);
	
	/**
	* @brief adds accomodation
	*
	*/
	void addAccomodation();
	
	/**
	* @brief adds accomodation from file
	*
	* @param acc
	*/
	void addAccomodationFile(Accomodation * acc);
	
	/**
	* @brief shows accomodations
	*
	*/
	void showAccomodations()const;
	
	/**
	* @brief gets accomodations
	*
	* @return accomodations
	*/
	vector<Accomodation*> getAccomodations() const { return accomodations; }
	
	/**
	* @brief sets accomodations
	*
	* @param accomodations
	*/
	void setAccomodations(vector<Accomodation*> accomodations) { this->accomodations = accomodations; }
	
	/**
	* @brief gets adress
	*
	* @return adress
	*/
	string getAdress() const { return adress; }

	/**
	* @brief sets adress
	*
	* @param adress
	*/
	void setAdress(string adress) { this->adress = adress; }

	/**
	* @brief gets NIF
	*
	* @return NIF
	*/
	int getNIF() const { return nif; }

	/**
	* @brief saves suplier in the file
	*
	* @param out supliers file
	*/
	void save(ofstream & out) const;

	/**
	* @brief adds reservation to the vector of reservations
	*
	* @param reservation
	*/
	void addReservation(Reservation res);

	/**
	* @brief displays teh percentage of the fee for each accomodation and the fees to pay for the reservations confirmed
	*
	*/
	void showFees()const;

	/**
	* @brief adds a new accomodation
	*
	* @return accomodation
	*/
<<<<<<< HEAD
	Accomodation* addAccomodation2(); 
=======
	Accomodation addAccomodation2(); 
>>>>>>> origin/master

	/**
	* @brief compares supliers
	*
 	* @param c the suplier being compared
	*
	* @return true if the suplier name is alphabetical minor 
	*/
	bool operator<(const Suplier & c) const;


	/**
	* @brief overload of << operator, shows the suplier information
	*
	* @param out the ofstream used
	*
	* @param s suplier whose information is being showed
	*
	* @return ostream 
	*/
	friend ostream &operator<<(ostream & out, const Suplier & s);
	
};

/**
* @brief asks for the prices of each accomodation, called from within addAccomodations()
*
* @param p_night price for night
*
* @param p_month price for month
*
* @param p_year price for year
*
*/
void askForPrice(float & p_night, float & p_week, float & p_month);

/**
* @brief asks for the gap of dates that each accomodation is unavailable, called from within addAccomodations()
*
* @param p_night price for night
*
* @param p_month price for month
*
* @param p_year price for year
*
*/
void askForAvailability(vector < pair<Date, Date>>&  unavailableDates);

/**
* @brief selects a bedroom type
*
* @param the bedroom type that is being selected
*
*/
void writeBedroomType(int x);

/**
* @brief selects a establishment type
*
* @param the establishment type that is being selected
*
*/
void writeEstabliType(int x);

/**
* @brief selects a bed type
*
* @param the bed type that is being selected
*
*/
void writeBedType(int x);


/**
* @brief selects a bed type
*
* @return bedroomType that was selected
*
*/
bedroomType chooseBedType();

/**
* @brief selects a establishment
*
* @return establishment that was selected
*
*/
establishment chooseEst();


class Client : public User {

private:
	int points;
	string adress;

public:
	/**
	* @brief Client constructor
	*
	* @param username
	*
	* @param password
	*
	* @param name
	*
	* @param points, default 0
	*
	* @param adress
	*
	*/
	Client(string username, string password, string name, string adress, int points = 0);

	/**
	* @brief gets points
	*
	* @return po0ints
	*/
	int getPoints() const { return points; };

	/**
	* @brief gets adress
	*
	* @return adress
	*/
	string getAdress() const { return adress; };

	/**
	* @brief adds a reservations to the vector reservations and increments the points based on the price
	*
	* @param res
	*/
	void addReservation(Reservation res);

	/**
	* @brief saves client uin the file
	*
	* @param out cleints file
	*/
	void save(ofstream & out) const;

	/**
	* @brief decides whereas a client is inactive or not
	*
	* @return true if the Client does not do a reservation for more than a year, false otherwise
	*/
	bool isInactiveClient();

	/**
	* @brief decides whereas a client is inactive or not
	*
	* @param ostream that is being used 
	*
	* @param cli the client wich information is going to be showed
	*
	* @return ostream with the client information
	*/
	friend ostream &operator<<(ostream & out, const Client  & cli); // comment later

};