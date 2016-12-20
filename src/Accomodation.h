#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "Date.h"

using namespace std;

enum establishment { HOTEL, BED_AND_BREAKFAST, SHARED_HOUSE };	//edificios onde podem estar os Bedroom
enum bedroomType { SINGLE, DOUBLE, DOUBLE_EXTRA_BED, TRIPLE };	//tipos de quarto

class Accomodation {
private:
	float price_night;
	float price_week;
	float price_month;
	string location;
	unsigned int id;
	static unsigned int lastID;
	vector<pair<Date, Date>> unavailable_dates;
	float fee;

public:
	Accomodation(float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> available_dates);
	Accomodation(unsigned int id, float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> available_dates);
	Accomodation() {};

	float getPriceNight()const { return price_night; };
	float getPriceWeek()const { return price_week; };
	float getPriceMonth()const { return price_month; };
	string getLocation()const { return location; };
	unsigned int getID()const { return id; };
	void setID(unsigned int id){ this->id = id; };
	virtual void saveAccomodation(ofstream & out);
	static unsigned int getLastID() { return lastID; }
	float getFee(){ return fee; }
	void setFee(float fee){ this->fee = fee; }

	void addDates(const pair<Date, Date> &dates);
	void removeDates(Date checkIN, Date checkOUT);

	vector<pair<Date, Date>> getUnavailableDates()const { return unavailable_dates; };

	virtual void print() const;
	static void setAccLastID(unsigned int id);
	bool operator == (const Accomodation &acc) const;
};

class Bedroom : public Accomodation{
private:
	establishment  est;
	bedroomType bed_type;
	
public:
	Bedroom(float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unvailableDates, establishment  est, bedroomType bed_type);
	Bedroom(unsigned int id, float price_night, float price_month, float price_year, string location, vector<pair<Date, Date>> unavailableDates, establishment  est, bedroomType bed_type);
	virtual void print() const;
	virtual void saveAccomodation(ofstream & out);
};


class Flat : public Accomodation {
public:
	Flat(float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailableDates) : Accomodation(price_night, price_week, price_month, location, unavailableDates) { setFee(0.1); };
	Flat(unsigned int id, float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailableDates) : Accomodation(id, price_night, price_week, price_month, location, unavailableDates) { setFee(0.1); };
	virtual void print() const;
	virtual void saveAccomodation(ofstream & out);
};

class Apartment : public Accomodation {
private:
	int number_bedrooms;
	bool suite;

public:
	Apartment(float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailable_dates, int n_bed, bool suite);
	Apartment(unsigned int id, float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailable_dates, int n_bed, bool suite);
	virtual void print() const;
	virtual void saveAccomodation(ofstream & out);
};

