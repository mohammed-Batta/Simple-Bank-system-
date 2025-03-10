#pragma once
#include<iostream>
#include"clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>
using namespace std;

class clsTransferScreen : protected clsScreen
{
    static void _PrintClientCard(clsBankClient& client) {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFullName      :" << client.FullName();
        cout << "\nAcc. Number   :" << client.getAccountNumber();
        cout << "\nBalance       :" << client.AccountBalance;
        cout << "\n___________________\n";

    }

public:

	static void ShowTransferScreen() {
		_DrawScreenHeader("\t Transfer Screen.");
        string AccountNumber = "";

        cout << "Plz Enter Account number To Transfer From: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExists(AccountNumber)) {

            cout << "Account number is NOT found  : enter another one : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient clientToTransferFrom = clsBankClient::Find(AccountNumber);
        _PrintClientCard(clientToTransferFrom);
        cout << "\n\nPlz Enter Account number To Transfer TO: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExists(AccountNumber)) {

            cout << "Account number is NOT found  : enter another one : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient clientToTransferTo = clsBankClient::Find(AccountNumber);
        _PrintClientCard(clientToTransferTo);
        cout << "Please enter Transfer Amount : ";
        double amount = clsInputValidate::ReadDblNumber();

        while (amount > clientToTransferFrom.AccountBalance) {
            cout << "\n Amount Exceeded the Balance : enter another : ";
            amount = clsInputValidate::ReadDblNumber();
        }

        cout << "Are u sure u wanna Preform this OP  ?";
        char Answer = 'n';
        cin >> Answer;
        if (tolower(Answer) == 'y') {

            if (clientToTransferFrom.Transfer(amount,clientToTransferTo)) {
                cout << "Transfer Done Sucssfullyyyyyy !";
                _PrintClientCard(clientToTransferFrom);
                _PrintClientCard(clientToTransferTo);

            }
            else
                cout << "ERROR !";
        }

	}
};

