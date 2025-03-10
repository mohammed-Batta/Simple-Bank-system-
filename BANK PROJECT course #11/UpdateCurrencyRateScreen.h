#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsUtil.h"
using namespace std;


class clsUpdateCurrencyRateScreen : protected clsScreen
{

    static void _PrintCurrency(clsCurrency& Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.getCountry();
        cout << "\nCode       : " << Currency.getCurrencyCode();
        cout << "\nName       : " << Currency.getCurrencyName();
        cout << "\nRate(1$) = : " << Currency.getRate();

        cout << "\n_____________________________\n";
    }

public:
    static void ShowUpdateCurrencyScreen() {
        _DrawScreenHeader("\tUpdate Currency Screen");
        string code = "";

        cout << "Plz Enter Currency code : ";
        code = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExists(code)) {

            cout << "Currency code is not found  : enter : ";
            code = clsInputValidate::ReadString();
        }

        clsCurrency currency = clsCurrency::FindByCode(code);
        _PrintCurrency(currency);

        cout << "Are u sure u wanna update this Currency Rate : ";
        char answer = 'n';
        cin >> answer;

        if (tolower(answer) != 'y') {
            return;
        }

        cout << "\n\nUpdate Currency Rate:";
        cout << "\n_______________________\n";
        cout << "Enter new Rate";
        currency.Rate = clsInputValidate::ReadDblNumber();
        cout << "Account Updates sucssuflly :-)\n";
        _PrintCurrency(currency);
           


    }
};

