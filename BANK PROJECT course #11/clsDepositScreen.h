#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include "clsBankClient.h"
#include <iomanip>
using namespace std;

class clsDepositScreen : protected clsScreen
{

    static void _PrintClientCard(clsBankClient& client) {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirsName     :" << client.firstName;
        cout << "\nLastName     :" << client.LastName;
        cout << "\nEmail        :" << client.email;
        cout << "\nPhone         :" << client.phone;
        cout << "\nAcc. Number   :" << client.getAccountNumber();
        cout << "\nPassword      :" << client.PinCode;
        cout << "\nBalance       :" << client.AccountBalance;
        cout << "\n___________________\n";

    }

public:

    static void ShowDepositScreen() {
        _DrawScreenHeader("\t Deposit Screen");
        string AccountNumber = "";

        cout << "Plz Enter Account number : ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExists(AccountNumber)) {

            cout << "Account number is not found  : enter : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient client = clsBankClient::Find(AccountNumber);
        _PrintClientCard(client);
        cout << "Please enter deposit Amount : ";
        double amount = clsInputValidate::ReadDblNumber();

        cout << "Are u sure u wanna Add " <<  amount << " in the account ?" ;
        char Answer = 'n';
        cin >> Answer;
        if (tolower(Answer) == 'y') {

            if (client.Deposit(amount)) {
                cout << "Amount Added succssflly to this client !";
                _PrintClientCard(client);

            }
            else
                cout << "ERORR";
        }
    }



};

