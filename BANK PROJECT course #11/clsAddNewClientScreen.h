#pragma once
#include<iostream>
#include"clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>
using namespace std;

class clsAddNewClientScreen : protected clsScreen
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

public :
	static void ShowAddNewClientScreen() {

        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
            return;

        _DrawScreenHeader("\t Add New Client Screen.");

        string AccountNumber = "";

        cout << "Plz Enter Account number : ";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExists(AccountNumber)) {

            cout << "Account number is  found  : enter another one : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient client = clsBankClient::GetAddNewClientObject(AccountNumber);

        cout << "\n\nAdd New client Info:";
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
            cout << "Client Added sucssuflly :-)\n";
            _PrintClientCard(client);
            break;

        case clsBankClient::enSaveResults::svFaildAccountNumberExists:
            cout << "Client NOT Added cuz the number is already exits :-(\n";
            break;
        default:
            break;
        }
	}
};

