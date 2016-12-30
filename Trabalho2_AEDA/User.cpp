#include "User.h"

User::User(string username, string password, string name) {
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

	gotoXY(48, 4); cout << "|| Reservas ||" << endl << endl << endl;


	if (reservations.size() == 0) {
		cout << TAB << "Ainda não possui reservas." << endl;
		return;
	}
	else {

		cout << "      Cliente      ID Reserva     ID Alojamento          Check IN           Check OUT      Preço      Data marcacao   " << endl;
		//cout << "         ID Reserva             ID Alojamento                Check IN             Check OUT             Preço         " << endl;
		cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;

		for (it = reservations.begin(); it != reservations.end(); it++) {
			cout << (*it);
		}
	}
}

void User::deleteReservation(int position) {
	reservations.erase(reservations.begin() + position);
}



// -------------------
//     SUPLIER
// -------------------

Suplier::Suplier(string username, string password, string name, int nif, string adress) : User(username, password, name) {
	this->nif = nif;
	this->adress = adress;

}

void askForPrice(float & p_night, float & p_week, float & p_month) {
	string line;
	
	clearScreen();

	gotoXY(48, 4); cout << "|| Mais informação ||";

	gotoXY(4, 7); cout << "-> Preçário" << endl;
	gotoXY(42, 7); cout << "Preço por noite : ";	
	getline(cin, line);
	p_night = stof(line);
	if (cin.eof()) throw InvalidInput();

	gotoXY(42, 8); cout << "Preço por semana : ";
	getline(cin, line);
	p_week = stof(line);
	if (cin.eof()) throw InvalidInput();

	gotoXY(42, 9); cout << "Preço por mês : ";
	getline(cin, line);
	p_month = stof(line);
	if (cin.eof()) throw InvalidInput();


}

void askForAvailability(vector < pair<Date, Date>>&  unavailable_dates) {
	string add;
	Date initial_date, final_date;
	string date;
	pair<Date, Date> pair_dates;

	int i = 0;

	gotoXY(4, 12); cout << "-> Disponibilidade" << endl;
	gotoXY(42, 12); cout << "(introduza o intervalo de datas em que o alojamento não estára disponível) ";
	gotoXY(42, 13); cout << "(as datas introduzidas devem estar no formato d/m/a)";


	do {
		gotoXY(42, 15);  cout << "Adicionar Data (s/n)? ";
		getline(cin, add);

		if (cin.eof()) throw InvalidInput();

		if (add == "s") {

			gotoXY(42, 16); cout << "Data Inicial : ";
			getline(cin, date);
			if (!initial_date.getDate(date)) throw InvalidDate();

			gotoXY(42, 17); cout << "Data Final   : ";
			getline(cin, date);
			if (!final_date.getDate(date)) throw InvalidDate();


			pair_dates.first = initial_date;
			pair_dates.second = final_date;

			unavailable_dates.push_back(pair_dates);

			i++;
			cout << endl;
		}
		gotoXY(42, 15); cout << "                             ";
		gotoXY(42, 16); cout << "                             ";
		gotoXY(42, 17); cout << "                             ";


	} while (add == "s");

	if (add != "n") throw InvalidInput();

}

void Suplier::addAccomodation() {
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


	cout << endl << TAB << "-> Tipo de Alojamento" << endl;
	cout << TAB << "1 - Quarto" << endl;
	cout << TAB << "2 - Flat" << endl;
	cout << TAB << "3 - Apartamento" << endl;

	cout << endl << TAB << "Opção: ";


	getline(cin, option_str);
	option_int = stoi(option_str);
	if (option_int < 1 || option_int >3) throw WrongOption(1, 3);

	switch (option_int) {
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



		switch (option_int) {
		case 1:
			bed_type = SINGLE;
			break;
		case 2:
			bed_type = DOUBLE_R;
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


		switch (option_int) {
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
		if (number_bedrooms < 1 || number_bedrooms >7) throw WrongOption(1, 7);


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
	//Company::updateDiscounts();

}


void writeBedroomType(int x) {

	switch (x)
	{
	case 7:
		cout << "   Quarto                      ";
		break;
	case 8:
		cout << "   Flat                        ";
		break;
	case 9:
		cout << "   Apartamento                 ";
		break;
	}
}

void writeBedType(int x) {

	switch (x)
	{
	case 7:
		cout << "   Quarto Simples                   ";
		break;
	case 8:
		cout << "   Quarto Duplo                     ";
		break;
	case 9:
		cout << "   Quarto Duplo com Cama Adicional  ";
		break;
	case 10:
		cout << "   Quarto Triplo                    ";
		break;
	}
}

void writeEstabliType(int x) {

	switch (x)
	{
	case 7:
		cout << "   Hotel                               ";
		break;
	case 8:
		cout << "   Casa Partilhada                     ";
		break;
	case 9:
		cout << "   Bed-n-Breakfast                     ";
		break;
	}
}


bedroomType chooseBedType() {

	clearScreen();

	int menu_item = 0, x = 7;
	bool running = true;

	gotoXY(48, 4); cout << "|| Tipo de Quarto ||";

	gotoXY(41, 7); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  " << "   Quarto Simples                   ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoXY(43, 8);  cout << "   Quarto Duplo                     ";
	gotoXY(43, 9);  cout << "   Quarto Duplo com Cama Adicional  ";
	gotoXY(43, 10);  cout << "   Quarto Triplo                    ";
	gotoXY(43, 15);

	system("pause>nul");

	while (running)
	{

		gotoXY(43, 15);

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && x != 10) //down button pressed
		{
			gotoXY(41, x); cout << "  "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); writeBedType(x);
			x++;
			gotoXY(41, x); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  "; writeBedType(x);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x != 7) //up button pressed
		{
			gotoXY(41, x); cout << "  "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); writeBedType(x);
			x--;
			gotoXY(41, x); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  "; writeBedType(x);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed

			switch (menu_item) {
			case 0:
				return SINGLE;
				break;
			case 1:
				return DOUBLE_R;
				break;
			case 2:
				return DOUBLE_EXTRA_BED;
				break;
			case 3:
				return TRIPLE;
				break;
			}
		}
	}

	gotoXY(43, 21);
}


establishment chooseEst() {

	clearScreen();

	int menu_item = 0, x = 7;
	bool running = true;

	gotoXY(48, 4); cout << "|| Tipo de Establecimento ||";

	gotoXY(41, 7); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  " << "   Hotel                               ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoXY(43, 8);  cout << "   Casa Partilhada             ";
	gotoXY(43, 9);  cout << "   Bed-n-Breakfast             ";

	gotoXY(43, 15);

	system("pause>nul");

	while (running)
	{

		gotoXY(43, 15);

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && x != 9) //down button pressed
		{
			gotoXY(41, x); cout << "  "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); writeEstabliType(x);
			x++;
			gotoXY(41, x); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  "; writeEstabliType(x);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x != 7) //up button pressed
		{
			gotoXY(41, x); cout << "  "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); writeEstabliType(x);
			x--;
			gotoXY(41, x); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  "; writeEstabliType(x);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed

			switch (menu_item) {
			case 0:
				return HOTEL;
				break;
			case 1:
				return SHARED_HOUSE;
				break;
			case 2:
				return BED_AND_BREAKFAST;
				break;
			}
		}
	}

	gotoXY(43, 21);

}

Accomodation Suplier::addAccomodation2() {
	string option_str;
	unsInt option_int;
	float p_day, p_week, p_month;
	vector <pair<Date, Date>> unavailable_dates;
	string location;
	Accomodation * acc;

	clearScreen();

	gotoXY(48, 4); cout << "|| Adicionar Alojamento ||" << endl << endl;

	gotoXY(4, 7); cout << "-> Localização" << endl;
	gotoXY(42, 7); cout << "Cidade: ";

	getline(cin, location);
	if (cin.eof()) throw InvalidInput();

	clearScreen();
	int menu_item = 0, x = 7;
	bool running = true;

	gotoXY(48, 4); cout << "|| Tipo de Alojamento ||";

	gotoXY(41, 7); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  " << "   Quarto                      ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoXY(43, 8);  cout << "   Flat                        ";
	gotoXY(43, 9);  cout << "   Apartamento                 ";

	gotoXY(43, 15);

	system("pause>nul");

	while (running)
	{

		gotoXY(43, 15);

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && x != 9) //down button pressed
		{
			gotoXY(41, x); cout << "  "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); writeBedroomType(x);
			x++;
			gotoXY(41, x); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  "; writeBedroomType(x);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x != 7) //up button pressed
		{
			gotoXY(41, x); cout << "  "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); writeBedroomType(x);
			x--;
			gotoXY(41, x); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  "; writeBedroomType(x);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed

			switch (menu_item) {
			case 0:
	
				bedroomType bed_type; bed_type = chooseBedType();
				establishment  est; est = chooseEst();

				askForPrice(p_day, p_week, p_month);

				askForAvailability(unavailable_dates);

				cout << "cheguei aqui user1";

				acc = new Bedroom(p_day, p_week, p_month, location, unavailable_dates, est, bed_type);
				cout << "cheguei aqui user2";
				running = false;
				break;

			case 1:
				askForPrice(p_day, p_week, p_month);

				askForAvailability(unavailable_dates);

				acc = new Flat(p_day, p_week, p_month, location, unavailable_dates);
				running = false;
				break;
			case 2:
				
				int number_bedrooms;
				bool suite;
				string answer;
				string nb_str;


				cout << endl << TAB << "Número de Quartos: ";
				getline(cin, nb_str);
				number_bedrooms = stoi(nb_str);
				if (number_bedrooms < 1 || number_bedrooms >7) throw WrongOption(1, 7);


				cout << endl << TAB << "Possui uma suite (s/n)? ";

				getline(cin, answer);

				if (cin.eof()) throw InvalidInput();

				if (answer == "s") suite = true;
				else if (answer == "n") suite = false;
				else throw InvalidInput();

				askForPrice(p_day, p_week, p_month);

				askForAvailability(unavailable_dates);

				acc = new Apartment(p_day, p_week, p_month, location, unavailable_dates, number_bedrooms, suite);
				
				running = false;
				break;
			}
		}
	}

	gotoXY(43, 21);

	cout << "cheguei aqui user3";

	accomodations.push_back(acc);

	cout << "cheguei aqui user4";

	return *acc;
}

void Suplier::addAccomodationFile(Accomodation * acc) {
	accomodations.push_back(acc);
}

void Suplier::showAccomodations()const {
	vector<Accomodation * >::const_iterator it;

	clearScreen(); 

	gotoXY(48, 4); cout << "|| Alojamentos ||" << endl << endl;

	if (accomodations.size() == 0) {
		cout << TAB << "Ainda não possui alojamentos registados." << endl;
		return;
	}


	for (it = accomodations.begin(); it != accomodations.end(); it++) {
		cout << endl;
		(*it)->print();
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

void Suplier::showFees()const {
	
	gotoXY(48, 4); cout << "|| Taxas de Serviço ||" << endl << endl << endl;
	cout << TAB_BIG << TAB_BIG << TAB_BIG <<  "        Quartos        Flats           Apartamentos   " << endl;
	cout << TAB_BIG << TAB_BIG << TAB_BIG <<  "      ------------------------------------------------" << endl;
	cout << TAB_BIG << TAB_BIG << TAB_BIG <<  "          5%            1%                 15%        \n\n";
	cout << TAB_BIG << TAB_BIG << TAB_BIG <<  "      ------------------------------------------------" << endl;
	cout << TAB_BIG << TAB_BIG << TAB_BIG <<  "                  ID Reserva           Taxa (euros)   " << endl;
	cout << TAB_BIG << TAB_BIG << TAB_BIG <<  "      ------------------------------------------------" << endl;


	vector<Reservation>::const_iterator itr;
	vector<Reservation> reservations_tmp = getReservations();

	for (itr = reservations_tmp.begin(); itr != reservations_tmp.end(); itr++) {
		cout << setw(56) << itr->getID() << setw(15) << itr->getFee() << endl;
	}

	cout << endl;

}


bool Suplier::operator<(const Suplier & c) const{

	return getName() < c.getName();

}

ostream &operator<<(ostream & out, const Suplier & s){
	cout << left<<  "     ";

	cout << setw(17) << s.getName()
		<< setw(20) << s.getUsername()
		<< setw(13) << s.getNIF()
		<< setw(40) << s.getAdress();

	itAccomodation it;
	vector<Accomodation*> accomodations = s.getAccomodations();

	for (it = accomodations.begin(); it != accomodations.end(); it++){
		cout << setw(4) << (*it)->getID();
	}


	cout << endl;

	return cout;
}

// -------------------
//    Client
// -------------------

Client::Client(string username, string password, string name, int points) :User(username, password, name) {
	this->points = points;

}

void Client::addReservation(Reservation res) {
	float price;

	vector<Reservation> res_vec = getReservations();

	res_vec.push_back(res);
	price = res.getTotalPrice();


	points = points + 5 * floor(price / 50);

	setReservations(res_vec);
}

void Client::save(ofstream & out) const
{
	out <<  setw(15)          << getUsername()
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

ostream &operator<<(ostream & out, const Client  & cli){

	out << setw(20) << cli.getUsername()
		<< setw(28) << cli.getPassword()
		<< setw(36) << cli.getName()
		<< setw(23) << cli.getPoints();

	return out;
}

bool Client::isInactiveClient() {

	vector<Reservation>::const_iterator it;
	vector<Reservation> reservs = getReservations();

	bool active = true;


	for(it = reservs.begin(); it != reservs.end(); it++){
	
		Date actual_date, marking_date = it->getMarking();

		struct tm newtime;
		time_t now = time(0);
		localtime_s(&newtime, &now);

		actual_date.setYear(newtime.tm_year + 1900);
		actual_date.setMonth(newtime.tm_mon + 1);
		actual_date.setDay(newtime.tm_mday);

		int marking_int = marking_date.convert_date_int();
		int aDate_int = actual_date.convert_date_int();

		if ((aDate_int - marking_int) > 365)
			active = false;
	}

	return active;
}