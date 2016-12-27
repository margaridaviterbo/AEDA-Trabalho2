#include "Menus.h"


/*
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto

COORD CursorPosition; // used for goto


void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
*/


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
		cout << "   Informação de Conta                 ";
		break;
	case 11:
		cout << "   Sair                                ";
		break;

	}
}

void Menu::clientMenu(Company & comp, vector<Client>::iterator it) {

	clearScreen();

	// dados para efetuar reserva
	string location;
	string date;
	Date initial_date;
	Date final_date;
	Accomodation* acc;
	Reservation res;
	int id, pos;
	vector<Reservation> reservations_tmp;

	int menu_item = 0, x = 7;
	bool running = true;


	gotoXY(48, 4); cout << "||" << it->getName() << "||";

	gotoXY(41, 7); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  " << "   Efetuar Reserva                     ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoXY(43, 8);  cout << "   Ver Reservas                        ";
	gotoXY(43, 9);  cout << "   Cancelar Reservas                   ";
	gotoXY(43, 10); cout << "   Informação de Conta                 ";
	gotoXY(43, 11); cout << "   Sair                                ";
	gotoXY(43, 15);

	system("pause>nul");

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
				if (acc == NULL) break;


				res.setAccomodation(acc);
				res.setCheckIN(initial_date);
				res.setCheckOUT(final_date);
				res.setID();

				it->addReservation(res);

				clearScreen();

				gotoXY(48, 4); cout << "|| Reserva ||" << endl << endl << endl;
				
				cout << "         ID Reserva             ID Alojamento                Check IN             Check OUT             Preço         " << endl;
				cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
				cout << res;

				cout << endl << TAB_BIG << "A sua reserva foi criada com sucesso." << endl;
				cout << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Cliente." << endl << endl;

				pauseScreen();

				clientMenu(comp, it);
				break;
			case 1:
				it->showReservations();
				pauseScreen();
				clientMenu(comp, it);
				break;
			case 2:
				it->showReservations();
				id = comp.cancelReservation();
				if (id == 0) break;

				reservations_tmp = it->getReservations();
				res.setID(id);
				pos = sequentialSearch<Reservation>(reservations_tmp, res);

				it->deleteReservation(pos);
				pauseScreen();
				clientMenu(comp, it);
				break;
			case 3:
				clearScreen();
				gotoXY(48, 4); cout << "|| Informações de Conta ||" << endl << endl;
				cout << "---------------------------------------------------------------------------------------------------------------------" << endl << endl;
				cout << TAB_BIG << TAB_BIG << TAB_BIG << "                    Nome : " << it->getName() << endl;
				cout << TAB_BIG << TAB_BIG << TAB_BIG << "      Nome de Utilizador : " << it->getUsername() << endl;
				cout << TAB_BIG << TAB_BIG << TAB_BIG << "                  Pontos : " << it->getPoints() << endl << endl;
				cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
				pauseScreen();
				clientMenu(comp, it);
				break;
			case 4:
				novoMenu(comp);
				break;
			}
		}
	}





	/*
	cout << endl << TAB_BIG << "|| " << it->getUsername() << " ||" << endl << endl;
	cout << endl << TAB << "| 1 |  Efetuar Reserva" << endl;
	cout << endl << TAB << "| 2 |  Ver Reservas" << endl;
	cout << endl << TAB << "| 3 |  Cancelar Reservas" << endl;
	cout << endl << TAB << "| 4 |  Informações de Conta" << endl;
	cout << endl << TAB << "| 5 |  Sair" << endl;

	option_int = showOptions(1, 5);

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

	*/

	cout << TAB << "Prima qualquer tecla para voltar ao Menu Cliente." << endl << endl;

	pauseScreen();

	clientMenu(comp, it);


}

void Menu::logIn(Company &comp, char user) {
	clearScreen();

	string username;
	string password = "";
	char ch;
	vector<Suplier>::iterator its;
	vector<Client>::iterator itc;


	gotoXY(48, 4); cout << "|| ENTRAR ||";

	gotoXY(42, 7);  cout << "Username: ";

	getline(cin, username);
	if (cin.eof()) throw InvalidInput();


	gotoXY(42, 8); cout << "Password: ";

	ch = _getch();
	while (ch != 13) {//character 13 is enter
		password.push_back(ch);
		cout << '*';
		ch = _getch();
	}


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

	novoMenu(comp);

}

void Menu::mainMenu2(Company & comp, char user) {
	
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
				if (user == 's') comp.registerSuplier();
				else comp.registerClient();

				pauseScreen();
				mainMenu2(comp, user);
				break;
			case 1:
				if (user == 's')  logIn(comp, 's');
				else logIn(comp, 'c');
				break;
			case 2:
				novoMenu(comp);
			}
		}
	}

	gotoXY(43, 21);


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

void Menu::mainMenu(Company & comp, char user) {
	clearScreen();

	string option_str;
	unsInt option_int;


	if (user == 's') cout << endl << TAB_BIG << "|| Menu Fornecedor ||" << endl << endl;
	else cout << endl << TAB_BIG << "|| Menu Cliente ||" << endl << endl;
	cout << endl << TAB << "| 1 |  Registar" << endl;
	cout << endl << TAB << "| 2 |  Entrar" << endl;
	cout << endl << TAB << "| 3 |  Voltar ao Menu Inicial" << endl;

	option_int = showOptions(1, 3);

	switch (option_int) {
	case 1:
		if (user == 's') comp.registerSuplier();
		else comp.registerClient();

		pauseScreen();
		mainMenu(comp, user);
		break;
	case 2:
		if (user == 's')  logIn(comp, 's');
		else logIn(comp, 'c');
		break;
	case 3:
		start(comp);
	}

}

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
		cout << "   Informações de Conta                ";
		break;
	case 10:
		cout << "   Ver Reservas                        ";
		break;
	case 11:
		cout << "   Consultar Taxas de Serviço          ";
		break;
	case 12:
		cout << "   Sair                                ";
		break;
	}
}

void Menu::suplierMenu(Company & comp, vector<Suplier>::iterator it) {

	clearScreen();

	int menu_item = 0, x = 7;
	bool running = true;
	string add;

	//cin.clear();
	//cin.ignore(256, '\n');


	gotoXY(48, 4); cout << "|| " << it->getUsername() << " ||";

	gotoXY(41, 7); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  " << "   Ver Alojamentos                     ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoXY(43, 8);  cout << "   Adicionar Alojamento                ";
	gotoXY(43, 9);  cout << "   Informações de Conta                ";
	gotoXY(43, 10); cout << "   Ver Reservas                        ";
	gotoXY(43, 11); cout << "   Consultar Taxas de Serviço          ";
	gotoXY(43, 12); cout << "   Sair                                ";
	//gotoXY(43, 15);

	system("pause>nul");

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

			switch (menu_item) {
			case 0:
				it->showAccomodations();
				pauseScreen();
				//running = false;
				suplierMenu(comp, it);
				break;
			case 1:
				add = "s";
				while (add == "s") {
					it->addAccomodation2();

					cout << endl << TAB << "Adicionar Alojamento (s/n)? ";
					getline(cin, add);

				}

				if (add != "n") throw InvalidInput();


				clearScreen();
				gotoXY(48, 4); cout << "|| Adicionar Alojamento ||" << endl << endl;
				gotoXY(35, 10); cout << "Os seus alojamentos foram atualizados com sucesso!" << endl;
				pauseScreen();
				suplierMenu(comp, it);
				break;
			case 2:
				clearScreen();
				gotoXY(48, 4); cout << "|| Informações de Conta ||" << endl << endl;
				cout << "---------------------------------------------------------------------------------------------------------------------" << endl << endl;
				cout << TAB_BIG << TAB_BIG << TAB_BIG << "                    Nome : " << it->getName() << endl;
				cout << TAB_BIG << TAB_BIG << TAB_BIG << "      Nome de Utilizador : " << it->getUsername() << endl;
				cout << TAB_BIG << TAB_BIG << TAB_BIG << "                     NIF : " << it->getNIF() << endl;
				cout << TAB_BIG << TAB_BIG << TAB_BIG << "                  Morada : " << it->getAdress() << endl << endl;
				cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
				pauseScreen();
				//running = false;
				suplierMenu(comp, it);
				break;
			case 3:
				it->showReservations();
				pauseScreen();
				//running = false;
				suplierMenu(comp, it);
				break;
			case 4:
				clearScreen();
				it->showFees();
				pauseScreen();
				//running = false;
				suplierMenu(comp, it);
				break;
			case 5:
				novoMenu(comp);
				//running = false;
			}
		}
	}


}

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

void Menu::guestMenu(Company & comp) {


	// dados para efetuar reserva
	string location;
	string date;
	Date initial_date;
	Date final_date;
	Accomodation* acc;
	Reservation res;

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

				clearScreen();
				gotoXY(48, 4); cout <<  "|| Efetuar Reserva ||" << endl << endl;

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
				if (acc == NULL) break;

				res.setAccomodation(acc);
				res.setCheckIN(initial_date);
				res.setCheckOUT(final_date);
				res.setID();

				clearScreen();

				gotoXY(48, 4); cout << "|| Reserva ||" << endl << endl << endl;

				cout << "         ID Reserva             ID Alojamento                Check IN             Check OUT             Preço         " << endl;
				cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
				cout << res;

				cout << endl << TAB_BIG << "A sua reserva foi criada com sucesso." << endl;
				cout << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Cliente." << endl << endl;
			
				pauseScreen();
				guestMenu(comp);
				break;
			case 1:
				comp.cancelReservation();
				pauseScreen();
				guestMenu(comp);
				break;
			case 2:
				comp.showReservation();
				pauseScreen();
				guestMenu(comp);
				break;
			case 3:
				novoMenu(comp);
			}
		}
	}

	
	cout << TAB << "Prima qualquer tecla para voltar ao Menu." << endl << endl;

	pauseScreen();

	guestMenu(comp);


}

void Menu::writeAdminMenu(int x) {

	switch (x)
	{
	case 7:
		cout << "   Aplicar Descontos                   ";
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
		cout << "   Voltar ao Menu Inicial              ";
		break;
	}
}

void Menu::adminMenu(Company & comp) {

	clearScreen();

	int menu_item = 0, x = 7;
	bool running = true;


	gotoXY(48, 4); cout << "|| Menu Administrador ||";

	gotoXY(41, 7); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  " << "   Aplicar Descontos                   ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoXY(43, 8);  cout << "   Lista de Fornecedores               ";
	gotoXY(43, 9);  cout << "   Lista de Clientes Inativos          ";
	gotoXY(43, 10); cout << "   Lista de Clientes Ativos            ";
	gotoXY(43, 11); cout << "   Lista de Reservas                   ";
	gotoXY(43, 12); cout << "   Voltar ao Menu Inicial              ";
	gotoXY(43, 15);

	system("pause>nul");

	while (running)
	{

		gotoXY(43, 15);

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && x < 12) //down button pressed
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
				gotoXY(43, 16);
				cout << "Opcao 1";
				break;
			case 1:
				gotoXY(43, 16);
				cout << "Opcao 2";
				break;
			case 2:
				gotoXY(43, 16);
				cout << "Opcao 3";
				break;
			case 3:
				gotoXY(43, 16);
				cout << "Opcao 4";
				break;
			case 4:
				gotoXY(43, 16);
				cout << "Opcao 5";
				break;
			case 5:
				novoMenu(comp);
			}
		}
	}

	gotoXY(43, 21);


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

	exit = 0;

	gotoXY(48, 4); cout << "|| MENU INICIAL ||";
	gotoXY(41, 7); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "  " << "   Menu Fornecedor             ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoXY(43, 8);  cout << "   Menu Cliente                ";
	gotoXY(43, 9);  cout << "   Menu Administrador          ";
	gotoXY(43, 10); cout << "   Entrar como Visitante       ";
	gotoXY(43, 11); cout << "   Sair                        ";
	gotoXY(43, 15);

	system("pause>nul");

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
				mainMenu2(comp, 's');
				break;
			case 1: 
				mainMenu2(comp, 'c');
				break;
			case 2: 
				adminMenu(comp);
				break;
			case 3: 
				guestMenu(comp);
				break;
			case 4: 
				exit = 1;
				comp.saveChanges();
				//exit = 1;
				
			}
		}
	}

	gotoXY(43, 21);

}

void Menu::start(Company & comp) {
	string option_str;
	unsInt option_int;

	clearScreen();

	cout << endl << TAB_BIG << "|| MENU INICIAL ||" << endl << endl;
	cout << endl << TAB << "| 1 |  Menu Fornecedor" << endl;
	cout << endl << TAB << "| 2 |  Menu Cliente" << endl;
	cout << endl << TAB << "| 3 |  Entrar como Visitante" << endl;
	cout << endl << TAB << "| 4 |  Sair" << endl << endl;
	/*
	cout << endl << TAB<< "Opção: ";

	getline(cin, option_str);

	option_int = stoi(option_str);

	if (option_int < 1 || option_int >4) throw WrongOption(1, 4);
	*/
	option_int = showOptions(1, 4);

	switch (option_int) {
	case 1:
		mainMenu(comp, 's');
		break;
	case 2:
		mainMenu(comp, 'c');
		break;
	case 3:
		guestMenu(comp);
		break;
	case 4:
		comp.saveChanges();
		exit = 1;
	}


}