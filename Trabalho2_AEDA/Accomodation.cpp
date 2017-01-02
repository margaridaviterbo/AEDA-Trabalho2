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
	creationDateTime = getCurrentDate();
}

Accomodation::Accomodation(unsigned int id, float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailable_dates, Date creation_time) {
	this->price_night = price_night;
	this->price_week = price_week;
	this->price_month = price_month;
	this->location = location;
	this->unavailable_dates = unavailable_dates;
	this->id = id;
	creationDateTime = creation_time;

}

bool Accomodation::operator == (const Accomodation &acc) const {
	return acc.getID() == id;

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


bool Accomodation::operator<(const Accomodation &acc) const {
	/*
	bool diff;
	int timePeriod1, timePeriod2;
	Date today = getCurrentDate();

	if (lastReservationID == 0)
		timePeriod1 = diffDays(today, creationDateTime);
	else
		timePeriod1 = diffDays(today, creationDateLastReservation);

	if (acc.lastReservationID == 0)
		timePeriod2 = diffDays(today, acc.creationDateTime);
	else
		timePeriod2 = diffDays(today, creationDateLastReservation);
	
	diff = timePeriod1 < timePeriod2;

	cout << "acc1 " << id << "acc2 " << acc.getID() << endl;
	cout << "Last Reservation ID: " << lastReservationID << endl;
	cout << "Create time: " << creationDateTime << "<" << acc.creationDateTime << endl;
	cout << "Last reservation: " << creationDateLastReservation << "<" << acc.creationDateLastReservation << "?" << diff << endl;
	return diff;*/
	return id < acc.getID();
}

Bedroom::Bedroom(float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailable_dates, establishment  est, bedroomType bed_type) :Accomodation(price_night, price_week, price_month, location, unavailable_dates) {
	this->est = est;
	this->bed_type = bed_type;
	setFee(0.05);
}

Bedroom::Bedroom(unsigned int id, float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailable_dates, Date creation_time, establishment  est, bedroomType bed_type) :Accomodation(id, price_night, price_week, price_month, location, unavailable_dates, creation_time) {
	this->est = est;
	this->bed_type = bed_type;
	setFee(0.05);
}


Apartment::Apartment(float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailable_dates, int n_bed, bool suite) :Accomodation(price_night, price_week, price_month, location, unavailable_dates) {
	this->number_bedrooms = n_bed;
	this->suite = suite;
	setFee(0.15);
}

Apartment::Apartment(unsigned int id, float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailable_dates, Date creation_time, int n_bed, bool suite) : Accomodation(id, price_night, price_week, price_month, location, unavailable_dates, creation_time) {
	this->number_bedrooms = n_bed;
	this->suite = suite;
	setFee(0.15);
}

void Accomodation::print() const {

	if (discount == 0) {
		cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(5) << id << setw(16) << location << setw(22) << price_night << setw(9) << price_week << setw(6) << price_month;
	}
	else {
		cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "DISCOUNT " << discount*100 << "%!!!" << endl << setw(5) << id << setw(16) << location << setw(22) << price_night << setw(9) << price_week << setw(6) << price_month;
	}
}

void Bedroom::print() const {
	cout << TAB << "-> Quarto\n" << endl;

	cout << setw(5) << "ID" << setw(15) << "Local" << setw(40) << "Preco por | Noite | Semana | Mes |" << setw(27) << "Tipo" << setw(20) << "Establecimento" << endl;

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

	cout << setw(5) << "ID" << setw(15) << "Local" << setw(40) << "Preco por | Noite | Semana | Mes |" << setw(27) << "Inclui" << endl;

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

	cout << setw(5) << "ID" << setw(15) << "Local" << setw(40) << "Preco por | Noite | Semana | Mes |" << setw(27) << "Inclui" << endl;

	Accomodation::print();

	cout  << setw(6) << number_bedrooms << " Quarto/s";
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

	out << "    -    " << creationDateTime << "    -";

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
