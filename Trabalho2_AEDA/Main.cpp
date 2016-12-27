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

	
	Menu m;

	while (1) {

		try {
			
			m.novoMenu(APlaceInTheSun);

		}
		catch (WrongOption wp) {
			cout << wp;
			APlaceInTheSun.saveChanges();
			cout << TAB << "Prima qualquer tecla para voltar ao Menu Inicial." << endl;
			pauseScreen();
		


		}
		catch (InvalidInput ii) {
			cout << ii;
			APlaceInTheSun.saveChanges();
			cin.clear();
			cout << TAB << "Prima qualquer tecla para voltar ao Menu Inicial." << endl;
			pauseScreen();
			

		}
		catch (InvalidDate id) {
			cout << id;
			APlaceInTheSun.saveChanges();
			cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Inicial." << endl;
			pauseScreen();
		
		}
		catch (invalid_argument) {
			cout << endl << TAB_BIG << TAB_BIG << "Erro na introdução dos dados." << endl;
			cout << TAB_BIG << TAB_BIG << "Deve introduzir um número." << endl;
			APlaceInTheSun.saveChanges();
			cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Inicial." << endl;
			pauseScreen();
		


		}
		catch (out_of_range) {
			cout << endl << TAB_BIG << TAB_BIG << "Erro na introdução dos dados." << endl;
			cout << TAB_BIG << TAB_BIG << "O número introduzido ultrapassa os valores suportados." << endl;
			APlaceInTheSun.saveChanges();
			cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Inicial." << endl;
			pauseScreen();
		


		}
		catch (InvalidLogIn ili) {
			cout << ili;
			APlaceInTheSun.saveChanges();
			cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Inicial." << endl;
			pauseScreen();
		

		}
		catch (InvalidUsername iu) {
			cout << iu;
			APlaceInTheSun.saveChanges();
			cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Inicial." << endl;
			pauseScreen();
			

		}
		catch (ErrorOpeningFile eof) {
			cout << eof;
			APlaceInTheSun.saveChanges();
			cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Inicial." << endl;
			pauseScreen();
		


		}
		catch (InvalidReservationID iri) {
			cout << iri;
			APlaceInTheSun.saveChanges();
			cout << TAB_BIG << TAB_BIG << "Prima qualquer tecla para voltar ao Menu Inicial." << endl;
			pauseScreen();
			

		}

	}

	

}
