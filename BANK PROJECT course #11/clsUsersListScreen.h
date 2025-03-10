#pragma once
#include<iostream>
#include"clsScreen.h"
#include "clsUser.h"
#include <iomanip>
using namespace std;

class clsUsersListScreen : protected clsScreen
{

    static void _PrintUserRecordLine(clsUser& user) {
        cout << '|' << setw(16) << left << user.UserName <<
            '|' << setw(30) << left << user.FullName() <<
            '|' << setw(14) << left << user.phone <<
            '|' << setw(30) << left << user.email <<
            '|' << setw(10) << left << user.Password <<
            '|' << setw(10) << left << user.Permissions;
        cout << '\n';
    }

public:
    static void ShowUsersList() {
        vector<clsUser> vUsers = clsUser::GetUsersList();
        string subtitle = to_string(vUsers.size());
        _DrawScreenHeader("\tUsers List Screen", "\t(" + subtitle + ") User(s).");

        cout << "------------------------------------------------------------------------------------------------------------------------\n";
        cout << '|' << setw(16) << left << "UserName" <<
            '|' << setw(30) << left << "Full Name" <<
            '|' << setw(14) << left << "Phone" <<
            '|' << setw(30) << left << "Email" <<
            '|' << setw(10) << left << "Password" <<
            '|' << setw(10) << left << "Permissions";
        cout << '\n';
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
        for (clsUser& user : vUsers)
        {
            _PrintUserRecordLine(user);
        }
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
    }
};

