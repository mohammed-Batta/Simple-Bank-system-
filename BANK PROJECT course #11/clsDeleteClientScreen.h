#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsUtil.h"
using namespace std;


class clsDeleteClientScreen : protected clsScreen
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
   static void ShowDeleteClientScreen() {
       if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
           return;
       _DrawScreenHeader("\t Delete Client Screen");
        string AccountNumber = "";

        cout << "Plz Enter Account number : ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExists(AccountNumber)) {

            cout << "Account number is not found  : enter : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient client = clsBankClient::Find(AccountNumber);
        _PrintClientCard(client);
        cout << "Are u sure u wanna delete this client : ";
        char Answer = 'n';
        cin >> Answer;
        if (tolower(Answer) == 'y') {

            if (client.Delete()) {
                cout << "Client deleted Scussfully !";
                _PrintClientCard(client);

            }
            else
                cout << "ERORR";
        }

    }
};

