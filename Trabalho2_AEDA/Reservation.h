#pragma once


#include <string>
#include <ctime>

#include "Date.h"
#include "Accomodation.h"

using namespace std;

class Reservation {
private:
	time_t reservationDateTime;
	static unsigned int lastID;
	int ID;
	Accomodation* accomodation;
	Date checkIN;
	Date checkOUT;
	Date marking;
	float totalPrice;
	string client;
public:
	Reservation() {};

	/**
	* @brief reservation constructor with id
	*
	* @param ID
	*
	* @param accomodation
	*
	* @param checkIN
	*
	* @param checkOUT
	*
	* @param marking
	*
	*/
	Reservation(int ID, Accomodation* accomodation, Date checkIN, Date checkOUT, Date marking, string client, time_t date_time);


	/**
	* @brief reservation constructor
	*
	* @param accomodation
	*
	* @param checkIN
	*
	* @param checkOUT
	*
	*/
	Reservation(Accomodation* accomodation, Date checkIN, Date checkOUT, Date marking, string client); 

	/**
	* @brief reservation constructor with id only
	*
	* @param id
	*
	*/
	Reservation(unsigned int id) { ID = id; }

	/**
	* @brief sets last id
	*
	* @param id
	*
	*/
	static void setResLastID(unsigned int id);

	/**
	* @brief gets last id
	*
	* @return lastID
	*
	*/
	static unsigned int getLastID() { return lastID; }

	/**
	* @brief calculates price based on the number of days of the reservation
	*
	*/
	float getTotalPrice()const;

	/**
	* @brief displays reservation on the screen
	*
	* @param out cout
	*
	* @param reserv reservation to display
	*
	* @return out
	*/
	friend ostream &operator<<(ostream & out, const Reservation  & reserv);

	/**
	* @brief compares 2 reservations
	*
	* @param acc1
	*
	* @param acc2
	*
	* @return true if the reservations have the same id, false otherwise
	*/
	friend bool operator == (const Reservation &acc1, const Reservation& acc2);

	/**
	* @brief sets accomodation
	*
	* @param a
	*
	*/
	void setAccomodation(Accomodation *a) { accomodation = a; };

	/**
	* @brief sets check in
	*
	* @param check_in
	*
	*/
	void setCheckIN(Date check_in) { checkIN = check_in; };

	/**
	* @brief sets check out
	*
	* @param check_out
	*
	*/
	void setCheckOUT(Date check_out) { checkOUT = check_out; };

	/**
	* @brief gets id
	*
	* @return ID of the reservation
	*
	*/
	int getID() const { return ID; };

	/**
	* @brief sets id
	*
	* @param id
	*
	*/
	void setID(unsigned int id) { ID = id; }

	/**
	* @brief sets by default
	*
	*/
	void setID() { ID = lastID; };

	/**
	* @brief gets check In
	*
	* @return date of check IN
	*
	*/
	Date getCheckIn() const { return checkIN; }

	/**
	* @brief gets check OUT
	*
	* @return date of check OUT
	*
	*/
	Date getCheckOut() const { return checkOUT; }


	/**
	* @brief gets marking
	*
	* @return marking date
	*
	*/
	Date getMarking() const { return marking; }

	/**
	* @brief gets accomodation
	*
	* @return accomodation pointer
	*
	*/
	Accomodation* getAccomodation() const { return accomodation; }

	/**
	* @brief calculates the fee based on the type of the accomodation
	*
	* @return fee
	*
	*/
	float getFee() const;


	/**
	* @brief saves reservation in rservations file
	*
	* @param out reservations file
	*
	*/
	void save(ofstream & out) const;

	

};


