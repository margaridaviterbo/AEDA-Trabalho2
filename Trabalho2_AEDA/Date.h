#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "defs.h"
#include "utils.h"

using namespace std;


class Date {
private:
	int day;
	int month;
	int year;

public:
	
	/**
	* @brief default date constructor
	*
	*/
	Date() {};

	/**
	* @brief date constructor
	*
	* @param date in DD/MM/YYYY format
	*
	*/
	Date(string date); // data na forma DD/MM/AAA

	/**
    * @brief gets day
	*
	* @return day
	*
	*/
	int getDay() const;


	/**
	* @brief gets month
	*
	* @return month
	*
	*/
	int getMonth() const;

	/**
	* @brief gets year
	*
	* @return year
	*
	*/
	int getYear() const;

	/**
	* @brief sets day
	*
	* @param day
	*
	*/
	void setDay(int day);

	/**
	* @brief sets month
	*
	* @param mont
	*
	*/
	void setMonth(int month);

	/**
	* @brief sets year
	*
	* @param year
	*
	*/
	void setYear(int year);

	/**
	* @brief converts date into an integer
	*
	* @return integer corresponding to date
	*
	*/
	int convert_date_int()const;

	/**
	* @brief checks if year is leap
	*
	* @param year
	*
	* @return true if leap, false otherwise
	*
	*/
	bool leapYear(int year);
	/**
	* @brief checks if year is leap
	*
	* @param year
	*
	* @return true if leap, false otherwise
	*
	*/
	bool isLeap(int year);

	/**
	* @brief checks if date is valid
	*
	* @return true if valid, false otherwise
	*
	*/
	bool checkDate();

	/**
	* @brief checks if date is valid and correctly extracted
	*
	* @param date_str
	*
	* @return true if valid, false otherwise
	*
	*/
	bool getDate(string date_str);

	/**
	* @brief checks if d1 is higher or equal to d2
	*
	* @param d1
	*
	* @param d2
	*
	* @return true if d1 is higher or equal to d2, false otherwise
	*
	*/
	friend bool operator>=(const Date &d1, const Date &d2);

	/**
	* @brief checks if d1 is less or equal to d2
	*
	* @param d1
	*
	* @param d2
	*
	* @return true if d1 is less or equal to d2, false otherwise
	*
	*/
	friend bool operator<=(const Date &d1, const Date &d2);

	/**
	* @brief checks if d1 is less than d2
	*
	* @param d1
	*
	* @param d2
	*
	* @return true if d1 is less than d2, false otherwise
	*
	*/
	friend bool operator<(const Date &d1, const Date &d2);
	/**
	* @brief checks if d1 is higher than d2
	*
	* @param d1
	*
	* @param d2
	*
	* @return true if d1 is higher than d2, false otherwise
	*
	*/
	friend bool operator>(const Date &d1, const Date &d2);

	/**
	* @brief checks if d1 is equal to d2
	*
	* @param d1
	*
	* @param d2
	*
	* @return true if d1 is equal to d2, false otherwise
	*
	*/
	friend bool operator == (const Date &d1, const Date &d2);

	/**
	* @brief displays date
	*
	* @param out
	*
	* @param date
	*
	* @return out
	*
	*/

	friend ostream& operator<<(ostream& out, const Date & date);
};


int diffDays(Date d1, Date d2);

Date getCurrentDate();

