#include "Reservation.h"


unsigned int Reservation::lastID = NULL;

void Reservation::setResLastID(unsigned int id) {
	if (Reservation::lastID == NULL) {
		Reservation::lastID = id;
	}
}



Reservation::Reservation(int ID, Accomodation* accomodation, Date checkIN, Date checkOUT, string name) {
	this->ID = ID;
	this->accomodation = accomodation;
	accomodation->setLastReservationID(ID);
	this->checkIN = checkIN;
	this->checkOUT = checkOUT;
	this->client = name;

}


Reservation::Reservation(Accomodation* accomodation, Date checkIN, Date checkOUT,string name) {
	this->accomodation = accomodation;
	this->checkIN = checkIN;
	this->checkOUT = checkOUT;
	this->client = name;

	pair<Date, Date> dates;
	dates.first = checkIN;
	dates.second = checkOUT;

	accomodation->addDates(dates);

	ID = ++lastID;
	accomodation->setLastReservationID(ID);
}

float Reservation::getTotalPrice()const {

	int in = checkIN.convert_date_int();
	int out = checkOUT.convert_date_int();

	int numDays = out - in;

	float total = 0;

	if (floor(numDays / 30) != 0)
	{
		float monthly = accomodation->getPriceMonth();
		total = total + floor(numDays / 30)*monthly;
		numDays = numDays % 30;
	}

	if (floor(numDays / 7) != 0)
	{
		float weekly = accomodation->getPriceWeek();
		total = total + floor(numDays / 7)*weekly;
		numDays = numDays % 7;
	}

	float daily = accomodation->getPriceNight();
	total = total + numDays*daily;

	return total;

}

ostream &operator<<(ostream & out, const Reservation  & reserv)
{

	out << setw(15) << reserv.ID
		<< setw(25) << reserv.accomodation->getID()
		<< setw(20) << "-" << reserv.checkIN << "-"
		<< setw(10) << "-" << reserv.checkOUT <<"-"
		<< setw(17) << reserv.getTotalPrice();
	out << endl;

	return out;

}

bool operator == (const Reservation &res1, const Reservation & res2) {
	return res1.ID == res2.ID;
}

void Reservation::save(ofstream & out) const
{
	out << setw(18) << client
		<< setw(5) << ID
		<< setw(5) << accomodation->getID()
		<< setw(10) << checkIN
		<< setw(10) << checkOUT
		<< endl;
}

float Reservation::getFee() const {
	float percentage = accomodation->getFee();
	float price = getTotalPrice();

	return price*percentage;
}



