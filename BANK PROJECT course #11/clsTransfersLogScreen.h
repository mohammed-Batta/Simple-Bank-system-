#pragma once
#include<iostream>
#include"clsScreen.h"
#include "clsUser.h"
#include "clsBankClient.h"
#include <iomanip>
using namespace std;

class clsTransfersLogScreen : protected clsScreen
{

    static void _PrintTransferRecordLine(clsBankClient::stTransferLog& record) {
        cout << '|' << setw(30) << left << record.DateTime <<
            '|' << setw(10) << left << record.AccountNumberFrom <<
            '|' << setw(10) << left << record.AccountNumberTo <<
            '|' << setw(10) << left << record.Amount <<
            '|' << setw(10) << left << record.AccountBalanceFrom <<
            '|' << setw(10) << left << record.AccountBalanceTo <<
            '|' << setw(10) << left << record.User;
        cout << '\n';
    }

public:
    static void ShowTransferLogList() {

        vector<clsBankClient::stTransferLog> vList = clsBankClient::GetTeansferLogList();
        string subtitle = to_string(vList.size());
        _DrawScreenHeader("\tTransfer Log List Screen", "\t(" + subtitle + ") Record(s).");

        cout << "------------------------------------------------------------------------------------------------------------------------\n";
        cout << '|' << setw(30) << left << "Date/Time" <<
            '|' << setw(10) << left << "s.Acct" <<
            '|' << setw(10) << left << "d.Acct" <<
            '|' << setw(10) << left << "Amount" <<
            '|' << setw(10) << left << "s.Balance" <<
            '|' << setw(10) << left << "d.Balance" <<
            '|' << setw(10) << left << "User";

        cout << '\n';
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
        for (clsBankClient::stTransferLog& record : vList)
        {
            _PrintTransferRecordLine(record);
        }
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
    }
};


