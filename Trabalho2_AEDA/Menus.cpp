#include "Menus.h"

// -------------------
//     Client Menu
// -------------------

void Menu::writeClientMenu(int x) {

	switch (x)
	{
	case 7:
		cout << "   Efetuar Reserva                     ";
		break;
	case 8:
		cout << "   Ver Reservas                        ";
		break;
	case 9:
		cout << "   Cancelar Reservas                   ";
		break;
	case 10:
		cout << "   Informacao de Conta                 ";
		break;
	case 11:
		cout << "   Sair                                ";
		break;

	}
}

void Menu::OptionClientAddReservation(Company & comp, vector<Client>::iterator it) {
<<<<<<< HEAD

	try {

		string location, date;
		Date initial_date, final_date;
		Accomodation* acc;
		Reservation res;

		clearScreen();

		gotoXY(48, 4); cout << "|| Efetuar Reserva ||" << endl << endl;

		gotoXY(40, 7); cout << "Local: ";
		getline(cin, location);
		if (cin.eof()) throw InvalidInput();

		gotoXY(40, 9); cout << "Data Inicial: ";
		getline(cin, date);
		if (!initial_date.getDate(date)) throw InvalidDate();

		gotoXY(40, 10); cout << "Data Final: ";
		getline(cin, date);
		if (!final_date.getDate(date)) throw InvalidDate();

		acc = comp.displayOffers(location, initial_date, final_date);
		if (acc == NULL) clientMenu(comp, it);

		res.setAccomodation(acc);
		res.setCheckIN(initial_date);
		res.setCheckOUT(final_date);
		res.setClient(it->getName());
		res.setMarking(getCurrentDate());
		res.setID();

		comp.addReservationComp(acc, res);
		// faz o add discounts só na função chamada acima ^^^^ 

		it->addReservation(res);

		clearScreen();

		gotoXY(48, 4); cout << "|| Reserva ||" << endl << endl << endl;

		cout << "    Cliente             ID Reserva     ID Alojamento     Check IN          Check OUT        Preco        Marcacao     " << endl;
		cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
		cout << res;

		cout << endl << TAB_BIG << "A sua reserva foi criada com sucesso." << endl;
		cout << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Cliente." << endl << endl;

=======

	try {

		string location, date;
		Date initial_date, final_date;
		Accomodation* acc;
		Reservation res;

		clearScreen();

		gotoXY(48, 4); cout << "|| Efetuar Reserva ||" << endl << endl;

		gotoXY(40, 7); cout << "Local: ";
		getline(cin, location);
		if (cin.eof()) throw InvalidInput();

		gotoXY(40, 9); cout << "Data Inicial: ";
		getline(cin, date);
		if (!initial_date.getDate(date)) throw InvalidDate();

		gotoXY(40, 10); cout << "Data Final: ";
		getline(cin, date);
		if (!final_date.getDate(date)) throw InvalidDate();

		acc = comp.displayOffers(location, initial_date, final_date);
		if (acc == NULL) clientMenu(comp, it);

		res.setAccomodation(acc);
		res.setCheckIN(initial_date);
		res.setCheckOUT(final_date);
		res.setClient(it->getName());
		res.setMarking(getCurrentDate());
		res.setID();

		comp.addReservationComp(acc, res);
		// faz o add discounts só na função chamada acima ^^^^ 

		it->addReservation(res);

		clearScreen();

		gotoXY(48, 4); cout << "|| Reserva ||" << endl << endl << endl;

		cout << "    Cliente             ID Reserva     ID Alojamento     Check IN         Check OUT      Preço     Marcacao   " << endl;
		cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
		cout << res;

		cout << endl << TAB_BIG << "A sua reserva foi criada com sucesso." << endl;
		cout << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Cliente." << endl << endl;

>>>>>>> origin/master
		pauseScreen();
		clientMenu(comp, it);
	}
	catch (WrongOption wp) {
		cout << wp;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenu(comp, it);
	}
	catch (InvalidInput ii) {
		cout << ii;
		cin.clear();
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenu(comp, it);
	}
	catch (InvalidDate id) {
		cout << id;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenu(comp, it);
	}
	catch (invalid_argument) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introducao dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "Deve introduzir um numero." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenu(comp, it);
	}
	catch (out_of_range) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introducao dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "O número introduzido ultrapassa os valores suportados." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenu(comp, it);
	}
	catch (InvalidLogIn ili) {
		cout << ili;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenu(comp, it);
	}
	catch (InvalidUsername iu) {
		cout << iu;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenu(comp, it);
	}
	catch (ErrorOpeningFile eof) {
		cout << eof;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenu(comp, it);
	}
	catch (InvalidReservationID iri) {
		cout << iri;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenu(comp, it);
	}
}

void Menu::OptionClientShowReservations(Company & comp, vector<Client>::iterator it) {
	
	it->showReservations();
	pauseScreen();
	clientMenu(comp, it);
}

void Menu::OptionClientCancelReservation(Company & comp, vector<Client>::iterator it) {
	
	Reservation res;
	int id, pos;
	vector<Reservation> reservations_tmp;
	
	try {
		it->showReservations();
		id = comp.cancelReservation();
		if (id == 0) clientMenu(comp, it);

		reservations_tmp = it->getReservations();
		res.setID(id);
		pos = sequentialSearch<Reservation>(reservations_tmp, res);

		it->deleteReservation(pos);
		pauseScreen();
		clientMenu(comp, it);
	}
	catch (WrongOption wp) {
		cout << wp;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenu(comp, it);
	}
	catch (InvalidInput ii) {
		cout << ii;
		cin.clear();
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenu(comp, it);
<<<<<<< HEAD
	}
	catch (InvalidDate id) {
		cout << id;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenu(comp, it);
	}
	catch (invalid_argument) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introducao dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "Deve introduzir um numero." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenu(comp, it);
	}
	catch (out_of_range) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introducao dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "O numero introduzido ultrapassa os valores suportados." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenu(comp, it);
	}
	catch (InvalidLogIn ili) {
		cout << ili;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenu(comp, it);
	}
	catch (InvalidUsername iu) {
		cout << iu;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenu(comp, it);
	}
	catch (ErrorOpeningFile eof) {
		cout << eof;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenu(comp, it);
	}
=======
	}
	catch (InvalidDate id) {
		cout << id;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenu(comp, it);
	}
	catch (invalid_argument) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introducao dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "Deve introduzir um numero." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenu(comp, it);
	}
	catch (out_of_range) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introducao dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "O numero introduzido ultrapassa os valores suportados." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenu(comp, it);
	}
	catch (InvalidLogIn ili) {
		cout << ili;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenu(comp, it);
	}
	catch (InvalidUsername iu) {
		cout << iu;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenu(comp, it);
	}
	catch (ErrorOpeningFile eof) {
		cout << eof;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenu(comp, it);
	}
>>>>>>> origin/master
	catch (InvalidReservationID iri) {
		cout << iri;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenu(comp, it);
	}
}

void Menu::OptionClientInformation(Company & comp, vector<Client>::iterator it){

	clearScreen();
	gotoXY(48, 4); cout << "|| Informacoes de Conta ||" << endl << endl;
	cout << "---------------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << TAB_BIG << TAB_BIG << TAB_BIG << "                    Nome : " << it->getName() << endl;
	cout << TAB_BIG << TAB_BIG << TAB_BIG << "      Nome de Utilizador : " << it->getUsername() << endl;
	cout << TAB_BIG << TAB_BIG << TAB_BIG << "                  Pontos : " << it->getPoints() << endl << endl;
	cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
	pauseScreen();
	clientMenu(comp, it);
}

void Menu::clientMenu(Company & comp, vector<Client>::iterator it) {

	clearScreen();
	int menu_item = 0, x = 7;
	bool running = true;

	gotoXY(48, 4); cout << "|| " << it->getName() << " ||";
	gotoXY(41, 7); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  " << "   Efetuar Reserva                     ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoXY(43, 8);  cout << "   Ver Reservas                        ";
	gotoXY(43, 9);  cout << "   Cancelar Reservas                   ";
	gotoXY(43, 10); cout << "   Informacao de Conta                 ";
	gotoXY(43, 11); cout << "   Sair                                ";
	gotoXY(43, 15);

	system("pause>nul");

	if (GetAsyncKeyState(VK_RETURN)) {

		gotoXY(43, 15); cout << "  ";
	}

	while (running)
	{

		gotoXY(43, 15);

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && x < 11) //down button pressed
		{
			gotoXY(41, x); cout << "  "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); writeClientMenu(x);
			x++;
			gotoXY(41, x); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  "; writeClientMenu(x);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x > 7) //up button pressed
		{
			gotoXY(41, x); cout << "  "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); writeClientMenu(x);
			x--;
			gotoXY(41, x); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  "; writeClientMenu(x);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed

			switch (menu_item) {
			case 0:
				OptionClientAddReservation(comp, it);
				break;
			case 1:
				OptionClientShowReservations(comp, it);
				break;
			case 2:
				OptionClientCancelReservation(comp, it);
				break;
			case 3:
				OptionClientInformation(comp, it);
				break;
			case 4:
				novoMenu(comp);
				break;
			}
		}
	}
}



// ---------------------------
//    Inactive Client Menu
// ---------------------------

void Menu::OptionInaClientAddReservation(Company & comp, unordered_set<Client, hcli, eqcli>::iterator ith) {

	try {

		string location, date;
		Date initial_date, final_date;
		Accomodation* acc;
		Reservation res;
		clearScreen();

		gotoXY(48, 4); cout << "|| Efetuar Reserva ||" << endl << endl;

		gotoXY(40, 7); cout << "Local: ";
		getline(cin, location);
		if (cin.eof()) throw InvalidInput();

		gotoXY(40, 9); cout << "Data Inicial: ";
		getline(cin, date);
		if (!initial_date.getDate(date)) throw InvalidDate();

		gotoXY(40, 10); cout << "Data Final: ";
		getline(cin, date);
		if (!final_date.getDate(date)) throw InvalidDate();

		acc = comp.displayOffers(location, initial_date, final_date);
		if (acc == NULL) clientMenuHash(comp, ith);

		res.setAccomodation(acc);
		res.setCheckIN(initial_date);
		res.setCheckOUT(final_date);
		res.setClient(ith->getName());
		res.setMarking(getCurrentDate());
		res.setID();

		comp.addReservationComp(acc, res);
<<<<<<< HEAD

		clearScreen();

		gotoXY(48, 4); cout << "|| Reserva ||" << endl << endl << endl;

		cout << "         ID Reserva             ID Alojamento                Check IN             Check OUT             Preço         " << endl;
		cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
		cout << res;

		cout << endl << TAB_BIG << "A sua reserva foi criada com sucesso." << endl;
		cout << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Cliente." << endl << endl;

		pauseScreen();

		clientMenuHash(comp, ith);
	}
	catch (WrongOption wp) {
		cout << wp;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
	catch (InvalidInput ii) {
		cout << ii;
		cin.clear();
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
	catch (InvalidDate id) {
		cout << id;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
	catch (invalid_argument) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introducao dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "Deve introduzir um numero." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
	catch (out_of_range) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introducao dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "O numero introduzido ultrapassa os valores suportados." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
	catch (InvalidLogIn ili) {
		cout << ili;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
	catch (InvalidUsername iu) {
		cout << iu;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
	catch (ErrorOpeningFile eof) {
		cout << eof;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
	catch (InvalidReservationID iri) {
		cout << iri;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
}

=======
    
		clearScreen();

		gotoXY(48, 4); cout << "|| Reserva ||" << endl << endl << endl;

		cout << "         ID Reserva             ID Alojamento                Check IN             Check OUT             Preço         " << endl;
		cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
		cout << res;

		cout << endl << TAB_BIG << "A sua reserva foi criada com sucesso." << endl;
		cout << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Cliente." << endl << endl;

		pauseScreen();

		clientMenuHash(comp, ith);
	}
	catch (WrongOption wp) {
		cout << wp;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
	catch (InvalidInput ii) {
		cout << ii;
		cin.clear();
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
	catch (InvalidDate id) {
		cout << id;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
	catch (invalid_argument) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introducao dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "Deve introduzir um numero." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
	catch (out_of_range) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introducao dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "O numero introduzido ultrapassa os valores suportados." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
	catch (InvalidLogIn ili) {
		cout << ili;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
	catch (InvalidUsername iu) {
		cout << iu;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
	catch (ErrorOpeningFile eof) {
		cout << eof;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
	catch (InvalidReservationID iri) {
		cout << iri;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
}

>>>>>>> origin/master
void Menu::OptionInaClientShowReservations(Company & comp, unordered_set<Client, hcli, eqcli>::iterator ith) {

	ith->showReservations();
	pauseScreen();
	clientMenuHash(comp, ith);
}

void Menu::OptionInaClientCancelReservation(Company & comp, unordered_set<Client, hcli, eqcli>::iterator ith) {

	try {
		Reservation res;
		int id, pos;
		vector<Reservation> reservations_tmp;

		ith->showReservations();
		pauseScreen();
		id = comp.cancelReservation();
		if (id == 0) clientMenuHash(comp, ith);
<<<<<<< HEAD

		reservations_tmp = ith->getReservations();
		res.setID(id);
		pos = sequentialSearch<Reservation>(reservations_tmp, res);

=======

		reservations_tmp = ith->getReservations();
		res.setID(id);
		pos = sequentialSearch<Reservation>(reservations_tmp, res);

>>>>>>> origin/master
		ith = comp.replaceHashClient(ith, pos);

		pauseScreen();
		clientMenuHash(comp, ith);
		
	}
	catch (WrongOption wp) {
		cout << wp;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
	catch (InvalidInput ii) {
		cout << ii;
		cin.clear();
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
	catch (InvalidDate id) {
		cout << id;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
	catch (invalid_argument) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introducao dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "Deve introduzir um numero." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
	catch (out_of_range) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introducao dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "O numero introduzido ultrapassa os valores suportados." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
	catch (InvalidLogIn ili) {
		cout << ili;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
	catch (InvalidUsername iu) {
		cout << iu;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
	catch (ErrorOpeningFile eof) {
		cout << eof;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
	catch (InvalidReservationID iri) {
		cout << iri;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Client." << endl;
		pauseScreen();
		clientMenuHash(comp, ith);
	}
}

void Menu::OptionInaClientInformation(Company & comp, unordered_set<Client, hcli, eqcli>::iterator ith) {

	clearScreen();
	gotoXY(48, 4); cout << "|| Informacoes de Conta ||" << endl << endl;
	cout << "---------------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << TAB_BIG << TAB_BIG << TAB_BIG << "                    Nome : " << ith->getName() << endl;
	cout << TAB_BIG << TAB_BIG << TAB_BIG << "      Nome de Utilizador : " << ith->getUsername() << endl;
	cout << TAB_BIG << TAB_BIG << TAB_BIG << "                  Pontos : " << ith->getPoints() << endl << endl;
	cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
	pauseScreen();
	clientMenuHash(comp, ith);

}

void Menu::clientMenuHash(Company & comp, unordered_set<Client, hcli, eqcli>::iterator ith) {

	clearScreen();
	int menu_item = 0, x = 7;
	bool running = true;


	gotoXY(48, 4); cout << "|| " << ith->getName() << " ||";
	gotoXY(41, 7); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  " << "   Efetuar Reserva                     ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoXY(43, 8);  cout << "   Ver Reservas                        ";
	gotoXY(43, 9);  cout << "   Cancelar Reservas                   ";
	gotoXY(43, 10); cout << "   Informação de Conta                 ";
	gotoXY(43, 11); cout << "   Sair                                ";
	gotoXY(43, 15);

	system("pause>nul");

	if (GetAsyncKeyState(VK_RETURN)) {

		gotoXY(43, 15); cout << "  ";
	}

	while (running)
	{

		gotoXY(43, 15);

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && x < 11) //down button pressed
		{
			gotoXY(41, x); cout << "  "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); writeClientMenu(x);
			x++;
			gotoXY(41, x); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  "; writeClientMenu(x);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x > 7) //up button pressed
		{
			gotoXY(41, x); cout << "  "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); writeClientMenu(x);
			x--;
			gotoXY(41, x); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  "; writeClientMenu(x);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed

			switch (menu_item) {
			case 0:
				OptionInaClientAddReservation(comp, ith);
				break;
			case 1:
				OptionInaClientShowReservations(comp, ith);
				break;
			case 2:
				OptionInaClientCancelReservation(comp, ith);
				break;
			case 3:
				OptionInaClientInformation(comp, ith);
				break;
			case 4:
				novoMenu(comp);
				break;
			}
		}
	}
}



// ---------------------------
//   Suplier Menu
// ---------------------------

void Menu::writeSuplierMenu(int x) {

	switch (x)
	{
	case 7:
		cout << "   Ver Alojamentos                     ";
		break;
	case 8:
		cout << "   Adicionar Alojamento                ";
		break;
	case 9:
		cout << "   Informacoes de Conta                ";
		break;
	case 10:
		cout << "   Ver Reservas                        ";
		break;
	case 11:
		cout << "   Consultar Taxas de Servico          ";
		break;
	case 12:
		cout << "   Sair                                ";
		break;
	}
}

void Menu::OptionSuplierAddAccomodation(Company & comp, vector<Suplier>::iterator it) {
<<<<<<< HEAD


	try
	{
		string add;

		add = "s";
		while (add == "s") {

			Accomodation * acc;
			acc = it->addAccomodation2();
			comp.addAccomodation(acc);


			cout << endl << TAB << "Adicionar Alojamento (s/n)? ";
			getline(cin, add);

		}

		if (add != "n") throw InvalidInput();

=======


	try
	{
		string add;

		add = "s";
		while (add == "s") {

			Accomodation acc;
			acc = it->addAccomodation2();
			comp.updateDiscounts(acc);


			cout << endl << TAB << "Adicionar Alojamento (s/n)? ";
			getline(cin, add);

		}

		if (add != "n") throw InvalidInput();

>>>>>>> origin/master

		clearScreen();
		gotoXY(48, 4); cout << "|| Adicionar Alojamento ||" << endl << endl;
		gotoXY(35, 10); cout << "Os seus alojamentos foram atualizados com sucesso!" << endl;
		pauseScreen();
		suplierMenu(comp, it);
	}
	catch (WrongOption wp) {
		cout << wp;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu de Fornecedores." << endl;
		pauseScreen();
		suplierMenu(comp, it);
	}
	catch (InvalidInput ii) {
		cout << ii;
		cin.clear();
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu de Fornecedores." << endl;
		pauseScreen();
		suplierMenu(comp, it);
<<<<<<< HEAD
	}
	catch (InvalidDate id) {
		cout << id;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu de Fornecedores." << endl;
		pauseScreen();
		suplierMenu(comp, it);
	}
	catch (invalid_argument) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introducao dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "Deve introduzir um numero." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu de Fornecedores." << endl;
		pauseScreen();
		suplierMenu(comp, it);
	}
=======
	}
	catch (InvalidDate id) {
		cout << id;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu de Fornecedores." << endl;
		pauseScreen();
		suplierMenu(comp, it);
	}
	catch (invalid_argument) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introducao dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "Deve introduzir um numero." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu de Fornecedores." << endl;
		pauseScreen();
		suplierMenu(comp, it);
	}
>>>>>>> origin/master
	catch (out_of_range) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introducao dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "O numero introduzido ultrapassa os valores suportados." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu de Fornecedores." << endl;
		pauseScreen();
		suplierMenu(comp, it);
	}
}

void Menu::OptionSuplierShowAccomodations(Company & comp, vector<Suplier>::iterator it) {

		it->showAccomodations();
		pauseScreen();
		suplierMenu(comp, it);

}

void Menu::OptionSuplierInformation(Company & comp, vector<Suplier>::iterator it) {

	clearScreen();
	gotoXY(48, 4); cout << "|| Informacoes de Conta ||" << endl << endl;
	cout << "---------------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << TAB_BIG << TAB_BIG << TAB_BIG << "                    Nome : " << it->getName() << endl;
	cout << TAB_BIG << TAB_BIG << TAB_BIG << "      Nome de Utilizador : " << it->getUsername() << endl;
	cout << TAB_BIG << TAB_BIG << TAB_BIG << "                     NIF : " << it->getNIF() << endl;
	cout << TAB_BIG << TAB_BIG << TAB_BIG << "                  Morada : " << it->getAdress() << endl << endl;
	cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
	pauseScreen();
	suplierMenu(comp, it);

}

void Menu::OptionSuplierReservations(Company & comp, vector<Suplier>::iterator it) {

	it->showReservations();
	pauseScreen();
	suplierMenu(comp, it);

}

void Menu::OptionSuplierShowFees(Company & comp, vector<Suplier>::iterator it) {

	clearScreen();
	it->showFees();
	pauseScreen();
	suplierMenu(comp, it);

}

void Menu::suplierMenu(Company & comp, vector<Suplier>::iterator it) {

	clearScreen();
	int menu_item = 0, x = 7;
	bool running = true;

	gotoXY(48, 4); cout << "|| " << it->getUsername() << " ||";

	gotoXY(41, 7); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  " << "   Ver Alojamentos                     ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoXY(43, 8);  cout << "   Adicionar Alojamento                ";
	gotoXY(43, 9);  cout << "   Informacoes de Conta                ";
	gotoXY(43, 10); cout << "   Ver Reservas                        ";
	gotoXY(43, 11); cout << "   Consultar Taxas de Servico          ";
	gotoXY(43, 12); cout << "   Sair                                ";
	gotoXY(43, 15);

	system("pause>nul");

	if (GetAsyncKeyState(VK_RETURN)) {

		gotoXY(43, 15); cout << "  ";
	}

	while (running)
	{

		gotoXY(43, 15);

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && x < 12) //down button pressed
		{
			gotoXY(41, x); cout << "  "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); writeSuplierMenu(x);
			x++;
			gotoXY(41, x); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  "; writeSuplierMenu(x);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x > 7) //up button pressed
		{
			gotoXY(41, x); cout << "  "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); writeSuplierMenu(x);
			x--;
			gotoXY(41, x); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  "; writeSuplierMenu(x);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed

			clearScreen();

			cout << "entrei";

			switch (menu_item) {
			case 0:
				OptionSuplierShowAccomodations(comp, it);
				break;
			case 1:
				OptionSuplierAddAccomodation(comp, it);
				break;
			case 2:
				OptionSuplierInformation(comp, it);
				break;
			case 3:
				OptionSuplierReservations(comp, it);
				break;
			case 4:
				OptionSuplierShowFees(comp, it);
				break;
			case 5:
				novoMenu(comp);
			}
		}
	}
}

// ---------------------------
//   Guest Menu
// ---------------------------

void Menu::writeGuestMenu(int x) {

	switch (x)
	{
	case 7:
		cout << "   Efetuar Reserva                     ";
		break;
	case 8:
		cout << "   Cancelar Reservas                   ";
		break;
	case 9:
		cout << "   Ver Reservas                        ";
		break;
	case 10:
		cout << "   Voltar ao Menu Inicial              ";
		break;
	}
}

void Menu::OptionGuestAddAccomodation(Company & comp) {
	
	try {

		string location;
		string date;
		Date initial_date;
		Date final_date;
		Accomodation* acc;
		Reservation res;

		clearScreen();
		gotoXY(48, 4); cout << "|| Efetuar Reserva ||" << endl << endl;

		gotoXY(40, 7); cout << "Local: ";
		getline(cin, location);
		if (cin.eof()) throw InvalidInput();

		gotoXY(40, 9); cout << "Data Inicial: ";
		getline(cin, date);
		if (!initial_date.getDate(date)) throw InvalidDate();

		gotoXY(40, 10); cout << "Data Final: ";
		getline(cin, date);
		if (!final_date.getDate(date)) throw InvalidDate();

		acc = comp.displayOffers(location, initial_date, final_date);
		if (acc == NULL) guestMenu(comp);


		res.setAccomodation(acc);
		res.setCheckIN(initial_date);
		res.setCheckOUT(final_date);
		res.setClient("Nao Registado");
		res.setMarking(getCurrentDate());
		res.setID();


		comp.addReservationComp(acc, res);

		clearScreen();

		gotoXY(48, 4); cout << "|| Reserva ||" << endl << endl << endl;

		cout << "    Cliente             ID Reserva     ID Alojamento     Check IN       Check OUT      Preço     Marcacao   " << endl;
		cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
		cout << res;

		cout << endl << TAB_BIG << "A sua reserva foi criada com sucesso." << endl;
		cout << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Visitante." << endl << endl;

		pauseScreen();
		guestMenu(comp);
	}
	catch (WrongOption wp) {
		cout << wp;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Visitante." << endl;
		pauseScreen();
		guestMenu(comp);
	}
	catch (InvalidInput ii) {
		cout << ii;
		cin.clear();
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Visitante." << endl;
		pauseScreen();
		guestMenu(comp);
	}
	catch (InvalidDate id) {
		cout << id;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu  Visitante." << endl;
		pauseScreen();
		guestMenu(comp);
	}
	catch (invalid_argument) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introducao dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "Deve introduzir um numero." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Visitante." << endl;
		pauseScreen();
		guestMenu(comp);
	}
	catch (out_of_range) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introducao dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "O número introduzido ultrapassa os valores suportados." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Visitante." << endl;
		pauseScreen();
		guestMenu(comp);
	}
<<<<<<< HEAD

}

void Menu::OptionGuestCancelReservation(Company & comp) {

	try {
		comp.cancelReservation();
		pauseScreen();
		guestMenu(comp);
	}
	catch (WrongOption wp) {
		cout << wp;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Visitante." << endl;
		pauseScreen();
		guestMenu(comp);
	}
	catch (InvalidInput ii) {
		cout << ii;
		cin.clear();
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Visitante." << endl;
		pauseScreen();
		guestMenu(comp);
	}
	catch (InvalidDate id) {
		cout << id;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu  Visitante." << endl;
		pauseScreen();
		guestMenu(comp);
	}
	catch (invalid_argument) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introducao dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "Deve introduzir um numero." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Visitante." << endl;
		pauseScreen();
		guestMenu(comp);
	}
	catch (out_of_range) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introducao dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "O numero introduzido ultrapassa os valores suportados." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Visitante." << endl;
		pauseScreen();
		guestMenu(comp);
	}
}

void Menu::OptionGuestShowReservations(Company & comp) {

	comp.showReservation();
	pauseScreen();
	guestMenu(comp);

}

=======

}

void Menu::OptionGuestCancelReservation(Company & comp) {

	try {
		comp.cancelReservation();
		pauseScreen();
		guestMenu(comp);
	}
	catch (WrongOption wp) {
		cout << wp;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Visitante." << endl;
		pauseScreen();
		guestMenu(comp);
	}
	catch (InvalidInput ii) {
		cout << ii;
		cin.clear();
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Visitante." << endl;
		pauseScreen();
		guestMenu(comp);
	}
	catch (InvalidDate id) {
		cout << id;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu  Visitante." << endl;
		pauseScreen();
		guestMenu(comp);
	}
	catch (invalid_argument) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introducao dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "Deve introduzir um numero." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Visitante." << endl;
		pauseScreen();
		guestMenu(comp);
	}
	catch (out_of_range) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introducao dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "O numero introduzido ultrapassa os valores suportados." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Visitante." << endl;
		pauseScreen();
		guestMenu(comp);
	}
}

void Menu::OptionGuestShowReservations(Company & comp) {

	comp.showReservation();
	pauseScreen();
	guestMenu(comp);

}

>>>>>>> origin/master
void Menu::guestMenu(Company & comp) {

	clearScreen();
	int menu_item = 0, x = 7;
	bool running = true;

	gotoXY(48, 4); cout << "|| Menu Visitante ||";
	gotoXY(41, 7); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  " << "   Efetuar Reserva                     ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoXY(43, 8);  cout << "   Cancelar Reservas                   ";
	gotoXY(43, 9);  cout << "   Ver Reservas                        ";
	gotoXY(43, 10); cout << "   Voltar ao Menu Inicial              ";
	gotoXY(43, 15);

	system("pause>nul");

	if (GetAsyncKeyState(VK_RETURN)) {

		gotoXY(43, 15); cout << "  ";
	}

	while (running)
	{

		gotoXY(43, 15);

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && x < 10) //down button pressed
		{
			gotoXY(41, x); cout << "  "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); writeGuestMenu(x);
			x++;
			gotoXY(41, x); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  "; writeGuestMenu(x);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x > 7) //up button pressed
		{
			gotoXY(41, x); cout << "  "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); writeGuestMenu(x);
			x--;
			gotoXY(41, x); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  "; writeGuestMenu(x);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed

			switch (menu_item) {
			case 0:
				OptionGuestAddAccomodation(comp);
				break;
			case 1:
				OptionGuestCancelReservation(comp);
				break;
			case 2:
				OptionGuestShowReservations(comp);
				break;
			case 3:
				novoMenu(comp);
			}
		}
	}
}



// ---------------------------
//   Administrator Menu
// ---------------------------

void Menu::writeAdminMenu(int x) {

	switch (x)
	{
	case 7:
		cout << "   Ver Descontos                       ";
		break;
	case 8:
		cout << "   Lista de Fornecedores               ";
		break;
	case 9:
		cout << "   Lista de Clientes Inativos          ";
		break;
	case 10:
		cout << "   Lista de Clientes Ativos            ";
		break;
	case 11:
		cout << "   Lista de Reservas                   ";
		break;
	case 12:
		cout << "   Moradas para Publicidade            ";
		break;
	case 13:
		cout << "   Atualizar Moradas                   ";
		break;
	case 14:
		cout << "   Voltar ao Menu Inicial              ";
		break;
	}
}

void Menu::adminMenu(Company & comp) {

	clearScreen();

	int menu_item = 0, x = 7;
	bool running = true;


	gotoXY(48, 4); cout << "|| Menu Administrador ||";

	gotoXY(41, 7); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  " << "   Ver Descontos                   ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoXY(43, 8);  cout << "   Lista de Fornecedores               ";
	gotoXY(43, 9);  cout << "   Lista de Clientes Inativos          ";
	gotoXY(43, 10); cout << "   Lista de Clientes Ativos            ";
	gotoXY(43, 11); cout << "   Lista de Reservas                   ";
	gotoXY(43, 12); cout << "   Moradas para Publicidade            ";
	gotoXY(43, 13); cout << "   Atualizar Moradas                   ";
	gotoXY(43, 14); cout << "   Voltar ao Menu Inicial              ";

	gotoXY(43, 15);

	system("pause>nul");

	if (GetAsyncKeyState(VK_RETURN)) {

		gotoXY(43, 15); cout << "  ";
	}

	while (running)
	{

		gotoXY(43, 15);

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && x < 14) //down button pressed
		{
			gotoXY(41, x); cout << "  "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); writeAdminMenu(x);
			x++;
			gotoXY(41, x); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  "; writeAdminMenu(x);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x > 7) //up button pressed
		{
			gotoXY(41, x); cout << "  "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); writeAdminMenu(x);
			x--;
			gotoXY(41, x); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  "; writeAdminMenu(x);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed

			switch (menu_item) {
			case 0:
				clearScreen();
<<<<<<< HEAD
				comp.updateDiscounts();
=======
				comp.showDiscounts();
>>>>>>> origin/master
				pauseScreen();
				adminMenu(comp);
				break;
			case 1:
				clearScreen();
				comp.showSupliers();
				adminMenu(comp);
				break;
			case 2:
				clearScreen();
				comp.showInactiveClients();
				pauseScreen();
				adminMenu(comp);
				break;
			case 3:
				clearScreen();
				comp.showActiveClients();
				pauseScreen();
				adminMenu(comp);
			case 4:
				gotoXY(43, 16);
				comp.showReservations();
				adminMenu(comp);
				break;
			case 5:
				clearScreen();
				comp.showInactiveClientsAdresses();
				pauseScreen();
				adminMenu(comp);
				break;
			case 6:
				clearScreen();
				comp.updateAdresses();
				pauseScreen();
				adminMenu(comp);
				break;
			case 7:
				novoMenu(comp);
			}
		}
	}

	gotoXY(43, 21);


}


// ---------------------------
//   Main Menu
// ---------------------------

void Menu::logIn(Company &comp, char user) {
	clearScreen();

	string username;
	string password = "";
	char ch;
	vector<Suplier>::iterator its;
	vector<Client>::iterator itc;
	unordered_set<Client, hcli, eqcli>::iterator ith;

	gotoXY(48, 4); cout << "|| ENTRAR ||";

	gotoXY(42, 7);  cout << "Username: ";

	getline(cin, username);
	if (cin.eof()) throw InvalidInput();


<<<<<<< HEAD
	gotoXY(42, 8); cout << "1Password: ";

	password = insertPassword();
=======
	gotoXY(42, 8); cout << "Password: ";

	ch = _getch();
	while (ch != 13) {//character 13 is enter
		password.push_back(ch);
		cout << '*';
		ch = _getch();
	}

>>>>>>> origin/master

	if (cin.eof()) throw InvalidInput();

	if (user == 's') {
		its = comp.verifyLogInSup(username, password);
		suplierMenu(comp, its);
	}
	else {

		if (comp.isClientInactive(username)) {

			ith = comp.verifyInactiveCliLogin(username, password);
			clientMenuHash(comp, ith);
		}
		else {
			pauseScreen();
			itc = comp.verifyLogInCli(username, password);
			clientMenu(comp, itc);
		}
	}


	cout << TAB << "Prima qualquer tecla para voltar ao Menu Inicial." << endl << endl;

	pauseScreen();

	novoMenu(comp);

}

void Menu::OptionRegister(Company &comp, char user) {

	try
	{
		if (user == 's') comp.registerSuplier();
		else comp.registerClient();

		pauseScreen();
		mainMenu(comp, user);
	}
	catch (WrongOption wp) {
		cout << wp;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Fornecedor." << endl;
		pauseScreen();
		mainMenu(comp, user);
	}
	catch (InvalidInput ii) {
		cout << ii;
		cin.clear();
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Fornecedor." << endl;
		pauseScreen();
		mainMenu(comp, user);
	}
	catch (InvalidDate id) {
		cout << id;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Fornecedor." << endl;
		pauseScreen();
		mainMenu(comp, user);
	}
	catch (invalid_argument) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introducao dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "Deve introduzir um numero." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Fornecedor." << endl;
		pauseScreen();
		mainMenu(comp, user);
	}
	catch (out_of_range) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introdução dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "O numero introduzido ultrapassa os valores suportados." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Fornecedor." << endl;
		pauseScreen();
		mainMenu(comp, user);
	}
	catch (InvalidLogIn ili) {
		cout << ili;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Fornecedor." << endl;
		pauseScreen();
		mainMenu(comp, user);
	}
	catch (InvalidUsername iu) {
		cout << iu;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Fornecedor." << endl;
		pauseScreen();
		mainMenu(comp, user);
	}
	catch (ErrorOpeningFile eof) {
		cout << eof;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Fornecedor." << endl;
		pauseScreen();
		mainMenu(comp, user);
	}
	catch (InvalidReservationID iri) {
		cout << iri;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Fornecedor." << endl;
		pauseScreen();
		mainMenu(comp, user);
	}


	
}

void Menu::OptionLogin(Company &comp, char user) {
	
	try {
		if (user == 's')  logIn(comp, 's');
		else logIn(comp, 'c');
	}
	catch (WrongOption wp) {
		cout << wp;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Fornecedor." << endl;
		pauseScreen();
		mainMenu(comp, user);
	}
	catch (InvalidInput ii) {
		cout << ii;
		cin.clear();
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Fornecedor." << endl;
		pauseScreen();
		mainMenu(comp, user);
	}
	catch (InvalidDate id) {
		cout << id;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Fornecedor." << endl;
		pauseScreen();
		mainMenu(comp, user);
	}
	catch (invalid_argument) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introducao dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "Deve introduzir um numero." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Fornecedor." << endl;
		pauseScreen();
		mainMenu(comp, user);
	}
	catch (out_of_range) {
		cout << endl << TAB_BIG << TAB_BIG << "Erro na introducao dos dados." << endl;
		cout << TAB_BIG << TAB_BIG << "O numero introduzido ultrapassa os valores suportados." << endl;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Fornecedor." << endl;
		pauseScreen();
		mainMenu(comp, user);
	}
	catch (InvalidLogIn ili) {
		cout << ili;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Fornecedor." << endl;
		pauseScreen();
		mainMenu(comp, user);
	}
	catch (InvalidUsername iu) {
		cout << iu;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Fornecedor." << endl;
		pauseScreen();
		mainMenu(comp, user);
	}
	catch (ErrorOpeningFile eof) {
		cout << eof;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Fornecedor." << endl;
		pauseScreen();
		mainMenu(comp, user);
	}
	catch (InvalidReservationID iri) {
		cout << iri;
		cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Fornecedor." << endl;
		pauseScreen();
		mainMenu(comp, user);
	}
}

void Menu::mainMenu(Company & comp, char user) {

	clearScreen();
	int menu_item = 0, x = 7;
	bool running = true;

	gotoXY(48, 4);
	if (user == 's') cout << "|| Menu Fornecedor ||";
	else cout << "|| Menu Cliente ||";
	gotoXY(41, 7); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  " << "   Registar                    ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoXY(43, 8);  cout << "   Entrar                      ";
	gotoXY(43, 9);  cout << "   Voltar ao Menu Inicial      ";
	gotoXY(43, 15);

	system("pause>nul");

	if (GetAsyncKeyState(VK_RETURN)) {

		gotoXY(43, 15); cout << "  ";
	}

	while (running)
	{

		gotoXY(43, 15);

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && x != 9) //down button pressed
		{
			gotoXY(41, x); cout << "  "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); writeOptionMainMenu(x);
			x++;
			gotoXY(41, x); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  "; writeOptionMainMenu(x);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x != 7) //up button pressed
		{
			gotoXY(41, x); cout << "  "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); writeOptionMainMenu(x);
			x--;
			gotoXY(41, x); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  "; writeOptionMainMenu(x);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed

			switch (menu_item) {
			case 0:
				OptionRegister(comp, user);
				break;
			case 1:
				OptionLogin(comp, user);
				break;
			case 2:
				novoMenu(comp);
			}
		}
	}
}

void Menu::writeOptionMainMenu(int x) {

	switch (x)
	{
	case 7:
		cout << "   Registar                    ";
		break;
	case 8:
		cout << "   Entrar                      ";
		break;
	case 9:
		cout << "   Voltar ao Menu Inicial      ";
		break;
	}
}

void Menu::writeOptionStartMenu(int x) {

	switch (x)
	{
	case 7:
		cout << "   Menu Fornecedor             ";
		break;
	case 8:
		cout << "   Menu Cliente                ";
		break;
	case 9:
		cout << "   Menu Administrador          ";
		break;
	case 10:
		cout << "   Entrar como Visitante       ";
		break;
	case 11:
		cout << "   Sair                        ";
		break;
	}
}

void Menu::novoMenu(Company & comp){

	clearScreen();

	int menu_item = 0, x = 7;
	bool running = true;

	gotoXY(48, 4); cout << "|| MENU INICIAL ||";
	gotoXY(41, 7); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  " << "   Menu Fornecedor             ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoXY(43, 8);  cout << "   Menu Cliente                ";
	gotoXY(43, 9);  cout << "   Menu Administrador          ";
	gotoXY(43, 10); cout << "   Entrar como Visitante       ";
	gotoXY(43, 11); cout << "   Sair                        ";
	gotoXY(43, 15);

	system("pause>nul");

	if (GetAsyncKeyState(VK_RETURN)) {

		gotoXY(43, 15); cout << "  ";
	}

	while (running)
	{

		gotoXY(43, 15);

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && x != 11) //down button pressed
		{
			gotoXY(41, x); cout << "  "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); writeOptionStartMenu(x);
			x++;
			gotoXY(41, x); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  "; writeOptionStartMenu(x);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x != 7) //up button pressed
		{
			gotoXY(41, x); cout << "  "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); writeOptionStartMenu(x);
			x--;
			gotoXY(41, x); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  "; writeOptionStartMenu(x);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed

			switch (menu_item) {
			case 0:
				mainMenu(comp, 's');
				break;
			case 1: 
				mainMenu(comp, 'c');
				break;
			case 2: 
				adminMenu(comp);
				break;
			case 3: 
				guestMenu(comp);
				break;
			case 4: 
				comp.saveChanges();
				exit(1);
				break;
			}
		}
	}
	gotoXY(43, 21);
}
