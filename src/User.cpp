#include "User.h"

User::User(string username, string password, string name){
	this->username = username;
	this->password = password;
	this->name = name;

}

bool User::operator== (const User & usr) const {
	return username == usr.username;
}

void User::showReservations()const {
	vector<Reservation>::const_iterator it;

	clearScreen();

	if (reservations.size() == 0) {
		cout << TAB << "Ainda não possui reservas." << endl;
		return;
	}

	cout << TAB_BIG << "|| Reservas ||" << endl;

	for (it = reservations.begin(); it != reservations.end(); it++) {
		cout << endl;
		cout << (*it);
		cout << TAB << "-------------------------------------------------" << endl;
	}
}

void User::deleteReservation(int position) {
	reservations.erase(reservations.begin() + position);
}



// -------------------
//     SUPLIER
// -------------------

Suplier::Suplier(string username, string password, string name, int nif, string adress) : User(username, password, name){
	this->nif = nif;
	this->adress = adress;

}

void askForPrice(float & p_night,float & p_week, float & p_month){
	string line;
	cout << endl << TAB << "-> Preçário" << endl;
	
	cout << TAB << "Preço por noite: ";
	getline(cin,line);
	p_night = stof(line);
	if (cin.eof()) throw InvalidInput();

	cout << TAB << "Preço por semana: ";
	getline(cin, line);
	p_week = stof(line);
	if (cin.eof()) throw InvalidInput();

	cout << TAB << "Preço por mês: ";
	getline(cin, line);
	p_month= stof(line);
	if (cin.eof()) throw InvalidInput();


}

void askForAvailability(vector < pair<Date, Date>>&  unavailable_dates) {
	string add;
	Date initial_date, final_date;
	string date;
	pair<Date, Date> pair_dates;

	int i = 0;

	cout << endl << TAB << "-> Disponibilidade" << endl;
	cout << TAB << "(introduza o intervalo de datas em que o alojamento não estára disponível) " << endl;
	cout << TAB << "(as datas introduzidas devem estar no formato d/m/a)" << endl << endl;

	do {
		cout << TAB << "Adicionar Data (s/n)? ";
		getline(cin, add);

		if (cin.eof()) throw InvalidInput();

		if (add == "s") {

			cout << TAB << "Data Inicial : ";
			getline(cin, date);
			if (!initial_date.getDate(date)) throw InvalidDate();

			cout << TAB << "Data Final : ";
			getline(cin, date);
			if (!final_date.getDate(date)) throw InvalidDate();

			
			pair_dates.first = initial_date;
			pair_dates.second = final_date;

			unavailable_dates.push_back(pair_dates);

			i++;
			cout << endl;


		}

	} while (add == "s");

	if (add != "n") throw InvalidInput();

}

void Suplier::addAccomodation(){
	string option_str;
	unsInt option_int;
	float p_day, p_week, p_month;
	vector <pair<Date, Date>> unavailable_dates;
	string location;
	Accomodation * acc;

	clearScreen();

	cout << TAB_BIG << " || Adicionar Alojamento ||" << endl << endl;

	cout << TAB << "-> Local: ";

	getline(cin, location);
	if (cin.eof()) throw InvalidInput();


	cout << endl <<  TAB << "-> Tipo de Alojamento" << endl;
	cout << TAB << "1 - Quarto" << endl;
	cout << TAB << "2 - Flat" << endl;
	cout << TAB << "3 - Apartamento" << endl;

	cout << endl << TAB << "Opção: ";


	getline(cin, option_str);
	option_int = stoi(option_str);
	if (option_int < 1 || option_int >3) throw WrongOption(1, 3);

	switch (option_int){
	case 1:

		establishment  est;
		bedroomType bed_type;

		cout << endl << TAB << "-> Tipo de Quarto" << endl;
		cout << TAB << "1 - Quarto Simples" << endl;
		cout << TAB << "2 - Quarto Duplo" << endl;
		cout << TAB << "3 - Quarto Duplo com Cama Adicional" << endl;
		cout << TAB << "4 - Quarto Triplo" << endl;

		cout << endl << TAB << "Opção: ";

		getline(cin, option_str);
		option_int = fromString<int>(option_str);
		if (option_int < 1 || option_int >4) throw WrongOption(1, 4);

		

		switch (option_int){
		case 1:
			bed_type = SINGLE;
			break;
		case 2:
			bed_type = DOUBLE;
			break;
		case 3:
			bed_type = DOUBLE_EXTRA_BED;
			break;
		case 4:
			bed_type = TRIPLE;
			break;
		}

		cout << endl << TAB << "-> Tipo de Estabelecimento" << endl;
		cout << TAB << "1 - Hotel" << endl;
		cout << TAB << "2 - Casa Partilhada" << endl;
		cout << TAB << "3 - Bed-n-Breakfast" << endl;

		cout << endl << TAB << "Opção: ";
		
		getline(cin, option_str);
		option_int = stoi(option_str);
		if (option_int < 1 || option_int >3) throw WrongOption(1, 3);


		switch (option_int){
		case 1:
			est = HOTEL;
			break;
		case 2:
			est = SHARED_HOUSE;
			break;
		case 3:
			est = BED_AND_BREAKFAST;
			break;
		}


		askForPrice(p_day, p_week, p_month);

		askForAvailability(unavailable_dates);

		acc = new Bedroom(p_day, p_week, p_month, location, unavailable_dates, est, bed_type);
		break;
	case 2:
		askForPrice(p_day, p_week, p_month);

		askForAvailability(unavailable_dates);
		
		acc = new Flat(p_day, p_week, p_month, location, unavailable_dates);
		break;
	case 3:

		int number_bedrooms;
		bool suite;
		string answer;
		string nb_str;
		

		cout << endl << TAB << "Número de Quartos: ";
		getline(cin, nb_str);
		number_bedrooms = stoi(nb_str);
		if (number_bedrooms < 1 ||number_bedrooms >7) throw WrongOption(1, 7);


		cout << endl << TAB << "Possui uma suite (s/n)? ";

		getline(cin, answer);

		if (cin.eof()) throw InvalidInput();

		if (answer == "s") suite = true;
		else if (answer == "n") suite = false;
		else throw InvalidInput();

		askForPrice(p_day, p_week, p_month);

		askForAvailability(unavailable_dates);

		acc = new Apartment(p_day, p_week, p_month, location, unavailable_dates, number_bedrooms, suite);
		break;

	}

	accomodations.push_back(acc);

}

void Suplier::addAccomodationFile(Accomodation * acc) {
	accomodations.push_back(acc);
}

void Suplier::showAccomodations()const {
	vector<Accomodation * >::const_iterator it;

	clearScreen();

	if (accomodations.size() == 0) {
		cout << TAB << "Ainda não possui alojamentos registados." << endl;
		return;
	}

	cout << endl << TAB_BIG << "|| Alojamentos ||" << endl;

	for (it = accomodations.begin(); it != accomodations.end(); it++) {
		cout << endl;
		(*it)->print();
		cout << TAB <<  "-------------------------------------------------" << endl;
	}

}

void Suplier::addReservation(Reservation res) {
	vector<Reservation> res_vec = getReservations();
	res_vec.push_back(res);
	setReservations(res_vec);
}


void Suplier::save(ofstream & out) const
{
	out << setw(15) << getUsername() << setw(15) << getPassword() << setw(18) << getName() << setw(15) << nif << "        - " << adress << " - " << endl;

	vector<Accomodation *> acc = getAccomodations();

	vector<Accomodation *>::const_iterator it;

	for (it = acc.begin(); it != acc.end(); it++)
	{
		(*it)->saveAccomodation(out);
	}

	out << "-------" << endl;

}

void Suplier::showFees()const{
	cout << TAB_BIG << "|| Taxas de Serviço ||" << endl << endl;
	cout << TAB << "Quartos: 5%" << endl;
	cout << TAB << "Flats: 1 %" << endl;
	cout << TAB << "Apartamentos: 15%" << endl << endl;

	vector<Reservation>::const_iterator itr;
	vector<Reservation> reservations_tmp = getReservations();

	for (itr = reservations_tmp.begin(); itr != reservations_tmp.end(); itr++){
		cout << TAB << "Reserva " << itr->getID() << ": " << itr->getFee() << " euros"<< endl;
	}

	cout << endl;

}


// -------------------
//    Client
// -------------------

Client::Client(string username, string password, string name,int points):User(username, password, name) {
	this->points = points;

}

void Client::addReservation(Reservation res) {
	float price;

	vector<Reservation> res_vec = getReservations();

	res_vec.push_back(res);
	price = res.getTotalPrice();


	points = points + 5*floor(price / 50);

	setReservations(res_vec);
}


void Client::save(ofstream & out) const
{
	out << setw(14) << getUsername()
		<< setw(14) << getPassword()
		<< setw(20) << getName()
		<< setw(8) << getPoints();

	vector<Reservation>::const_iterator it;

	vector<Reservation> reserv = getReservations();

	for (it = reserv.begin(); it != reserv.end(); it++)
	{
		out << setw(5) << it->getID();
	}

	out << endl;
}
