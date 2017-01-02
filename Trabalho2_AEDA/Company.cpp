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
		string username, password, name, surname, adress, trash, nif; //, time ;
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
			string type, d, w, m, city, date1, date2, next, time;
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
				ss >> date2;
				Date d2(date2); pair_dates.second = d2;
				unavailableDates.push_back(pair_dates);
				ss >> date1;

			}

			getline(ss, time, '-'); trim(time);
			Date creation_time(time);

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

				Bedroom *bed = new Bedroom(ID, daily, weekly, monthly, city, unavailableDates, creation_time, estbl, bedType);
				accomodations.push_back(bed);
				sup.addAccomodationFile(bed);

				updateDiscounts(*bed);
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

				Apartment *apart = new Apartment(ID, daily, weekly, monthly, city, unavailableDates, creation_time, numRooms, suite);
				accomodations.push_back(apart);
				sup.addAccomodationFile(apart);

				updateDiscounts(*apart);
			}


			if (type == "FLAT")
			{

				Flat *flt = new Flat(ID, daily, weekly, monthly, city, unavailableDates, creation_time);
				accomodations.push_back(flt);
				sup.addAccomodationFile(flt);

				updateDiscounts(*flt);

			}

		}
		supliers.push_back(sup);
	}

	name_supliers.close();
}

void Company::reservationsInicialization(string reservationsFile) {

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
					updateDiscounts();
					reservationsBST.insert(reserv);
					it->addReservation(reserv);

					break;

				}
			}
		}
	}

	name_reservations.close();

	// TEST

	for (int i = 0; i < accomodations.size(); i++) {
		accomodations.at(i)->setDiscount(calculateDiscounts(*(accomodations[i])));
		cout << "lr id " << accomodations.at(i)->getLastReservationID() << endl;
		cout << "id accomodation " << accomodations.at(i)->getID() << endl;
		system("pause");
	}
}

void Company::clientsInicialization(string clientsFile) {
	ifstream name_clients;
	string line_c;

	name_clients.open(clientsFile);

	while (getline(name_clients, line_c))
	{
		string ID, password, name, surname, pts, IDreservation, trash, adress;
		unsigned int idr;
		stringstream ss; ss.str(line_c);

		ss >> ID;
		ss >> password;
		ss >> name;
		ss >> surname; name = name + ' ' + surname;
		ss >> pts;
		ss >> trash; getline(ss, adress, '-'); trim(adress);


		Client client(ID, password, name, adress);

		bool activeClient = true;

		while (ss >> IDreservation)
		{
			idr = fromString<unsigned int>(IDreservation);

			BSTItrIn<Reservation> itr(reservationsBST);

			while (!itr.isAtEnd()) {
				Reservation r = itr.retrieve();
				if (r.getID() == idr)
					client.addReservation(r);

				itr.advance();
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


	// TEST

	cout << "clientsInit\n";

	for (int i = 0; i < accomodations.size(); i++) {
		accomodations.at(i)->setDiscount(calculateDiscounts(*(accomodations[i])));
		cout << "lr id " << accomodations.at(i)->getLastReservationID() << endl;
		cout << "id accomodation " << accomodations.at(i)->getID() << endl;
		system("pause");
	}
}

Company::Company(string clientsFile, string supliersFile, string reservationsFile) : reservationsBST(Reservation()) {
	cout << "inicia company";

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
	BSTItrIn<Reservation> itr(reservationsBST);
	fout.open(reservationsFile);

	if (fout.fail()) throw ErrorOpeningFile("Reservas");

	fout << setw(5) << Reservation::getLastID() << endl;

	while (!itr.isAtEnd()) {
		itr.retrieve().save(fout);
		itr.advance();
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

	if (NIF > 999999999 || NIF < 100000000)throw InvalidInput();

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
		gotoXY(42, 13); cout << "Adicionar Alojamento (s/n)? ";
		getline(cin, add);

		if (cin.eof()) throw InvalidInput();

		Accomodation acc;
		if (add == "s") {
			acc = s.addAccomodation2();
			updateDiscounts(acc);
		}

	} while (add == "s");

	if (add != "n") throw InvalidInput();

	clearScreen();

	supliers.push_back(s);

	gotoXY(48, 4); cout << "|| Registar ||" << endl << endl;

	gotoXY(35, 7); cout << s.getName() << ", a sua conta foi criada com sucesso!" << endl;


	updateDiscounts();

}


void Company::showSupliers() {
	sort(supliers.begin(), supliers.end());


	gotoXY(48, 4); cout << "|| Fornecedores ||" << endl << endl << endl;

	cout << "     Nome             Nome de Utilizador  NIF          Morada                                  Alojamentos             " << endl;
	cout << " --------------------------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < supliers.size(); i++) {
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
	string name, adress, username, password = "";
	char ch;

	clearScreen();


	gotoXY(48, 4);  cout << "|| Registar ||" << endl << endl;
	gotoXY(42, 7);  cout << "Nome: ";
	getline(cin, name);
	if (cin.eof()) throw InvalidInput();

	gotoXY(42, 7);  cout << "Morada: ";
	getline(cin, adress);
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


	Client client(username, password, name, adress);
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

vector<Client>::iterator Company::reservationHash(unordered_set<Client, hcli, eqcli>::iterator ith, Reservation res) {

	Client cli = *ith;
	cli.addReservation(res);

	inactiveClients.erase(ith);

	clients.push_back(cli);

	vector<Client>::iterator it;

	for (it = clients.begin(); it != clients.end(); it++) {

		if (cli.getUsername() == it->getUsername())
			return it;
	}

}



// -------------------
//     Reservation
// -------------------

void Company::addReservationComp(Accomodation *a, Reservation res) {

	vector<Accomodation *> accomodations_tmp;

	//reservations.push_back(res);

	reservationsBST.insert(res);

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

	updateDiscounts();

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
		cout << TAB << "Nao existe nenhum alojamento que verifique as condicoes desejadas." << endl;
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
	cout << TAB << "Caso nao esteja interessado em nenhum dos alojamentos introduza o valor zero." << endl;

	cout << endl << TAB << "ID: ";

	getline(cin, id_str);
	if (cin.eof()) throw InvalidInput();
	id = stoi(id_str);

	if (id == 0) return NULL;

	a->setID(id);



	for (ita = accomodations.begin(); ita != accomodations.end(); ita++) {
		if ((*ita)->getID() == id) {
			a = (*ita);

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
	cout << TAB << "Caso nao esteja interessado em cancelar reservas introduza o valor zero." << endl;

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

	BSTItrIn<Reservation> itr_bst(reservationsBST);
	Reservation r;


	while (!itr_bst.isAtEnd()) {
		r = itr_bst.retrieve();
		if (r.getID() == id) {
			a = r.getAccomodation();
			ci = r.getCheckIn();
			co = r.getCheckOut();
			price = r.getTotalPrice();
			found = true;
			break;
		}

		itr_bst.advance();
	}

	if (!found) throw InvalidReservationID(id);

	// remove da árvore de reservas

	reservationsBST.remove(r);

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

	/*
	for (itr = reservations.begin(); itr != reservations.end(); itr++) {
		if (itr->getID() == id) {
			reservations.erase(itr);
			break;
		}
	}
	*/


	//converte a data de hoje e a date de inicio da reserva em inteiros
	id_int = ci.convert_date_int();
	ad_int = actual_date.convert_date_int();

	num_days = id_int - ad_int;

	if (num_days >= 30) {
		gotoXY(48, 4); cout << "|| Reservas ||" << endl << endl << endl;

		cout << TAB_BIG << TAB_BIG << "A sua reserva foi cancelada com sucesso." << endl << endl;
		cout << TAB_BIG << TAB_BIG << "A totalidade do valor (" << price << ") ser-lhe-a devolvida." << endl;


	}
	else if (num_days >= 15) {
		gotoXY(48, 4); cout << "|| Reservas ||" << endl << endl << endl;
		cout << TAB_BIG << TAB_BIG << "A sua reserva foi cancelada com sucesso." << endl << endl;
		cout << TAB_BIG << TAB_BIG << "Apenas 50% do valor (" << price / 2 << ") ser-lhe-a devolvida." << endl;

	}
	else {
		gotoXY(48, 4); cout << "|| Reservas ||" << endl << endl << endl;
		cout << TAB_BIG << TAB_BIG << "A sua reserva foi cancelada com sucesso." << endl << endl;
		cout << TAB_BIG << TAB_BIG << "Por a reserva ter sido cancelada com pouca antecedencia não será reembolsado." << endl;
	}

	//updateDiscounts();
	return id;
}

void Company::showReservation()const {
	string id_str;
	unsigned int id;

	BSTItrIn<Reservation> itr(reservationsBST);


	clearScreen();
	gotoXY(48, 4); cout << "|| Reserva ||" << endl << endl << endl;

	cout << endl << TAB << "Introduza o ID da reserva que pretende visualizar." << endl;
	cout << TAB << "Caso nao esteja interessado em visualizar reservas introduza o valor zero." << endl;

	cout << endl << TAB << "ID: ";

	getline(cin, id_str);
	if (cin.eof()) throw InvalidInput();
	id = stoi(id_str);

	if (id == 0) return;

	clearScreen();

	while (!itr.isAtEnd()) {


		if (itr.retrieve().getID() == id) {
			gotoXY(48, 4); cout << "|| Reserva ||" << endl << endl << endl;
			cout << "    Cliente             ID Reserva     ID Alojamento     Check IN          Check OUT        Preco        Marcacao     " << endl;
			cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
			cout << itr.retrieve();
			return;
		}

		itr.advance();
	}


	throw InvalidReservationID(id);



}

void Company::showReservations() const {
	BSTItrIn<Reservation> itr(reservationsBST);

	clearScreen();

	gotoXY(48, 4); cout << "|| Reservas ||" << endl << endl << endl;
	cout << "    Cliente             ID Reserva     ID Alojamento     Check IN          Check OUT        Preco        Marcacao     " << endl;
	cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;

	while (!itr.isAtEnd()) {
		cout << itr.retrieve();

		itr.advance();
	}


	pauseScreen();
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

void Company::showInactiveClientsAdresses() const {

	unordered_set<Client, hcli, eqcli>::iterator it = inactiveClients.begin();

	gotoXY(40, 4); cout << "|| Moradas de Clientes Inativos ||" << endl << endl << endl;
	cout << "           Nome do Cliente                  Username                     Morada                                       " << endl;
	cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;


	while (it != inactiveClients.end()) {

		cout << left << "             ";

		cout << setw(33) << it->getName()
			<< setw(25) << it->getUsername()
			<< setw(50) << it->getAdress();

		it++;
	}
}

void Company::updateAdresses() {

	int points;
	string username, adress, name, password;
	bool exist = false;

	showInactiveClientsAdresses();
	pauseScreen();
	clearScreen();
	gotoXY(40, 4); cout << "|| Atualizar Moradas ||" << endl << endl << endl;

	gotoXY(30, 7); cout << "Nome de utilizador: ";
	getline(cin, username);
	if (cin.eof()) throw InvalidInput();

	unordered_set<Client, hcli, eqcli>::iterator it = inactiveClients.begin();

	while (it != inactiveClients.end()) {

		if (username == it->getUsername())
			exist = true;
		it++;
	}

	if (exist) {

		gotoXY(30, 8); cout << "Nova morada: ";
		getline(cin, adress);
		if (cin.eof()) throw InvalidInput();

		unordered_set<Client, hcli, eqcli>::iterator itt = inactiveClients.begin();
		vector<Reservation>reser;

		while (itt != inactiveClients.end()) {

			if (username == itt->getUsername()) {

				password = itt->getPassword();
				name = itt->getName();
				points = itt->getPoints();
				reser = itt->getReservations();
				break;
			}

			itt++;
		}

		Client cli(username, password, name, adress, points);

		vector<Reservation>::iterator itr;

		for (itr = reser.begin(); itr != reser.end(); itr++) {

			cli.addReservation(*itr);
		}

		inactiveClients.erase(itt);

		inactiveClients.insert(cli);


		gotoXY(30, 12); cout << "Morada atualizada com sucesso";

	}
	else {
		gotoXY(30, 9); cout << "O nome de utilizador nao e valido!!" << endl;
	}



}

void Company::updateDiscounts() {

	/*bool found;
	BSTItrIn<Reservation> itr(reservationsBST);
	priority_queue<Accomodation> temp;

	while (!itr.isAtEnd()) {

		found = false;
		temp = accomodationsDiscounts;*/
		/*for (int j = 0; j < accomodationsDiscounts.size(); j++) {

			if (temp.top() == *(itr.retrieve()).getAccomodation())
				found = true;
			temp.pop();
		}
		if (!found) {*/


	/*for (int i = 0; i < supliers.size(); i++) {
		for (int j = 0; j < supliers.at(i).getAccomodations().size(); j++) {
			if (*(supliers.at(i).getAccomodations().at(j)) == *(itr.retrieve().getAccomodation()))
				supliers.at(i).getAccomodations().at(j)->setDiscount(calculateDiscounts(*(itr.retrieve().getAccomodation())));
		}
	}*/
	
	while (!accomodationsDiscounts.empty()) {
		accomodationsDiscounts.pop();
	}

	cout << "updateDiscounts" << endl;
	for (int i = 0; i < accomodations.size(); i++) {
		cout << accomodations.at(i)->getID() << endl;
		accomodationsDiscounts.push(*(accomodations.at(i)));
		accomodations.at(i)->setDiscount(calculateDiscounts(*(accomodations[i])));
	}
	/*}
	itr.advance();
}*/
}

void Company::updateDiscounts(Accomodation acc) {

	bool found = false;
	priority_queue<Accomodation> temp = accomodationsDiscounts;

	cout << "size: " << accomodationsDiscounts.size() << endl;
	for (int j = 0; j < accomodationsDiscounts.size(); j++) {

		if (temp.top() == acc)
			found = true;
		temp.pop();
	}

	if (!found) {
		accomodationsDiscounts.push(acc);

		/*for (int i = 0; i < supliers.size(); i++) {
			for (int j = 0; j < supliers.at(i).getAccomodations().size(); j++) {
				cout << supliers.at(i).getAccomodations().at(j)->getID() << " maybe bitch " << acc.getID() << endl;
				if (*(supliers.at(i).getAccomodations().at(j)) == acc)
					supliers.at(i).getAccomodations().at(j)->setDiscount(calculateDiscounts(acc));
			}
		}*/
		for (int i = 0; i < accomodations.size(); i++) {
			accomodations.at(i)->setDiscount(calculateDiscounts(*(accomodations[i])));
		}
	}
}

float Company::calculateDiscounts(Accomodation acc) {
	priority_queue<Accomodation> temp = accomodationsDiscounts;
	float res;
	int first10percent, second10percent, third10percent;
	discounts.clear();

	first10percent = round(0.1 * accomodationsDiscounts.size());
	second10percent = 2 * first10percent;
	third10percent = 3 * first10percent;

	int index = 0;
	while (!accomodationsDiscounts.empty()) {
		if (acc == temp.top()) {
			break;
		}
		index++;
		temp.pop();
	}

	for (int i = 1; i <= accomodationsDiscounts.size(); i++) {
		if (i <= first10percent) {
			discounts.push_back(0.5);
		}
		else if (i > first10percent && i <= second10percent) {
			discounts.push_back(0.25);
		}
		else if (i > second10percent && i <= third10percent) {
			discounts.push_back(0.1);
		}
		else {
			discounts.push_back(0);
		}
		/*if (temp.top() == acc) {
			cout << "accomodationDiscounts.size()=" << accomodationsDiscounts.size() << endl;
			cout << "[" << first10percent << ", " << second10percent << ", " << third10percent << "]" << endl;
			cout << temp.top().getID() << "==" << acc.getID() << endl;
			cout << "Discount=" << discounts.back() << " (i=" << i << ")" << endl;
			system("pause");

			res = discounts.back();
		}
		temp.pop();*/
	}

	/*cout << "accomodationDiscounts.size()=" << accomodationsDiscounts.size() << endl;
	cout << "[" << first10percent << ", " << second10percent << ", " << third10percent << "]" << endl;
	cout << temp.top().getID() << "==" << acc.getID() << endl;
	cout << "Discount=" << discounts[index] << " (index=" << index << ")" << endl;*/
	//system("pause");
	return discounts[index];
}

void Company::showDiscounts() {


	gotoXY(40, 4); cout << "|| Lista de Descontos dos Alojamentos ||" << endl << endl << endl;
	cout << "            ID Alojamento                    Desconto              " << endl;
	cout << " ------------------------------------------------------------------" << endl;

	priority_queue<Accomodation> temp = accomodationsDiscounts;

	for (int j = 0; j < accomodationsDiscounts.size(); j++) {

		cout << setw(10) << temp.top().getID() << setw(10) << discounts[j] << endl;

		temp.pop();
	}
}


