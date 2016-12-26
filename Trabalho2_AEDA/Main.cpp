#include <iostream>
#include <string>
#include <vector>
#include <locale.h>

#include "Company.h"
#include "Menus.h"
#include "utils.h"


using namespace std;



int main() {

	setlocale(LC_ALL, "Portuguese");

	Company APlaceInTheSun("clients.txt", "supliers.txt", "reservations.txt");	//inicialização da nossa empresa

	try {
		novoMenu(APlaceInTheSun);
		//start(APlaceInTheSun);
	}
	catch (WrongOption wp) {
		cout << wp;
		APlaceInTheSun.saveChanges();
		cout << TAB << "Prima qualquer tecla para voltar ao Menu Inicial." << endl;
		pauseScreen();
		return main();


	}
	catch (InvalidInput ii) {
		cout << ii;
		APlaceInTheSun.saveChanges();
		cout << TAB << "Prima qualquer tecla para voltar ao Menu Inicial." << endl;
		pauseScreen();
		return main();

	}
	catch (InvalidDate id) {
		cout << id;
		APlaceInTheSun.saveChanges();
		cout << TAB << "Prima qualquer tecla para voltar ao Menu Inicial." << endl;
		pauseScreen();
		return main();
	}
	catch (invalid_argument) {
		cout << endl << TAB << "Erro na introdução dos dados." << endl;
		cout << TAB << "Deve introduzir um número." << endl;
		APlaceInTheSun.saveChanges();
		cout << TAB << "Prima qualquer tecla para voltar ao Menu Inicial." << endl;
		pauseScreen();
		return main();


	}
	catch (out_of_range) {
		cout << endl << TAB << "Erro na introdução dos dados." << endl;
		cout << TAB << "O número introduzido ultrapassa os valores suportados." << endl;
		APlaceInTheSun.saveChanges();
		cout << TAB << "Prima qualquer tecla para voltar ao Menu Inicial." << endl;
		pauseScreen();
		return main();


	}
	catch (InvalidLogIn ili) {
		cout << ili;
		APlaceInTheSun.saveChanges();
		cout << TAB << "Prima qualquer tecla para voltar ao Menu Inicial." << endl;
		pauseScreen();
		return main();

	}
	catch (InvalidUsername iu) {
		cout << iu;
		APlaceInTheSun.saveChanges();
		cout << TAB << "Prima qualquer tecla para voltar ao Menu Inicial." << endl;
		pauseScreen();
		return main();

	}
	catch (ErrorOpeningFile eof) {
		cout << eof;
		APlaceInTheSun.saveChanges();
		cout << TAB << "Prima qualquer tecla para voltar ao Menu Inicial." << endl;
		pauseScreen();
		return main();


	}
	catch (InvalidReservationID iri) {
		cout << iri;
		APlaceInTheSun.saveChanges();
		cout << TAB << "Prima qualquer tecla para voltar ao Menu Inicial." << endl;
		pauseScreen();
		return main();


	}



}
