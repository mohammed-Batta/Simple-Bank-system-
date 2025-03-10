#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsAddNewClientScreen.h"
#include "clsBankClient.h"
#include "clsClientListScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsTransactionsScreen.h"
#include"clsUpdateClientScreen.h"
#include "clsManageUsersScreen.h"
#include "clsFindClientScreen.h"
#include "Global.h"
#include "clsLoginRegisterScreen.h"
#include "clsUser.h"
#include "clsCurrencyMainScreen.h"
#include <iomanip>
using namespace std;

class clsMainScreen : protected clsScreen
{
	enum enMainMenueOptions {
		eListClient = 1 , eAddNewClient ,eDeleteClient,eUpdateClient,eFindClient,
		eShowTransactionsMenu,eManageUsers,eLoginRegisterScreen,eCurrencyExchange,eExit
	};

    static short _ReadMainMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 10, "Enter Number between 1 to 10? ");
        return Choice;
    }

    static  void _GoBackToMainMenue()
    {
        system("pause");
        ShowMainMenue();
    }



    static void _ShowAllClientsScreen()
    {
        clsClientListScreen::ShowClientsList();
        

    }

    static void _ShowAddNewClientsScreen()
    {
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenue()
    {
        clsTransactionsScreen::ShowTransactionsMenue();
    }

    static void _ShowManageUsersMenue()
    {
        clsManageUsersScreen::ShowManageUsersMenue();
    }

    static void _Logout()
    {
        CurrentUser = clsUser::Find("","");
    }
    static void _ShowLoginRegisterScreen() {
        clsLoginRegisterScreen::ShowLoginRegisterList();
    }

    static void _ShowCurrencyMainScreen() {
        clsCurrencyMainScreen::ShowCurrencyMenue();
    }

    static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
    {
        switch (MainMenueOption)
        {
        case enMainMenueOptions::eListClient:
        {
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOptions::eAddNewClient:
            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eShowTransactionsMenu:
            system("cls");
            _ShowTransactionsMenue();
            _GoBackToMainMenue();

            break;

        case enMainMenueOptions::eManageUsers:
            system("cls");
            _ShowManageUsersMenue();
            _GoBackToMainMenue();

            break;

        case enMainMenueOptions::eLoginRegisterScreen:
            system("cls");
            _ShowLoginRegisterScreen();
            _GoBackToMainMenue();

            break;

        case enMainMenueOptions::eCurrencyExchange:
            system("cls");
            _ShowCurrencyMainScreen();
            _GoBackToMainMenue();

            break;

        case enMainMenueOptions::eExit:
            system("cls");
            _Logout();
            //Login();

            break;
        }

    }



public:


    static void ShowMainMenue()
    {

        system("cls");
        _DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[01] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[02] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[03] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[04] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[05] Find Client.\n";
        cout << setw(37) << left << "" << "\t[06] Transactions.\n";
        cout << setw(37) << left << "" << "\t[07] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[08] Login Register.\n";
        cout << setw(37) << left << "" << "\t[09] Currency Exchange.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
    }
};

