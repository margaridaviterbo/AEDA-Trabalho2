#include "Company.h"

void Company::supliersInicialization(string supliersFile)
{
	ifstream name_supliers;
	string line_f;
	unsigned int maxID;

	name_supliers.open(supliersFile);

	if (!name_supliers.is_open()) throw ErrorOpeningFile("Fornecedores");

	getline(name_supliers, line_f);
	stringstream ss; ss.str(line_f);

	ss >> maxID;

	Accomodation::setAccLastID(maxID);

	while (getline(name_supliers, line_f))
	{
		string username, password, name, surname, adress, trash, nif;
		unsigned int NIF;
		stringstream ss; ss.str(line_f);

		ss >> username;
		ss >> password;
		ss >> name;
		ss >> surname; name = name + ' ' + surname;
		ss >> nif; NIF = fromString<unsigned int>(nif);
		ss >> trash; getline(ss, adress, '-'); trim(adress);

		Suplier sup(username, password, name, NIF, adress);

		while (getline(name_supliers, line_f) && line_f != "-------")
		{

			stringstream ss; ss.str(line_f);
			string type, d, w, m, city, date1, date2, next;
			float daily, weekly, monthly;
			pair<Date, Date> pair_dates;
			vector<pair<Date, Date>> unavailableDates;
			unsigned int ID;


			ss >> ID;
			ss >> type;
			ss >> d; daily = stof(d);
			ss >> w; weekly = stof(w);
			ss >> m; monthly = stof(m);
			getline(ss, city, '-');

			normalize(city);

			ss >> date1;

			while (date1 != "-")
			{
				Date d1(date1); pair_dates.first = d1;
				ss >> date2; Date d2(date2); pair_dates.second = d2;
				unavailableDates.push_back(pair_dates);
				ss >> date1;

			}

			if (type == "BEDROOM")
			{

				string bedroomType2, est;
				bedroomType bedType;

				ss >> bedroomType2;

				if (bedroomType2 == "SINGLE")
				{
					bedType = SINGLE;
				}
				if (bedroomType2 == "DOUBLE")
				{
					bedType = DOUBLE_R;
				}
				if (bedroomType2 == "DOUBLE_EXTRA_BED")
				{
					bedType = DOUBLE_EXTRA_BED;
				}
				if (bedroomType2 == "TRIPLE")
				{
					bedType = TRIPLE;
				}



				ss >> est;
				establishment estbl;

				if (est == "HOTEL")
				{
					estbl = HOTEL;
				}
				if (est == "BED_AND_BREAKFAST")
				{
					estbl = BED_AND_BREAKFAST;
				}
				if (est == "SHARED_HOUSE")
				{
					estbl = SHARED_HOUSE;
				}

				Bedroom *bed = new Bedroom(ID, daily, weekly, monthly, city, unavailableDates, estbl, bedType);

				sup.addAccomodationFile(bed);
			}

			if (type == "APARTMENT")
			{
				string suite_str, nRooms;
				int numRooms;
				bool suite = true;


				ss >> nRooms; numRooms = stoi(nRooms);
				ss >> suite_str;

				if (suite_str != "SIM")
					suite = false;

				Apartment *apart = new Apartment(ID, daily, weekly, monthly, city, unavailableDates, numRooms, suite);

				sup.addAccomodationFile(apart);
			}


			if (type == "FLAT")
			{

				Flat *flt = new Flat(ID, daily, weekly, monthly, city, unavailableDates);

				sup.addAccomodationFile(flt);
			}

		}
		supliers.push_back(sup);
	}

	name_supliers.close();

}

void Company::reservationsInicialization(string reservationsFile)
{
	ifstream name_reservations;
	string line_r;
	unsigned int maxID;

	name_reservations.open(reservationsFile);

	getline(name_reservations, line_r);
	stringstream ss; ss.str(line_r);

	ss >> maxID;

	Reservation::setResLastID(maxID);

	while (getline(name_reservations, line_r))
	{
		string name, surname, checkIN, checkOUT, idr, ida, mark;
		unsigned int IDreservation, IDaccomodation;
		stringstream ss; ss.str(line_r);
		Accomodation *accom = new Accomodation();


		ss >> name;
		ss >> surname; name = name + ' ' + surname;
		ss >> idr; IDreservation = fromString<unsigned int>(idr);
		ss >> ida; IDaccomodation = fromString<unsigned int>(ida);
		ss >> checkIN; Date in(checkIN);
		ss >> checkOUT; Date out(checkOUT);
		ss >> mark; Date markg(mark);
		accom->setID(IDreservation);

		Accomodation *accomodation = new Accomodation();
		vector<Suplier>::iterator it;

		for (it = supliers.begin(); it != supliers.end(); it++)
		{
			vector<Accomodation *> acc; acc = it->getAccomodations();
			vector<Accomodation *>::iterator it2;

			for (it2 = acc.begin(); it2 != acc.end(); it2++)
			{
				if ((*it2)->getID() == IDaccomodation)
				{
					accomodation = *it2;
					Reservation reserv(IDreservation, accomodation, in, out, markg, name);
					reservations.push_back(reserv);
					it->addReservation(reserv);

					break;

				}
			}
		}
	}

	name_reservations.close();
}

void Company::clientsInicialization(string clientsFile)
{
	ifstream name_clients;
	string line_c;

	name_clients.open(clientsFile);

	while (getline(name_clients, line_c))
	{
		string ID, password, name, surname, pts, IDreservation;
		unsigned int idr;
		stringstream ss; ss.str(line_c);

		ss >> ID;
		ss >> password;
		ss >> name;
		ss >> surname; name = name + ' ' + surname;
		ss >> pts;

		Client client(ID, password, name);

		bool activeClient = true;

		while (ss >> IDreservation)
		{
			idr = fromString<unsigned int>(IDreservation);

			for (unsigned int i = 0; i < reservations.size(); i++)
			{
				if (reservations[i].getID() == idr) {
					client.addReservation(reservations[i]);
				}
			}
		}

		if (client.isInactiveClient()) {
			clients.push_back(client);
		}
		else {
			pair<unordered_set<Client, hcli, eqcli>::iterator, bool> res = inactiveClients.insert(client);
		}
	}

	name_clients.close();

}


Company::Company(string clientsFile, string supliersFile, string reservationsFile) {

	this->clientsFile = clientsFile;
	this->supliersFile = supliersFile;
	this->reservationsFile = reservationsFile;

	/*
	Ficheiro de fornecedores
	*/

	supliersInicialization(supliersFile);


	/*
	FICHEIRO DE RESERVAS
	*/

	reservationsInicialization(reservationsFile);

	/*
	FICHEIRO DE CLIENTES
	*/

	clientsInicialization(clientsFile);

}

void Company::saveClientsChanges() const
{
	ofstream fout;
	fout.open(clientsFile);

	if (fout.fail()) throw ErrorOpeningFile("Clientes");

	for (unsigned int i = 0; i < clients.size(); i++)
	{
		clients[i].save(fout);
	}
	
	unordered_set<Client, hcli, eqcli>::iterator it = inactiveClients.begin();

	while (it != inactiveClients.end()) {
		
		(*it).save(fout);
		it++;
	}
	

	fout.close();
}

void Company::saveSupliersChanges() const
{
	ofstream fout;

	fout.open(supliersFile);

	if (fout.fail()) throw ErrorOpeningFile("fornecedores para output");

	fout << setw(5) << Accomodation::getLastID() << endl;

	for (unsigned int i = 0; i < supliers.size(); i++)
	{
		supliers[i].save(fout);
	}

	fout.close();
}

void Company::saveReservationsChanges() const
{
	ofstream fout;
	fout.open(reservationsFile);

	if (fout.fail()) throw ErrorOpeningFile("Reservas");

	fout << setw(5) << Reservation::getLastID() << endl;

	for (unsigned int i = 0; i < reservations.size(); i++)
	{
		reservations[i].save(fout);
	}

	fout.close();
}


void Company::saveChanges() const
{
	saveClientsChanges();
	saveReservationsChanges();
	saveSupliersChanges();
}

// -------------------
//     Suplier
// -------------------

vector<Suplier>::iterator Company::verifyLogInSup(string username, string password) {
	string un;
	string pw;

	vector<Suplier>::iterator it;

	for (it = supliers.begin(); it != supliers.end(); it++) {
		un = (*it).getUsername();
		pw = (*it).getPassword();

		if ((un == username) && (pw == password)) return it;
	}

	throw InvalidLogIn();
}

void Company::registerSuplier() {
	string name;
	string NIF_str;
	unsigned long NIF;
	string adress;
	string username;
	string password = "";
	string add;
	char ch;

	clearScreen();

	gotoXY(48, 4); cout << "|| Registar ||" << endl << endl;

	gotoXY(4, 7); cout << "-> Dados Pessoais" << endl;
	gotoXY(42, 7); cout << "Nome: ";
	getline(cin, name);
	if (cin.eof()) throw InvalidInput();

	gotoXY(42, 8); cout << "NIF: ";
	getline(cin, NIF_str);


	if (cin.eof()) throw InvalidInput();

	NIF = stoul(NIF_str);


	gotoXY(42, 9); cout << "Morada: ";
	getline(cin, adress);
	if (cin.eof()) throw InvalidInput();

	gotoXY(4, 11); cout << "-> Credenciais de Acesso" << endl;
	gotoXY(42, 11); cout << "Nome de Utilizador: ";
	getline(cin, username);
	if (cin.eof()) throw InvalidInput();

	gotoXY(42, 12); cout << "Palavra-Passe: ";
	

	ch = _getch();
	while (ch != 13) {//character 13 is enter
		password.push_back(ch);
		cout << '*';
		ch = _getch();
	}

	if (cin.eof()) throw InvalidInput();

	Suplier s(username, password, name, NIF, adress);

	if (sequentialSearch(supliers, s) != -1) throw InvalidUsername();

	do {
		clearScreen();
		gotoXY(48, 4); cout << "|| Registar ||" << endl << endl;
		gotoXY(42, 13); cout <<  "Adicionar Alojamento (s/n)? ";
		getline(cin, add);

		if (cin.eof()) throw InvalidInput();

		if (add == "s") s.addAccomodation2();

	} while (add == "s");

	if (add != "n") throw InvalidInput();

	clearScreen();

	supliers.push_back(s);

	gotoXY(48, 4); cout << "|| Registar ||" << endl << endl;

	gotoXY(35, 7); cout << s.getName() << ", a sua conta foi criada com sucesso!" << endl;


}


void Company::showSupliers(){
	sort(supliers.begin(), supliers.end());


	gotoXY(48, 4); cout << "|| Fornecedores ||" << endl << endl << endl;

	cout << "     Nome             Nome de Utilizador  NIF          Morada                                  Alojamentos             " << endl;
	cout << " --------------------------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < supliers.size(); i++){
		cout << supliers.at(i);

	}

	pauseScreen();



}
// -------------------
//     Client
// -------------------

bool Company::isClientInactive(string username) {

	bool inactive = false;

	unordered_set<Client, hcli, eqcli>::const_iterator it = inactiveClients.begin();

	while (it != inactiveClients.end()) {

		if (username == it->getUsername())
			inactive = true;

		it++;
	}

	return inactive;

}

unordered_set<Client, hcli, eqcli>::iterator Company::verifyInactiveCliLogin(string username, string password) {

	string un;
	string pw;

	unordered_set<Client, hcli, eqcli>::iterator it = inactiveClients.begin();

	while (it != inactiveClients.end()) {

		un = (*it).getUsername();
		pw = (*it).getPassword();

		if ((un == username) && (pw == password)) return it;

		it++;
	}

	throw InvalidLogIn();

}


vector<Client>::iterator Company::verifyLogInCli(string username, string password) {
	string un;
	string pw;

	vector<Client>::iterator it;

	for (it = clients.begin(); it != clients.end(); it++) {
		un = (*it).getUsername();
		pw = (*it).getPassword();

		if ((un == username) && (pw == password)) return it;
	}

	throw InvalidLogIn();
}

void Company::registerClient() {
	string name;
	string username;
	string password = "";
	char ch;

	clearScreen();

	
	gotoXY(48, 4);  cout << "|| Registar ||" << endl << endl;
	gotoXY(42, 7);  cout << "Nome: ";
	getline(cin, name);
	if (cin.eof()) throw InvalidInput();


	gotoXY(42, 8); cout << "Nome de Utilizador: ";
	getline(cin, username);
	if (cin.eof()) throw InvalidInput();



	gotoXY(42, 9); cout << "Palavra-Passe: ";
	
	ch = _getch();
	while (ch != 13) {//character 13 is enter
		password.push_back(ch);
		cout << '*';
		ch = _getch();
	}

	if (cin.eof()) throw InvalidInput();


	Client client(username, password, name);
	if (sequentialSearch(clients, client) != -1) throw InvalidUsername();

	clearScreen();

	clients.push_back(client);
	gotoXY(48, 4);  cout << "|| Registar ||" << endl << endl;
	gotoXY(40, 9); cout << client.getName() << ", a sua conta foi criada com sucesso!";

	gotoXY(43, 15);
}

unordered_set<Client, hcli, eqcli>::iterator Company::replaceHashClient(unordered_set<Client, hcli, eqcli>::iterator ith, int pos) {

	Client cli = *ith;
	cli.deleteReservation(pos);

	inactiveClients.erase(ith);

	inactiveClients.insert(cli);

	for (ith = inactiveClients.begin(); ith != inactiveClients.end(); ith++) {
	
		if (cli.getUsername() == ith->getUsername())
			return ith;
	}
}


void Company::addReservationComp(Accomodation *a, Date init_date, Date final_date, string client) {

	Date d; // DANIEL apagar isto e calcular a Data atual!!!!!!
	
	// Data atual

	/*
	Date actual_date;

	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);

	actual_date.setYear(newtime.tm_year + 1900);
	actual_date.setMonth(newtime.tm_mon + 1);
	actual_date.setDay(newtime.tm_mday);
	*/

	Reservation res(a, init_date, final_date, d, client);
	vector<Accomodation *> accomodations_tmp;

	reservations.push_back(res);

	vector<Suplier>::iterator its;
	vector<Accomodation*>::iterator ita;

	for (its = supliers.begin(); its != supliers.end(); its++) {
		accomodations_tmp = its->getAccomodations();

		for (ita = accomodations_tmp.begin(); ita != accomodations_tmp.end(); ita++) {
			if (*ita == a) {
				its->addReservation(res);
				break;
			}
		}

	}

//	updateDiscounts();

}

Accomodation* Company::displayOffers(string location, Date initial_date, Date final_date) {
	vector<Accomodation *> accomodations;
	vector<Accomodation *> accomodations_tmp;

	vector<pair<Date, Date>> unavailable_dates;

	vector<Suplier>::const_iterator its;
	vector<Accomodation *>::const_iterator ita;
	vector<pair<Date, Date>>::const_iterator itd;

	string location_tmp;
	Date id_tmp;
	Date fd_tmp;
	bool add = true;

	for (its = supliers.begin(); its != supliers.end(); its++) {
		accomodations_tmp = its->getAccomodations();

		for (ita = accomodations_tmp.begin(); ita != accomodations_tmp.end(); ita++) {
			location_tmp = (*ita)->getLocation();

			if (location_tmp == location) accomodations.push_back(*ita);

		}

	}

	// vetor de alojamentos com todos os alojamentos na cidade pretendida 


	accomodations_tmp = accomodations;
	accomodations.clear();

	for (ita = accomodations_tmp.begin(); ita != accomodations_tmp.end(); ita++) {

		unavailable_dates = (*ita)->getUnavailableDates();

		for (itd = unavailable_dates.begin(); itd != unavailable_dates.end(); itd++) {
			id_tmp = itd->first;
			fd_tmp = itd->second;

			if ((initial_date <= fd_tmp && initial_date >= id_tmp) || (final_date <= fd_tmp && final_date >= id_tmp)) {
				add = false;
			}
		}

		if (add == true) accomodations.push_back(*ita);

		add = true;
	}

	// vetor de alojamentos disponiveis nas datas pretendidas 


	clearScreen();

	if (accomodations.size() == 0) {
		cout << TAB << "Não existe nenhum alojamento que verifique as condições desejadas." << endl;
		return NULL;
	}

	gotoXY(48, 4); cout << "|| Alojamentos ||" << endl;

	for (ita = accomodations.begin(); ita != accomodations.end(); ita++) {
		cout << endl;
		(*ita)->print();
	}


	// Escolha do alojamento pretendido

	string id_str;
	unsigned int id;
	Accomodation * a = new Accomodation();


	cout << endl << TAB << "Introduza o ID do alojamento que pertende reservar." << endl;
	cout << TAB << "Caso não esteja interessado em nenhum dos alojamentos introduza o valor zero." << endl;

	cout << endl << TAB << "ID: ";

	getline(cin, id_str);
	if (cin.eof()) throw InvalidInput();
	id = stoi(id_str);

	if (id == 0) return NULL;

	a->setID(id);



	for (ita = accomodations.begin(); ita != accomodations.end(); ita++) {
		if ((*ita)->getID() == id) {
			a = (*ita);
		//	updateDiscounts();	//TODO not sure yet se está no sítio certo // definitivamente não o sítio certo

			return a;
		}
	}

	throw InvalidReservationID(id);



}

int Company::cancelReservation() {
	string id_str;
	unsigned int id;
	Date actual_date;
	Accomodation * a = new Accomodation();
	Date ci, co;
	vector<Reservation> reservations_tmp;
	int id_int, ad_int;
	int num_days;
	float price;
	int pos;
	bool found = false;


	vector<Reservation>::iterator itr;
	vector<Suplier>::iterator its;

	clearScreen();

	gotoXY(48, 4); cout << "|| Cancelar Reserva ||" << endl << endl << endl;

	cout << endl << TAB << "Introduza o ID da reserva que pretende cancelar." << endl;
	cout << TAB << "Caso não esteja interessado em cancelar reservas introduza o valor zero." << endl;

	cout << endl << TAB << "ID: ";



	getline(cin, id_str);
	if (cin.eof()) throw InvalidInput();
	id = stoi(id_str);

	if (id == 0) return id;

	clearScreen();

	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);

	actual_date.setYear(newtime.tm_year + 1900);
	actual_date.setMonth(newtime.tm_mon + 1);
	actual_date.setDay(newtime.tm_mday);


	for (itr = reservations.begin(); itr != reservations.end(); itr++) {
		if (itr->getID() == id) {
			a = itr->getAccomodation();
			ci = itr->getCheckIn();
			co = itr->getCheckOut();
			price = itr->getTotalPrice();
			found = true;
			break;
		}
	}

	if (!found) throw InvalidReservationID(id);

	// torna válidas as datas da reserva no alojamento correspondente
	a->removeDates(ci, co);

	Reservation res(id);

	//remove do vetor de reservas do fornecedor responsável a respetiva reserva
	for (its = supliers.begin(); its != supliers.end(); its++) {
		reservations_tmp = its->getReservations();

		pos = sequentialSearch<Reservation>(reservations_tmp, res);
		if (pos != -1) {
			its->deleteReservation(pos);
			break;
		}
	}


	//remove do vetor de reservas

	for (itr = reservations.begin(); itr != reservations.end(); itr++) {
		if (itr->getID() == id) {
			reservations.erase(itr);
			break;
		}
	}



	//converte a data de hoje e a date de inicio da reserva em inteiros
	id_int = ci.convert_date_int();
	ad_int = actual_date.convert_date_int();

	num_days = id_int - ad_int;

	if (num_days >= 30) {
		gotoXY(48, 4); cout << "|| Reservas ||" << endl << endl << endl;

		cout << TAB_BIG << TAB_BIG <<"A sua reserva foi cancelada com sucesso." << endl << endl;
		cout << TAB_BIG << TAB_BIG << "A totalidade do valor (" << price << ") ser-lhe-� devolvida." << endl;

		cout << TAB_BIG << TAB_BIG << "A sua reserva foi cancelada com sucesso." << endl << endl;
		cout << TAB_BIG << TAB_BIG << "A totalidade do valor (" << price << ") ser-lhe-á devolvida." << endl;


	}
	else if (num_days >= 15) {
		gotoXY(48, 4); cout << "|| Reservas ||" << endl << endl << endl;
		cout << TAB_BIG << TAB_BIG << "A sua reserva foi cancelada com sucesso." << endl << endl;
		cout << TAB_BIG << TAB_BIG << "Apenas 50% do valor (" << price / 2 << ") ser-lhe-á devolvida." << endl;

	}
	else {
		gotoXY(48, 4); cout << "|| Reservas ||" << endl << endl << endl;
		cout << TAB_BIG << TAB_BIG << "A sua reserva foi cancelada com sucesso." << endl << endl;
		cout << TAB_BIG << TAB_BIG << "Por a reserva ter sido cancelada com pouca antecedência não será reembolsadao." << endl;
	}


	return id;
}

void Company::showReservation()const {
	string id_str;
	unsigned int id;

	vector<Reservation>::const_iterator itr;

	clearScreen();
	gotoXY(48, 4); cout << "|| Reserva ||" << endl << endl << endl;

	cout << endl << TAB << "Introduza o ID da reserva que pretende visualizar." << endl;
	cout << TAB << "Caso não esteja interessado em visualizar reservas introduza o valor zero." << endl;

	cout << endl << TAB << "ID: ";

	getline(cin, id_str);
	if (cin.eof()) throw InvalidInput();
	id = stoi(id_str);

	if (id == 0) return;

	clearScreen();

	for (itr = reservations.begin(); itr != reservations.end(); itr++) {
		if (itr->getID() == id) {
			gotoXY(48, 4); cout << "|| Reserva ||" << endl << endl << endl;
			cout << "         ID Reserva             ID Alojamento                Check IN             Check OUT             Preço         " << endl;
			cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
			cout << (*itr);
			return;
		}
	}

	throw InvalidReservationID(id);



}


// -------------------
//     Administrator
// -------------------


void Company::showInactiveClients() const {

	unordered_set<Client, hcli, eqcli>::iterator it = inactiveClients.begin();

	gotoXY(40, 4); cout << "|| Lista de Clientes Inativos ||" << endl << endl << endl;
	cout << "            Username                    Password                     Nome do Cliente                  Pontos          " << endl;
	cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;


	while (it != inactiveClients.end()) {
		cout << *it << endl;
		it++;
	}
}

void Company::showActiveClients() const {

	vector<Client>::const_iterator it;

	gotoXY(40, 4); cout << "|| Lista de Clientes Ativos ||" << endl << endl << endl;
	cout << "            Username                    Password                     Nome do Cliente                  Pontos          " << endl;
	cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;

	for (it = clients.begin(); it != clients.end(); it++) {

		cout << *it << endl;
	}

}




/*

void Company::updateDiscounts() {

	bool found = false;
	for (int i = reservations.size(); i >= 0; i--) {
		priority_queue<Accomodation> temp = accomodationsDiscounts;
		for (int j = 0; j <= temp.size(); j++) {
			if (temp.top() == *(reservations.at(i)).getAccomodation())
				found = true;
			temp.pop();
		}

		if (!found) {
			accomodationsDiscounts.push(*(reservations.at(i)).getAccomodation());
			temp = accomodationsDiscounts;
		}
	}

}
*/

