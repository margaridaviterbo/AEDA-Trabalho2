#pragma once

#include <iostream>
#include <string>



#include "defs.h"
#include "utils.h"
#include "Company.h"



using namespace std;


void start(Company & comp);
void clientMenu(Company & comp, vector<Client>::iterator it);
void logIn(Company &comp, char user);
void mainMenu(Company & comp, char user);
void guestMenu(Company & comp);
void suplierMenu(Company & comp, vector<Suplier>::iterator it);
