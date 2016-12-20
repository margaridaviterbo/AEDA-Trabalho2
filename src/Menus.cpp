#include "Menus.h"


void clientMenu(Company & comp, vector<Client>::iterator it) {

	clearScreen();

	string option_str;
	int option_int;

	// dados para efetuar reserva
	string location;
	string date;
	Date initial_date;
	Date final_date;
	Accomodation* acc;
	Reservation res;
	int id, pos;
	vector<Reservation> reservations_tmp;


	cout << endl << TAB_BIG << "|| " << it->getUsername() << " ||" << endl << endl;
	cout << TAB << "1 - Efetuar Reserva" << endl;
	cout << TAB << "2 - Ver Reservas" << endl;
	cout << TAB << "3 - Cancelar Reservas" << endl;   
	cout << TAB << "4 - Informações de Conta" << endl;
	cout << TAB << "5 - Sair" << endl;

	cout << endl << TAB << "Opção: ";

	getline(cin, option_str);

	option_int = stoi(option_str);

	if (option_int < 1 || option_int >5) throw WrongOption(1, 5);

	switch (option_int) {
	case 1:
		clearScreen();
	
		cout << endl << TAB_BIG << "|| Efetuar Reserva ||" << endl << endl;

		cout << TAB << "Local: ";
		getline(cin, location);
		if (cin.eof()) throw InvalidInput();

		cout << TAB << "Data Inicial: ";
		getline(cin, date);
		if (!initial_date.getDate(date)) throw InvalidDate();

		cout << TAB << "Data Final: ";
		getline(cin, date);
		if (!final_date.getDate(date)) throw InvalidDate();

		acc = comp.displayOffers(location, initial_date, final_date);
		if (acc == NULL) break;

		
		res.setAccomodation(acc);
		res.setCheckIN(initial_date);
		res.setCheckOUT(final_date);
		res.setID();

		it->addReservation(res);

		clearScreen();

		cout << endl << TAB_BIG << "|| Reserva ||" << endl << endl;
		cout << res;
		//cout da reserva

		cout << endl << TAB << "A sua reserva foi criada com sucesso." << endl;
		cout << TAB << "Prima qualquer tecla para voltar ao Menu Cliente." << endl << endl;

		pauseScreen();

		clientMenu(comp, it);
		break;
	case 2:
		it->showReservations();
		break;

	case 3:
		it->showReservations();
		id = comp.cancelReservation();
		if (id == 0) break;

		reservations_tmp = it->getReservations();
		res.setID(id);
		pos = sequentialSearch<Reservation>(reservations_tmp, res);

		it->deleteReservation(pos);

		break;
	case 4:
		clearScreen();
		cout << endl << TAB_BIG << "|| INFORMAÇÕES DA CONTA ||" << endl << endl;
		cout << TAB << "Nome: " << it->getName() << endl;
		cout << TAB << "Nome de Utilizador: " << it->getUsername() << endl;
		cout << TAB << "Pontos: " << it->getPoints() << endl << endl;

		break;
	case 5:
		//exit(1);  
		start(comp);
		break;
	}

	cout << TAB << "Prima qualquer tecla para voltar ao Menu Cliente." << endl << endl;

	pauseScreen();

	clientMenu(comp, it);


}

void logIn(Company &comp, char user) {
	clearScreen();

	string username;
	string password;
	vector<Suplier>::iterator its;
	vector<Client>::iterator itc;

	cout << endl << TAB_BIG << "|| ENTRAR ||" << endl << endl;

	cout << TAB << "Username: ";

	getline(cin, username);
	if (cin.eof()) throw InvalidInput();


	cout << TAB << "Password: ";

	getline(cin, password);
	if (cin.eof()) throw InvalidInput();

	if (user == 's') {
		its = comp.verifyLogInSup(username, password);
		suplierMenu(comp, its);
	}
	else {
		itc = comp.verifyLogInCli(username, password);
		clientMenu(comp, itc);
	}


	cout << TAB << "Prima qualquer tecla para voltar ao Menu Inicial." << endl << endl;

	pauseScreen();

	start(comp);

}



void mainMenu(Company & comp, char user) {
	clearScreen();

	string option_str;
	unsInt option_int;


	if(user== 's') cout << endl << TAB_BIG << "|| Menu Fornecedor ||" << endl << endl;
	else cout << endl << TAB_BIG << "|| Menu Cliente ||" << endl << endl;
	cout << endl << TAB << "| 1 |  Registar" << endl;
	cout << endl << TAB << "| 2 |  Entrar" << endl;
	cout << endl << TAB << "| 3 |  Voltar ao Menu Inicial" << endl;

	cout << endl << TAB << "Opção: ";

	getline(cin, option_str);

	option_int = stoi(option_str);

	if (option_int < 1 || option_int >3) throw WrongOption(1, 3);


	switch (option_int) {
	case 1:
		if(user== 's') comp.registerSuplier();
		else comp.registerClient();

		pauseScreen();
		mainMenu(comp,user);
		break;
	case 2:
		if (user == 's')  logIn(comp, 's');
		else logIn(comp, 'c');
		break;
	case 3:
		start(comp);
	}

}

void suplierMenu(Company & comp, vector<Suplier>::iterator it){

	clearScreen();

	string option_str;
	int option_int;
	string add;
	//cout << endl << TAB << "| 1 |  Menu Fornecedor" << endl;

	cout  << endl << TAB_BIG << "|| " << it->getUsername() << " ||" << endl << endl;
	cout << endl << TAB << "| 1 |  Ver Alojamentos" << endl;
	cout << endl << TAB << "| 2 |  Adicionar Alojamento" << endl;
	cout << endl << TAB << "| 3 |  Informações de Conta" << endl;
	cout << endl << TAB << "| 4 |  Ver Reservas" << endl;
	cout << endl << TAB << "| 5 |  Consultar Taxas de Serviço" << endl;
	cout << endl << TAB << "| 6 |  Sair" << endl;

	cout << endl << TAB << "Opção: ";

	getline(cin, option_str);

	option_int = stoi(option_str);

	if (option_int < 1 || option_int >6) throw WrongOption(1, 6);

	switch (option_int) {
	case 1:
		it->showAccomodations();
		break;

	case 2:
		add = "s";
		while (add == "s") {
			it->addAccomodation();

			cout << endl << TAB << "Adicionar Alojamento (s/n)? ";
			getline(cin, add);

		}

		if (add != "n") throw InvalidInput();
		

		clearScreen();
		cout << TAB << "Os seus alojamentos foram atualizados com sucesso!" << endl;
		break;

	case 3:
		clearScreen();
		cout << endl << TAB_BIG << "|| Informações de Conta ||" << endl << endl;
		cout << TAB << "| Nome | " << it->getName() << endl;
		cout << TAB << "| Nome de Utilizador | " << it->getUsername() << endl;
		cout << TAB << "| NIF | " << it->getNIF() << endl;
		cout << TAB << "| Morada | " << it->getAdress() << endl << endl;

		break;

	case 4:
		it->showReservations();
		break;
	case 5:
		clearScreen();
		it->showFees();
		break;
	case 6:
		start(comp);
	}

	cout << TAB << "Prima qualquer tecla para voltar ao Menu Fornecedor." << endl << endl;

	pauseScreen();

	suplierMenu(comp, it);

}

void guestMenu(Company & comp) {
	string option_str;
	unsInt option_int;

	// dados para efetuar reserva
	string location;
	string date;
	Date initial_date;
	Date final_date;
	Accomodation* acc;
	Reservation res;

	clearScreen();

	cout << TAB_BIG << "|| Menu ||" << endl << endl;
	cout << TAB << "1 - Efetuar Reserva" << endl;
	cout << TAB << "2 - Cancelar Reserva" << endl;
	cout << TAB << "3 - Ver Reserva" << endl;
	cout << TAB << "4 - Voltar ao Menu Inicial" << endl;

	cout << endl << TAB << "Opção: ";

	getline(cin, option_str);

	option_int = stoi(option_str);

	if (option_int < 1 || option_int >4) throw WrongOption(1, 4);

	clearScreen();

	switch(option_int) {
	case 1:
		
		cout << TAB_BIG << "|| Eftuar Reserva ||" << endl << endl;

		cout << TAB << "Local: ";
		getline(cin, location);
		if (cin.eof()) throw InvalidInput();

		cout << TAB << "Data Inicial: ";
		getline(cin, date);
		if (!initial_date.getDate(date)) throw InvalidDate();

		cout << TAB << "Data Final: ";
		getline(cin, date);
		if (!final_date.getDate(date)) throw InvalidDate();

		acc = comp.displayOffers(location, initial_date, final_date);
		if (acc == NULL) break;

		res.setAccomodation(acc);
		res.setCheckIN(initial_date);
		res.setCheckOUT(final_date);
		res.setID();


		clearScreen();

		cout << TAB_BIG << "|| Reserva ||" << endl << endl;
		cout << res;


		cout << endl << TAB << "A sua reserva foi criada com sucesso." << endl;
		cout << endl << TAB << "É importante que guarde o id da sua reserva para poder fazer alterações futuras." << endl;
	
		break;
	case 2:
		 comp.cancelReservation();
		break;
	case 3:
		comp.showReservation();
		break;
	case 4:
		start(comp);
	}
	cout << TAB << "Prima qualquer tecla para voltar ao Menu." << endl << endl;

	pauseScreen();

	guestMenu(comp);


}


void start(Company & comp) { 
	string option_str;
	unsInt option_int;

	clearScreen();

	cout << endl << TAB_BIG << "|| MENU INICIAL ||" << endl << endl;
	cout << endl << TAB << "| 1 |  Menu Fornecedor" << endl;
	cout << endl << TAB << "| 2 |  Menu Cliente" << endl;
	cout << endl << TAB << "| 3 |  Entrar como Visitante" << endl;
	cout << endl << TAB << "| 4 |  Sair" << endl << endl;

	cout << endl << TAB<< "Opção: ";

	getline(cin, option_str);

	option_int = stoi(option_str);

	if (option_int < 1 || option_int >4) throw WrongOption(1, 4);



	switch (option_int){
	case 1:
		mainMenu(comp,'s');
		break;
	case 2:
		mainMenu(comp, 'c');
		break;
	case 3:
		guestMenu(comp);
		break;
	case 4:
		comp.saveChanges();
		exit(1);
	}


}