#pragma once
#include<iostream>
#include"clsScreen.h"
#include "clsBankClient.h"
#include "clsUser.h"
#include <iomanip>
using namespace std;

class clsClientListScreen : protected clsScreen
{

    static void PrintClientRecordLine(clsBankClient& client) {
        cout << '|' << setw(16) << left << client.getAccountNumber() <<
            '|' << setw(30) << left << client.FullName() <<
            '|' << setw(14) << left << client.phone <<
            '|' << setw(30) << left << client.email <<
            '|' << setw(10) << left << client.PinCode <<
            '|' << setw(10) << left << client.AccountBalance;
        cout << '\n';
    }

public:
	static void ShowClientsList() {
        if (!CheckAccessRights(clsUser::enPermissions::pListClients)) {
            return;
        }

        vector<clsBankClient> vClientsData = clsBankClient::GetClientsList();
        string subtitle = to_string(vClientsData.size());
        _DrawScreenHeader("\tClients List Screen", "\t(" + subtitle + ") Client(s).");

        cout << "------------------------------------------------------------------------------------------------------------------------\n";
        cout << '|' << setw(16) << left << "Account Number" <<
            '|' << setw(30) << left << "Client name" <<
            '|' << setw(14) << left << "Phone" <<
            '|' << setw(30) << left << "Email" <<
            '|' << setw(10) << left << "Pin code" <<
            '|' << setw(10) << left << "Balance";
        cout << '\n';
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
        for (clsBankClient& client : vClientsData)
        {
            PrintClientRecordLine(client);
        }
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
    }
};

