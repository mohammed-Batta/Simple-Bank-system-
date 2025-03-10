#pragma once
#include<iostream>
#include"clsScreen.h"
#include "clsCurrency.h"
#include "clsUser.h"
#include <iomanip>
using namespace std;

class clsCurrenciesListScreen : protected clsScreen
{

    static void PrintCurrencyRecordLine(clsCurrency& currency) {
        cout << '|' << setw(30) << left << currency.getCountry() <<
            '|' << setw(5) << left << currency.getCurrencyCode() <<
            '|' << setw(30) << left << currency.getCurrencyName() <<
            '|' << setw(14) << left << currency.Rate ;
        cout << '\n';
    }

public:
    static void ShowCurrenciesList() {

        vector<clsCurrency> vData = clsCurrency::GetCurrenciesList();
        string subtitle = to_string(vData.size());
        _DrawScreenHeader("\tCurrencies List Screen", "\t(" + subtitle + ") Currency.");

        cout << "------------------------------------------------------------------------------------------------------------------------\n";
        cout << '|' << setw(30) << left << "Country" <<
            '|' << setw(5) << left << "Code" <<
            '|' << setw(30) << left << "Name" <<
            '|' << setw(14) << left << "Rate/(1$)";
        cout << '\n';
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
        for (clsCurrency& currency : vData)
        {
            PrintCurrencyRecordLine(currency);
        }
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
    }
};

