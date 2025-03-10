#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsDepositScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTransferScreen.h"
#include "clsCurrenciesListScreen.h"
#include "clsTransfersLogScreen.h";
#include "clsFincCurrencyScreen.h";
#include "UpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
#include <iomanip>
using namespace std;

class clsCurrencyMainScreen : protected clsScreen
{
    enum enCurrenciesMenueOptions { eListCurrencies = 1, eFindCurrency, eUpdateRate, eCurrencyCalculator, eGoBackToMainMenu };

    static short _ReadCurrenciesMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }

    static  void _GoBackToCurrenciesMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Currencies Menue...\n";
        system("pause>0");
        ShowCurrencyMenue();
    }

    static void _ShowListCurrenciesScreen() {
        clsCurrenciesListScreen::ShowCurrenciesList();
    }

    static void _ShowFindCurrencyScreen() {
        clsFincCurrencyScreen::ShowFindCurrencyScreen();
    }
    static void _ShowUpdateRateScreen() {
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyScreen();
    }
    static void _ShowCurrencyCalculatorScreen() {
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }

    static void _PerfromCurrenciesMenueOption(enCurrenciesMenueOptions CurrenciesMenueOption)
    {
        switch (CurrenciesMenueOption)
        {
        case enCurrenciesMenueOptions::eListCurrencies:
        {
            system("cls");
            _ShowListCurrenciesScreen();
            _GoBackToCurrenciesMenue();
            break;
        }
        case enCurrenciesMenueOptions::eFindCurrency:
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrenciesMenue();
            break;

        case enCurrenciesMenueOptions::eUpdateRate:
            system("cls");
            _ShowUpdateRateScreen();
            _GoBackToCurrenciesMenue();
            break;

        case enCurrenciesMenueOptions::eCurrencyCalculator:
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrenciesMenue();
            break;
        case enCurrenciesMenueOptions::eGoBackToMainMenu:
            break;

        }

    }



public:


    static void ShowCurrencyMenue()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pCurrencyExchange))
            return;
        system("cls");
        _DrawScreenHeader("\t Currency Exchange Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t Currency Exchange Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Go Back To Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromCurrenciesMenueOption((enCurrenciesMenueOptions)_ReadCurrenciesMenueOption());
    }

};

