#include "Accomodation.h"

unsigned int Accomodation::lastID = NULL;

void Accomodation::setAccLastID(unsigned int id) {
	if (Accomodation::lastID == NULL) {
		Accomodation::lastID = id;
	}
}



Accomodation::Accomodation(float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailable_dates) {
	this->price_night = price_night;
	this->price_week = price_week;
	this->price_month = price_month;
	this->location = location;
	this->unavailable_dates = unavailable_dates;
	this->id = ++lastID;
<<<<<<< HEAD

	
	lastReservation = Date("0/0/0");
	
	
}

Accomodation::Accomodation(unsigned int id, float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailable_dates) {
=======
	creationDateTime = getCurrentDate();
}

Accomodation::Accomodation(unsigned int id, float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailable_dates, Date creation_time) {
>>>>>>> origin/master
	this->price_night = price_night;
	this->price_week = price_week;
	this->price_month = price_month;
	this->location = location;
	this->unavailable_dates = unavailable_dates;
	this->id = id;

	lastReservation = Date("0/0/0");


}


bool Accomodation::operator == (const Accomodation &acc) const {
	
	return (acc.getID() == id);

}

void Accomodation::addDates(const pair<Date, Date> &dates) {
	unavailable_dates.push_back(dates);
}

void Accomodation::removeDates(Date checkIN, Date checkOUT) {

	vector<pair<Date, Date>>::iterator it;

	for (it = unavailable_dates.begin(); it != unavailable_dates.end(); it++) {
		if (it->first == checkIN && it->second == checkOUT)
		{
			unavailable_dates.erase(it);
			return;
		}
	}

}


<<<<<<< HEAD

=======
bool Accomodation::operator<(const Accomodation &acc) const {
	/*
	if (id == acc.getID())
		return false;

	bool diff;
	int timePeriod1, timePeriod2;
	Date today = getCurrentDate();

	//cout << "id1= " << id << " id2= " << acc.getID() << endl;
	//cout << "diffdays1" << endl;
	if (lastReservationID == 0)
		timePeriod1 = diffDays(today, creationDateTime);
	else
		timePeriod1 = diffDays(today, creationDateLastReservation);
	//cout << "diffdays2" << endl;
	if (acc.lastReservationID == 0)
		timePeriod2 = diffDays(today, acc.creationDateTime);
	else
		timePeriod2 = diffDays(today, creationDateLastReservation);
	//cout << "timeperiod1 = " << timePeriod1 << "timeperiod2 = " << timePeriod2 << endl;
	diff = timePeriod1 < timePeriod2;

	return diff;*/

	/*if (creationDateTime.getYear() < acc.creationDateTime.getYear())
		return true;
	else if (creationDateTime.getYear() == acc.creationDateTime.getYear() && creationDateTime.getMonth() < acc.creationDateTime.getMonth())
		return true;
	else if (creationDateTime.getYear() == acc.creationDateTime.getYear() && creationDateTime.getMonth() == acc.creationDateTime.getMonth() && creationDateTime.getDay() <= acc.creationDateTime.getDay())
		return true;
	else
		return false;*/
	
	return creationDateTime.getMonth() < acc.creationDateTime.getMonth();
}
>>>>>>> origin/master

Bedroom::Bedroom(float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailable_dates, establishment  est, bedroomType bed_type) :Accomodation(price_night, price_week, price_month, location, unavailable_dates) {
	this->est = est;
	this->bed_type = bed_type;
	setFee(0.05);
}

<<<<<<< HEAD
Bedroom::Bedroom(unsigned int id, float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailable_dates, establishment  est, bedroomType bed_type) :Accomodation(id, price_night, price_week, price_month, location, unavailable_dates) {
=======
Bedroom::Bedroom(unsigned int id, float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailable_dates, Date creation_time, establishment  est, bedroomType bed_type) :Accomodation(id, price_night, price_week, price_month, location, unavailable_dates, creation_time) {
>>>>>>> origin/master
	this->est = est;
	this->bed_type = bed_type;
	setFee(0.05);
}


Apartment::Apartment(float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailable_dates, int n_bed, bool suite) :Accomodation(price_night, price_week, price_month, location, unavailable_dates) {
	this->number_bedrooms = n_bed;
	this->suite = suite;
	setFee(0.15);
}

<<<<<<< HEAD
Apartment::Apartment(unsigned int id, float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailable_dates,  int n_bed, bool suite) : Accomodation(id, price_night, price_week, price_month, location, unavailable_dates) {
=======
Apartment::Apartment(unsigned int id, float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailable_dates, Date creation_time, int n_bed, bool suite) : Accomodation(id, price_night, price_week, price_month, location, unavailable_dates, creation_time) {
>>>>>>> origin/master
	this->number_bedrooms = n_bed;
	this->suite = suite;
	setFee(0.15);
}

void Accomodation::print() const {

<<<<<<< HEAD
	cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
	cout << left << "     " << setw(5) << id << setw(28) << location << setw(8) << price_night << setw(8) << price_week << setw(11) << price_month;
	
=======
	if (discount == 0) {
		cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(5) << id << setw(16) << location << setw(22) << price_night << setw(9) << price_week << setw(6) << price_month;
	}
	else {
		cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "DESCONTO " << discount*100 << "%!!!" << endl << setw(5) << id << setw(16) << location << setw(22) << price_night << setw(9) << price_week << setw(6) << price_month;
	}
>>>>>>> origin/master
}

void Bedroom::print() const {
	cout << TAB << "-> Quarto\n" << endl;

<<<<<<< HEAD
	cout << left << "     " << setw(5) << "ID" << setw(15) << "Local" << setw(40) << "Preco por | Noite | Semana | Mes |" << setw(30) << "Tipo" << setw(15) << "Establecimento" << endl;
=======
	cout << setw(5) << "ID" << setw(15) << "Local" << setw(40) << "Preco por | Noite | Semana | Mes |" << setw(27) << "Tipo" << setw(20) << "Establecimento" << endl;
>>>>>>> origin/master

	Accomodation::print();

	switch (bed_type) {
	case SINGLE:
		cout << setw(30) << "Simples";
		break;
	case DOUBLE_R:
		cout << setw(30) << "Duplo";
		break;
	case DOUBLE_EXTRA_BED:
		cout << setw(30) << "Duplo com cama adicional";
		break;
	case TRIPLE:
		cout << setw(30) << "Triplo";
		break;
	}
	enum establishment { HOTEL, BED_AND_BREAKFAST, SHARED_HOUSE };	//edificios onde podem estar os Bedroom


	switch (est) {
	case HOTEL:
		cout << setw(20) << "Hotel" << endl;
		break;
	case BED_AND_BREAKFAST:
		cout << setw(20)<< "Bed-N-Breakfast" << endl;
		break;
	case SHARED_HOUSE:
		cout << setw(20)<< "Casa Partilhada" << endl;
		break;
	}

	cout << "---------------------------------------------------------------------------------------------------------------------" << endl;

	vector<pair<Date, Date>> undates = getUnavailableDates();

	if (undates.size() != 0) {
		cout << TAB << "Datas Indisponíveis:" << endl;

		vector<pair<Date, Date>>::const_iterator it;

		for (it = undates.begin(); it != undates.end(); it++) {
			cout << TAB << (*it).first << " - " << (*it).second << endl;
		}
	}

	cout << "---------------------------------------------------------------------------------------------------------------------" << endl << endl;

}

void Flat::print() const {
	cout << TAB << "-> Flat\n" << endl;

<<<<<<< HEAD
	cout << left << "     " << setw(5) << "ID" << setw(15) << "Local" << setw(40) << "Preco por | Noite | Semana | Mes |" << setw(30) << "Inclui" << endl;
	
=======
	cout << setw(5) << "ID" << setw(15) << "Local" << setw(40) << "Preco por | Noite | Semana | Mes |" << setw(27) << "Inclui" << endl;

>>>>>>> origin/master
	Accomodation::print();

	cout << setw(50) << "1 Quarto       Cozinha        Casa de Banho" << endl;

	cout << "---------------------------------------------------------------------------------------------------------------------" << endl;

	vector<pair<Date, Date>> undates = getUnavailableDates();

	if (undates.size() != 0) {
		cout << TAB << "Datas Indisponiveis:" << endl;

		vector<pair<Date, Date>>::const_iterator it;

		for (it = undates.begin(); it != undates.end(); it++) {
			cout << TAB << (*it).first << " - " << (*it).second << endl;
		}
	}

	cout << "---------------------------------------------------------------------------------------------------------------------" << endl << endl;


}

void Apartment::print() const {
	cout << TAB << "-> Apartamento\n" << endl;

<<<<<<< HEAD
	cout << left << "     " << setw(5) << "ID" << setw(15) << "Local" << setw(40) << "Preco por | Noite | Semana | Mes |" << setw(30) << "Inclui" << endl;
	//cout << setw(5) << "ID" << setw(15) << "Local" << setw(40) << "Preco por | Noite | Semana | Mes |" << setw(27) << "Inclui" << endl;
=======
	cout << setw(5) << "ID" << setw(15) << "Local" << setw(40) << "Preco por | Noite | Semana | Mes |" << setw(27) << "Inclui" << endl;
>>>>>>> origin/master

	Accomodation::print();

	cout  << setw(1) << number_bedrooms << " Quarto/s";
	cout << "    Cozinha    Sala de Estar   ";
	if (suite) cout << "Suite" << endl;
	else cout << endl;
	
	cout << "---------------------------------------------------------------------------------------------------------------------" << endl;

	vector<pair<Date, Date>> undates = getUnavailableDates();

	if (undates.size() != 0) {
		cout << TAB << "Datas Indisponiveis:" << endl;

		vector<pair<Date, Date>>::const_iterator it;

		for (it = undates.begin(); it != undates.end(); it++) {
			cout << TAB << (*it).first << " - " << (*it).second << endl;
		}
	}

	cout << "---------------------------------------------------------------------------------------------------------------------" << endl << endl;


}

void Accomodation::saveAccomodation(ofstream & out)
{
	out << setw(5) << price_night << setw(5) << price_week << setw(5) << price_month << setw(14) << location << "         -    ";

	vector<pair<Date, Date>>::const_iterator it;

	vector<pair<Date, Date>> un = getUnavailableDates();

	for (it = un.begin(); it != un.end(); it++)
	{
		out << it->first << " " << it->second << "    ";
	}
	
	//date_time.erase(date_time.length() - 1);

<<<<<<< HEAD
	

	out << "   -" ;
=======
	out << "    -    " << creationDateTime << "    -";
>>>>>>> origin/master

}
void Bedroom::saveAccomodation(ofstream & out)
{
	out << setw(5) << getID();

	out << setw(10) << "BEDROOM";

	Accomodation::saveAccomodation(out);

	switch (bed_type) {
	case SINGLE:
		out << setw(10) << "SINGLE";
		break;
	case DOUBLE_R:
		out << setw(10) << "DOUBLE";
		break;
	case DOUBLE_EXTRA_BED:
		out << setw(20) << "DOUBLE_EXTRA_BED";
		break;
	case TRIPLE:
		out << setw(10) << "TRIPLE";
		break;
	}

	enum establishment { HOTEL, BED_AND_BREAKFAST, SHARED_HOUSE };

	switch (est) {
	case HOTEL:
		out << setw(10) << "HOTEL";
		break;
	case BED_AND_BREAKFAST:
		out << setw(20) << "BED_AND_BREAKFAST";
		break;
	case SHARED_HOUSE:
		out << setw(15) << "SHARED_HOUSE";
		break;
	}

	out << endl;


}

void Flat::saveAccomodation(ofstream & out)
{
	out << setw(5) << getID();

	out << setw(10) << "FLAT";

	Accomodation::saveAccomodation(out);

	out << endl;

}
void Apartment::saveAccomodation(ofstream & out)
{
	out << setw(5) << getID();

	out << setw(10) << "APARTMENT";

	Accomodation::saveAccomodation(out);

	out << setw(5) << number_bedrooms;

	if (suite)
		out << setw(11) << "SIM";
	else out << setw(11) << "NAO";

	out << endl;

}


void Accomodation::updateLastReservation(Date d){


	if (d > lastReservation)
		lastReservation = d;

}


void Accomodation::applyDiscount(){
	
		price_night = price_night - (price_night *0.1);
		price_month = price_month - (price_month *0.1);
		price_week = price_week - (price_week *0.1);

}
