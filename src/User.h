#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "defs.h"
#include "utils.h"
#include "Accomodation.h"
#include "Date.h"
#include "Reservation.h"


using namespace std;

class User{
private:
	string username;
	string password;
	string name;
	vector<Reservation> reservations;

public:
	User(string username, string password, string name);
	string getName() const { return name; }
	void setName(string name) { this->name = name; }
	string getPassword() const { return password; }
	void setPassword(string password) { this->password = password; }
	string getUsername() const { return username; }
	void setUsername(string username) { this->username = username; }
	
	void showReservations()const;
	vector<Reservation> getReservations() const{ return reservations; };
	void setReservations(vector<Reservation> res) { this->reservations = res; };
	void deleteReservation(int position);


	bool operator== (const User & usr) const;
};


class Suplier : public User{
private:
	int nif;
	string adress;
	vector <Accomodation*> accomodations;

public:
	Suplier(string username, string password, string name, int nif, string adress); 
	void addAccomodation();
	void addAccomodationFile(Accomodation * acc);
	void showAccomodations()const;
	vector<Accomodation*> getAccomodations() const { return accomodations; }
	void setAccomodations(vector<Accomodation*> accomodations) { this->accomodations = accomodations; }
	

	string getAdress() const { return adress; }
	void setAdress(string adress) { this->adress = adress; }
	int getNIF() const { return nif; }
	void save(ofstream & out) const;
	void addReservation(Reservation res);

	void showFees()const;
};


void askForPrice(float & p_night, float & p_week, float & p_month);
void askForAvailability(vector < pair<Date, Date>>&  unavailableDates);

class Client : public User{

	private:
		int points;

	public:
		Client(string username, string password, string name, int points = 0);
		int getPoints() const { return points; };
		void addReservation(Reservation res);

		void save(ofstream & out) const;
		//vector<Reservation*> getReservations() const;
		//void setReservations(vector<Reservation*> reservations);
		//makeReservation		//adicionar um numero de pontos ao utilizador por ter feito uma reserva (no algoritmo da pesquisa de alojamento do programa por a adicionar um numero menor de pontos por estar a pesqiusar no site


};