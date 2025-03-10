#pragma once

#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsUtil.h"
using namespace std;


class clsFindClientScreen : protected clsScreen
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
    static void ShowFindClientScreen() {
        if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
            return;
        _DrawScreenHeader("\tFind Client Screen");

        string AccountNumber = "";

        cout << "Plz Enter Account number : ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExists(AccountNumber)) {

            cout << "Account number is not found  : enter : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient client = clsBankClient::Find(AccountNumber);
        _PrintClientCard(client);
    }
};

