#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ctime>


#include "User.h"
#include "utils.h"

using namespace std;

class Company{	//implementar nesta classe as funcionalidades gerais do programa, os metodos para gerir a empresa
private:
	vector<Suplier> supliers; // precisa de ser pointer??????
	vector<Client> clients;
	vector <Reservation> reservations;

	string clientsFile;
	string supliersFile;
	string reservationsFile;
	
public:
	Company(string clientsFile, string supliersFile, string reservationsFile);
	Company() {};

	void supliersInicialization(string supliersFile);
	void reservationsInicialization(string reservationsFile);
	void clientsInicialization(string clientsFile);

	void registerSuplier();  // regista um fornecedor
	void registerClient();   // regista um cliente
	vector<Suplier>::iterator verifyLogInSup(string username, string password);     // verifica se os dados de acesso á conta fornecedor estão corretos
	vector<Client>::iterator verifyLogInCli(string username, string password);		// não pode ser const porque o iterator deve permitir alterações do valor
	Accomodation* displayOffers(string location,Date initial_date,Date final_Date);

	void addReservationComp(Accomodation *a, Date init_date, Date final_date);
	int cancelReservation();  //retorna o id da reserva a cancelar
	void showReservation()const;

	void saveChanges() const;
	void saveClientsChanges() const;
	void saveSupliersChanges() const;
	void saveReservationsChanges() const;
};