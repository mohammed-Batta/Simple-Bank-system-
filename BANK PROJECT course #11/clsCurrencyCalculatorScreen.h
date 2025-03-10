#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsUtil.h"
using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen
{
    static void _PrintCurrency(clsCurrency& Currency,string Title)
    {
        cout << Title << endl;
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.getCountry();
        cout << "\nCode       : " << Currency.getCurrencyCode();
        cout << "\nName       : " << Currency.getCurrencyName();
        cout << "\nRate(1$) = : " << Currency.getRate();

        cout << "\n_____________________________\n";
    }

    static clsCurrency GetCurrecny() {
        string code = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExists(code)) {

            cout << "Currency code is not found  : enter : ";
            code = clsInputValidate::ReadString();
        }
        return clsCurrency::FindByCode(code);
    }

    static void ConvertCurrencies(clsCurrency currencyFrom, clsCurrency currencyTo,float ExchangeAmout = 1) {
        _PrintCurrency(currencyFrom, "Convert From:");
        float AmountInUSD = currencyFrom.ConvertToUSD(ExchangeAmout);
        cout << endl << ExchangeAmout << currencyFrom.getCurrencyCode() << " = " << AmountInUSD << currencyTo.getCurrencyCode() << endl;

        if (currencyTo.getCurrencyCode() == "USD")
            return;
        else {
            cout << endl << "Converting from USD TO : " << endl;
            _PrintCurrency(currencyTo, "TO:");
            float AmountInOther = currencyFrom.ConvertToOtherCurrency(ExchangeAmout,currencyTo);
            cout << endl << ExchangeAmout << currencyFrom.getCurrencyCode() << " = " << AmountInOther << currencyTo.getCurrencyCode() << endl;

        }
    }
public:
    static void ShowCurrencyCalculatorScreen() {

        char ConverMore = 'y';

        while (tolower(ConverMore) == 'y') {
        system("cls");
        _DrawScreenHeader("\tCurrency Calculator Screen");
        cout << "Plz Enter Currency 1 code : ";
        clsCurrency currency1 = GetCurrecny();
        cout << "Plz Enter Currency 2 code : ";
        clsCurrency currency2 = GetCurrecny();
        cout << "Enter Amount to Exchange : ";
        float amount;
        cin >> amount;
         ConvertCurrencies(currency1, currency2, amount);
         cout << "\n MOre ? Y,N :: ";
         cin >> ConverMore;
        }
    }


};



