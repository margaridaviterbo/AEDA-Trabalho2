#pragma once


#include <string>


#include "Date.h"
#include "Accomodation.h"

using namespace std;

class Reservation {
private:
	static unsigned int lastID;
	int ID;
	Accomodation* accomodation;
	Date checkIN;
	Date checkOUT;
	float totalPrice;
public:
	Reservation() {};
	Reservation(int ID, Accomodation* accomodation, Date checkIN, Date checkOUT);
	Reservation(Accomodation* accomodation, Date checkIN, Date checkOUT);
	Reservation(unsigned int id) { ID = id; }
	static void setResLastID(unsigned int id);
	static unsigned int getLastID() { return lastID; }
	
	float getTotalPrice()const;

	friend ostream &operator<<(ostream & out, const Reservation  & reserv);
	friend bool operator == (const Reservation &acc1, const Reservation& acc2);

	void setAccomodation(Accomodation *a) {accomodation = a; };
	void setCheckIN(Date check_in) { checkIN = check_in; };
	void setCheckOUT(Date check_out) { checkOUT = check_out; };

	int getID() const { return ID; };
	void setID(unsigned int id) { ID = id; }
	void setID() { ID = lastID; };
	Date getCheckIn() const { return checkIN; }
	Date getCheckOut() const { return checkOUT; }
	Accomodation* getAccomodation() const { return accomodation; }

	float getFee() const;

	void save(ofstream & out) const;
	/*
	string getPeriodOfTime();
	

	Accomodation* getAccomodation() const;

	void setCheckIn(Date checkIn);
	
	void setCheckOut(Date checkOut);

	*/
};

