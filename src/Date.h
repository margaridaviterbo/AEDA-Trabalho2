#pragma once

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
	Date() {};
	Date(string date); // data na forma DD/MM/AAA

	int getDay() const;
	int getMonth() const;
	int getYear() const;

	void setDay(int day);
	void setMonth(int month);
	void setYear(int year);

	int convert_date_int()const;
	bool leapYear(int year);
	bool isLeap(int year);
	bool checkDate();
	bool getDate(string date_str);

	friend bool operator>=(const Date &d1, const Date &d2);
	friend bool operator<=(const Date &d1, const Date &d2);
	friend bool operator<(const Date &d1, const Date &d2);
	friend bool operator>(const Date &d1, const Date &d2);
	friend bool operator == (const Date &d1, const Date &d2);
	friend ostream& operator<<(ostream& out, const Date & date);
};

