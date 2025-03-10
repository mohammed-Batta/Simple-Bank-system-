#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsUtil.h"
using namespace std;


class clsUpdateClientScreen : protected clsScreen
{
    static void _ReadClientInfo(clsBankClient& client) {
        cout << "\nEnter FirstName :";
        client.firstName = clsInputValidate::ReadString();
        cout << "\nEnter LastName :";
        client.LastName = clsInputValidate::ReadString();
        cout << "\nEnter email :";
        client.email = clsInputValidate::ReadString();
        cout << "\nEnter phone :";
        client.phone = clsInputValidate::ReadString();
        cout << "\nEnter PinCode :";
        client.PinCode = clsInputValidate::ReadString();
        cout << "\nEnter Account Balance :";
        client.AccountBalance = clsInputValidate::ReadDblNumber();

    }

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
    static void ShowUpdateClientScreen() {

        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
            return;
        _DrawScreenHeader("\tUpdate Client Screen");
        string AccountNumber = "";

        cout << "Plz Enter Account number : ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExists(AccountNumber)) {

            cout << "Account number is not found  : enter : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient client = clsBankClient::Find(AccountNumber);
        _PrintClientCard(client);

        cout << "Are u sure u wanna update this client Info : ";
        char answer = 'n';
        cin >> answer;

        if (tolower(answer) != 'y') {
            return;
        }

        cout << "\n\nUpdate client Info:";
        cout << "\n_______________________\n";
        _ReadClientInfo(client);

        clsBankClient::enSaveResults result;
        result = client.Save();
        switch (result)
        {
        case clsBankClient::enSaveResults::svFaildEmptyObject:
            cout << "Account Not sucssuflly cuz it's empty :-(\n";
            break;
        case clsBankClient::enSaveResults::svSucceeded:
            cout << "Account Updates sucssuflly :-)\n";
            _PrintClientCard(client);
            break;
        default:
            break;
        }


    }
};

