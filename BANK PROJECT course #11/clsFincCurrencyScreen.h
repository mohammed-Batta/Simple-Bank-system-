#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsUtil.h"
using namespace std;

class clsFincCurrencyScreen : protected clsScreen
{
    static void _PrintCurrency(clsCurrency & Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.getCountry();
        cout << "\nCode       : " << Currency.getCurrencyCode();
        cout << "\nName       : " << Currency.getCurrencyName();
        cout << "\nRate(1$) = : " << Currency.getRate();

        cout << "\n_____________________________\n";
    }
    enum enFindMethod {eCode = 1, eCountry = 2};
public:
    static void ShowFindCurrencyScreen() {
       
        _DrawScreenHeader("\tFind Currency Screen");

        cout << "[1] By Currency Code , [2] By Counrty Name" ;
        enFindMethod method = (enFindMethod)clsInputValidate::ReadShortNumberBetween(1, 2, "The num should be either 1 or 2");
       
        if (method == enFindMethod::eCode) {
            string code = "";
            cout << "Plz Enter Currency code : ";
            code = clsInputValidate::ReadString();
            clsCurrency currency = clsCurrency::FindByCode(code);

            if (currency.IsEmpty())
                return;

            _PrintCurrency(currency);

        }
        else {
            string counrty = "";
            cout << "Plz Enter Country : ";
            counrty = clsInputValidate::ReadString();
            clsCurrency currency = clsCurrency::FindByCounrty(counrty);

            if (currency.IsEmpty())
                return;

            _PrintCurrency(currency);
        }

       

     

    }


};

