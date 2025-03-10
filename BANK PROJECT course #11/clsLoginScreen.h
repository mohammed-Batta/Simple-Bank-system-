#pragma warning(disable : 4996)
#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "Global.h"
#include "clsMainScreen.h"
#include <fstream>
#include "clsDate.h"
using namespace std;
class clsLoginScreen : protected clsScreen
{

	
	static void _Login(){
		bool LoginFiled = false;
		string username, password;
		short trials = 3;
		do {
			if (LoginFiled) {
				cout << "\nInvlaid Username/password!";
				cout << "\nYou have " << --trials << " trials to Login !";
				
			}
			if (trials == 0) {
				cout << "\nLocked!";
				return;
			}
			cout << "Enter username : ";
			cin >> username;
			cout << "Enter Password : ";
			cin >> password;

			CurrentUser = clsUser::Find(username, password);
			LoginFiled = CurrentUser.IsEmpty();
		} while (LoginFiled);
		CurrentUser.RegisterLogin();
		clsMainScreen::ShowMainMenue();
		ShowLoginScreen();
	}

public:

	static void ShowLoginScreen() {
		system("cls");
		_DrawScreenHeader("\tLogin Screen");
		_Login();
	}
};

