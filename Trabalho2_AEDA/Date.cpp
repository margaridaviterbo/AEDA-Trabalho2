#include "Date.h"


Date::Date(string dateStr) {
	istringstream idate(dateStr);
	char c_trash;

	idate >> day >> c_trash >> month >> c_trash >> year >> c_trash;
}

int Date::getDay() const {
	return day;
}

int Date::getMonth() const {
	return month;
}

int Date::getYear() const {
	return year;
}

void Date::setDay(int day) {
	this->day = day;
}

void Date::setMonth(int month) {
	this->month = month;
}

void Date::setYear(int year) {
	this->year = year;
}


bool Date::leapYear(int year) {
	bool leap_year = true;
	if (year % 4 == 0) {
		if (year % 100 == 0) {
			if (year % 400 != 0) leap_year = false;
		}
	}

	if (leap_year)
		return true;
	else
		return false;
}


// verifica se um determinado ano � bissexto ou n�o
bool Date::isLeap(int year) {
	bool leap = true;
	if (year % 4 == 0) {
		if (year % 100 == 0) {
			if (year % 400 != 0) leap = false;
		}
	}

	if (leap)
		return true;
	else
		return false;
}


// verifica se a data � v�lida
bool Date::checkDate() {
	bool result = true;
	int daysInMonths[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


	if (isLeap(year))
	{
		daysInMonths[1] = 29;
	}
	if (month < 1 || month > 12)
	{
		result = false;
	}
	else if (day < 1 || day > daysInMonths[month - 1])
	{
		result = false;
	}
	return result;

}

// verifica se a data introduzida � v�lida
bool Date::getDate(string date_str) {
	istringstream date_iss(date_str);
	char bar;


	if (!(date_iss >> day >> bar >> month >> bar >> year && checkDate()))
		return false;

	return true;
}

int Date::convert_date_int()const {

	int year_copy = year;
	int month_copy = month;

	if (month < 3) {
		year_copy--;
		month_copy += 12;
	}
	return 365 * year_copy + year / 4 - year_copy / 100 + year_copy / 400 + (153 * month_copy - 457) / 5 + day - 306;
}


ostream& operator<<(ostream& out, const Date & date) {
	if (date.day < 10)
		out << "0" << date.day << "/";
	else
		out << date.day << "/";

	if (date.month < 10)
		out << "0" << date.month << "/";
	else
		out << date.month << "/";

	out << date.year;

	return out;
}

bool operator<(const Date &d1, const Date &d2) {
	int d1_int, d2_int;
	d1_int = d1.convert_date_int();
	d2_int = d2.convert_date_int();

	return d1_int < d2_int;
}

bool operator>(const Date &d1, const Date &d2) {
	int d1_int, d2_int;
	d1_int = d1.convert_date_int();
	d2_int = d2.convert_date_int();

	return d1_int > d2_int;
}

bool operator<=(const Date &d1, const Date &d2) {
	int d1_int, d2_int;
	d1_int = d1.convert_date_int();
	d2_int = d2.convert_date_int();

	return d1_int <= d2_int;

}

bool operator>=(const Date &d1, const Date &d2) {
	int d1_int, d2_int;
	d1_int = d1.convert_date_int();
	d2_int = d2.convert_date_int();

	return d1_int >= d2_int;

}

bool operator == (const Date &d1, const Date &d2) {
	return (d1.day == d2.day && d1.month == d2.month && d1.year == d2.year);


}

int diffDays (Date d1, Date d2) {

	int year, month;
	int days1, days2;

	year = d1.getYear();
	month = d1.getMonth();
	if (d1.getMonth() < 3)
		year--, month += 12;
	days1 = 365 * year + year / 4 - year / 100 + year / 400 + (153 * month - 457) / 5 + d1.getDay() - 306;

	year = d2.getYear();
	month = d2.getMonth();
	if (d2.getMonth() < 3)
		year--, month += 12;
	days2 = 365 * year + year / 4 - year / 100 + year / 400 + (153 * month - 457) / 5 + d2.getDay() - 306;

	return abs(days1 - days2);
}


Date getCurrentDate() {
	Date current_date;

	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);

	current_date.setYear(newtime.tm_year + 1900);
	current_date.setMonth(newtime.tm_mon + 1);
	current_date.setDay(newtime.tm_mday);

	return current_date;

}


