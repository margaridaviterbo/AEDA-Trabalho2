#include <iostream>
#include <string>
#include <vector>
#include <locale.h>

#include "Company.h"
#include "Menus.h"
#include "utils.h"


using namespace std;



int main(){

	setlocale(LC_ALL, "Portuguese");
	


		try{
			Company APlaceInTheSun("clients.txt", "supliers.txt","reservations.txt");	//inicialização da nossa empresa
			start(APlaceInTheSun);
		}
		catch (WrongOption wp){
			cout << wp;
			system("Pause");
		}
		catch (InvalidInput ii){
			cout << ii;
			system("Pause");
		}
		catch (InvalidDate id){
			cout << id;
			system("Pause");
		}
		catch (invalid_argument){
			cout << endl << TAB << "Erro na introdução dos dados." << endl;
			cout << TAB << "Deve introduzir um número." << endl;
			system("Pause");
		}
		catch (out_of_range){
			cout << endl << TAB << "Erro na introdução dos dados." << endl;
			cout << TAB << "O número introduzido ultrapassa os valores suportados." << endl;
			system("Pause");
		}
		catch (InvalidLogIn ili) {
			cout << ili;
			system("Pause");
		}
		catch (InvalidUsername iu) {
			cout << iu;
			system("Pause");
		}
		catch (ErrorOpeningFile eof) {
			cout << eof;
			system("Pause");
		}
		catch (InvalidReservationID iri) {
			cout << iri;
			system("Pause");
		}
	


	}
