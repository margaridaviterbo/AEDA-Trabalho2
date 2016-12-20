#include "Accomodation.h"

unsigned int Accomodation::lastID = NULL;

void Accomodation::setAccLastID(unsigned int id) {
	if (Accomodation::lastID == NULL) {
		Accomodation::lastID = id;
	}
}



Accomodation::Accomodation(float price_night, float price_week, float price_month, string location, vector<pair<Date,Date>> unavailable_dates){
	this->price_night = price_night;
	this->price_week = price_week;
	this->price_month = price_month;
	this->location = location;
	this->unavailable_dates = unavailable_dates;

	this->id = ++lastID;
}

Accomodation::Accomodation(unsigned int id, float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailable_dates) {
	this->price_night = price_night;
	this->price_week = price_week;
	this->price_month = price_month;
	this->location = location;
	this->unavailable_dates = unavailable_dates;
	this->id = id;

}

bool Accomodation::operator == (const Accomodation &acc) const{
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



Bedroom::Bedroom(float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailable_dates, establishment  est, bedroomType bed_type):Accomodation(price_night, price_week, price_month,location, unavailable_dates){
	this->est = est;
	this->bed_type = bed_type;
	setFee(0.05);
}

Bedroom::Bedroom(unsigned int id, float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailable_dates, establishment  est, bedroomType bed_type) :Accomodation(id, price_night, price_week, price_month, location, unavailable_dates) {
	this->est = est;
	this->bed_type = bed_type;
	setFee(0.05);
}


Apartment::Apartment(float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailable_dates, int n_bed, bool suite) :Accomodation(price_night, price_week, price_month, location, unavailable_dates) {
	this->number_bedrooms = n_bed;
	this->suite = suite;
	setFee(0.15);
}

Apartment::Apartment(unsigned int id, float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailable_dates, int n_bed, bool suite) : Accomodation(id, price_night, price_week, price_month, location, unavailable_dates) {
	this->number_bedrooms = n_bed;
	this->suite = suite;
	setFee(0.15);
}

void Accomodation::print() const {

	cout << TAB << "ID: " << id << endl;
	cout << TAB << "Local: " << location << endl << endl;

	cout << TAB << "Preço por Noite: " << price_night << endl;
	cout << TAB << "Preço por Semana: " <<price_week << endl;
	cout << TAB << "Preço por Mês: " << price_month << endl << endl;

	if (unavailable_dates.size() == 0)return;
	cout << TAB << "Datas Indisponíveis:" << endl;

	vector<pair<Date, Date>>::const_iterator it;

	for (it = unavailable_dates.begin(); it != unavailable_dates.end(); it++) {
		cout << TAB << (*it).first << " - " << (*it).second << endl;
	}


}

void Bedroom::print() const{
	cout << TAB << "-> Quarto" << endl;

	Accomodation::print();

	cout << endl << TAB << "Tipo: ";

	switch (bed_type) {
	case SINGLE:
		cout << "Simples" << endl;
		break;
	case DOUBLE:
		cout << "Duplo" << endl;
		break;
	case DOUBLE_EXTRA_BED:
		cout << "Duplo com cama adicional" << endl;
		break;
	case TRIPLE:
		cout << "Triplo" << endl;
		break;
	}
	enum establishment { HOTEL, BED_AND_BREAKFAST, SHARED_HOUSE };	//edificios onde podem estar os Bedroom
	cout << endl << TAB << "Estabelecimento: ";

	switch (est) {
	case HOTEL:
		cout << "Hotel" << endl;
		break;
	case BED_AND_BREAKFAST:
		cout << "Bed-N-Breakfast" << endl;
		break;
	case SHARED_HOUSE:
		cout << "Casa Partilhada" << endl;
		break;
	}

	cout  << endl;


}

void Flat::print() const {
	 cout << TAB << "-> Flat" << endl;

	 Accomodation::print();

	cout << endl << TAB << "Inclui: " << endl;
	cout << TAB << "-> 1 Quarto" << endl;
	cout << TAB << "-> Cozinha" << endl;
	cout << TAB << "-> Casa de Banho" << endl;

	cout << endl;

}

void Apartment::print() const{
	cout << TAB << "-> Apartamento" << endl;

	Accomodation::print();

	cout<< endl << TAB << "Inclui: " << endl;
	cout << TAB << "-> " << number_bedrooms << " Quarto/s" << endl;
	if (suite) cout << TAB << "-> Suite" << endl;
	cout << TAB << "-> Cozinha" << endl;
	cout << TAB << "-> Sala de Estar" << endl;

	cout << endl;

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

	out << "-";

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
	case DOUBLE:
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
