#pragma once
#include<iostream>
#include"clsScreen.h"
#include "clsUser.h"
#include <iomanip>
using namespace std;

class clsLoginRegisterScreen : protected clsScreen
{

    static void _PrintLoginRecordLine(clsUser::stLoginRegisterRecord& record) {
        cout << '|' << setw(30) << left << record.DateTime <<
            '|' << setw(10) << left << record.Username <<
            '|' << setw(10) << left << record.Password <<
            '|' << setw(10) << left << record.stPermissions;
        cout << '\n';
    }

public:
    static void ShowLoginRegisterList() {
        if (!CheckAccessRights(clsUser::enPermissions::pLoginRegister))
            return;
        vector<clsUser::stLoginRegisterRecord> vList = clsUser::GetLoginRegisterList();
        string subtitle = to_string(vList.size());
        _DrawScreenHeader("\tLogin Register List Screen", "\t(" + subtitle + ") Record(s).");

        cout << "------------------------------------------------------------------------------------------------------------------------\n";
        cout << '|' << setw(30) << left << "Date/Time" <<
            '|' << setw(10) << left << "Username" <<
            '|' << setw(10) << left << "Password" <<
            '|' << setw(10) << left << "Permissions";
        cout << '\n';
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
        for (clsUser::stLoginRegisterRecord& record : vList)
        {
            _PrintLoginRecordLine(record);
        }
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
    }
};


