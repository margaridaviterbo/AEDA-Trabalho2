#pragma once
#pragma warning(disable : 4996)

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <ctime>

#include "Date.h"

using namespace std;

enum establishment { HOTEL, BED_AND_BREAKFAST, SHARED_HOUSE };	//edificios onde podem estar os Bedroom
enum bedroomType { SINGLE, DOUBLE_R, DOUBLE_EXTRA_BED, TRIPLE };	//tipos de quarto

class Accomodation {
private:
	time_t creationDateTime;
	float price_night;
	float price_week;
	float price_month;
	string location;
	unsigned int id;
	static unsigned int lastID;
	int lastReservationID=0;
	vector<pair<Date, Date>> unavailable_dates;
	float fee;

public:

	/**
	* @brief  accomodation constructor
	*
	* @param price_night
	*
	* @param price_week
	*
	* @param price_month
	*
	* @param location
	*
	* @param unavailable_dates
	*
	*/
	Accomodation(float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> available_dates);

	/**
	* @brief  accomodation constructor with id
	*
	* @param id
	*
	* @param price_night
	*
	* @param price_week
	*
	* @param price_month
	*
	* @param location
	*
	* @param unavailable_dates
	*
	*/
	Accomodation(unsigned int id, float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> available_dates, time_t creation_time);
	Accomodation() {};

	/**
	* @brief  gets price_night
	*
	* @return price_night
	*/
	float getPriceNight()const { return price_night; };

	/**
	* @brief  gets price_week
	*
	* @return price_week
	*/
	float getPriceWeek()const { return price_week; };

	/**
	* @brief  gets price_month
	*
	* @return price_month
	*/
	float getPriceMonth()const { return price_month; };

	/**
	* @brief  gets location
	*
	* @return location
	*/
	string getLocation()const { return location; };

	/**
	* @brief  gets ID
	*
	* @return ID
	*/
	unsigned int getID()const { return id; };

	/**
	* @brief sets ID
	*
	* @param id
	*/
	void setID(unsigned int id) { this->id = id; };

	/**
	* @brief virtual fuction to save accomodation on the supliers file
	*
	* @param out file supliers
	*/
	virtual void saveAccomodation(ofstream & out);

	/**
	* @brief gets lastID
	*
	* @return lastID
	*/
	static unsigned int getLastID() { return lastID; }

	/**
	* @brief gets fee
	*
	* @return fee that supliers pay for each reservations
	*/
	float getFee() { return fee; }

	/**
	* @brief sets fee
	*
	* @param fee
	*/
	void setFee(float fee) { this->fee = fee; }

	/**
	* @brief adds dates to the vector of unavailable dates
	*
	* @param dates pair of dates(initial and final)
	*/
	void addDates(const pair<Date, Date> &dates);

	/**
	* @brief removes dates to the vector of unavailable dates
	*
	* @param checkIN
	*
	* @param checkOUT
	*
	*/
	void removeDates(Date checkIN, Date checkOUT);

	/**
	* @brief gets unavailable dates
	*
	* @return unavailable dates
	*/
	vector<pair<Date, Date>> getUnavailableDates()const { return unavailable_dates; };

	/**
	* @brief virtual fuction to print a accomodation on the screen
	*
	*/
	virtual void print() const;

	/**
	* @brief sets accomomodation last id
	*
	* @param id
	*
	*/
	static void setAccLastID(unsigned int id);
	void setLastReservationID(int id) { lastReservationID = id; }

	/**
	* @brief overload of the the equality operator
	*
	* @param acc
	*
	* @return true is accomodations have the same id, false otherwise
	*/
	bool operator == (const Accomodation &acc) const;
	bool operator < (const Accomodation &acc) const;
};

class Bedroom : public Accomodation {
private:
	establishment  est;
	bedroomType bed_type;

public:
	/**
	* @brief  bedroom constructor
	*
	* @param price_night
	*
	* @param price_week
	*
	* @param price_month
	*
	* @param location
	*
	* @param unavailable_dates
	*
	* @param est type of establishment
	*
	* @param bed_type type of bedroom
	*
	*/
	Bedroom(float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unvailableDates, establishment  est, bedroomType bed_type);

	/**
	* @brief  bedroom constructor with id
	*
	* @param id
	*
	* @param price_night
	*
	* @param price_week
	*
	* @param price_month
	*
	* @param location
	*
	* @param unavailable_dates
	*
	* @param est type of establishment
	*
	* @param bed_type type of bedroom
	*
	*/
	Bedroom(unsigned int id, float price_night, float price_month, float price_year, string location, vector<pair<Date, Date>> unavailableDates, time_t creation_time, establishment  est, bedroomType bed_type);

	/**
	* @brief prints bedroom on the sreen
	*
	*/
	virtual void print() const;

	/**
	* @brief saves bedroom in supliers file
	*
	* @param out supliers file
	*/
	virtual void saveAccomodation(ofstream & out);
};


class Flat : public Accomodation {
public:
	/**
	* @brief flat constructor
	*
	* @param price_night
	*
	* @param price_week
	*
	* @param price_month
	*
	* @param location
	*
	* @param unavailable_dates
	*
	*/
	Flat(float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailableDates) : Accomodation(price_night, price_week, price_month, location, unavailableDates) { setFee(0.1); };

	/**
	* @brief flat constructor with id
	*
	* @param id
	*
	* @param price_night
	*
	* @param price_week
	*
	* @param price_month
	*
	* @param location
	*
	* @param unavailable_dates
	*
	*/
	Flat(unsigned int id, float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailableDates, time_t creation_time) : Accomodation(id, price_night, price_week, price_month, location, unavailableDates, creation_time) { setFee(0.1); };

	/**
	* @brief prints flat on the sreen
	*
	*/
	virtual void print() const;

	/**
	* @brief saves flat in supliers file
	*
	* @param out supliers file
	*/
	virtual void saveAccomodation(ofstream & out);
};

class Apartment : public Accomodation {
private:
	int number_bedrooms;
	bool suite;

public:
	/**
	* @brief apartment constructor
	*
	* @param price_night
	*
	* @param price_week
	*
	* @param price_month
	*
	* @param location
	*
	* @param unavailable_dates
	*
	*/
	Apartment(float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailable_dates, int n_bed, bool suite);

	/**
	* @brief apartment constructor with id
	*
	* @param id
	*
	* @param price_night
	*
	* @param price_week
	*
	* @param price_month
	*
	* @param location
	*
	* @param unavailable_dates
	*
	*/
	Apartment(unsigned int id, float price_night, float price_week, float price_month, string location, vector<pair<Date, Date>> unavailable_dates, time_t creation_time, int n_bed, bool suite);

	/**
	* @brief prints apartment on the sreen
	*
	*/
	virtual void print() const;

	/**
	* @brief saves apartment in supliers file
	*
	* @param out supliers file
	*/
	virtual void saveAccomodation(ofstream & out);
};

