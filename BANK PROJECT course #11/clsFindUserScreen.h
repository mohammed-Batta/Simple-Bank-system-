#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsUtil.h"
using namespace std;


class  clsFindUserScreen : protected clsScreen
{
    static void _PrintUserCard(clsUser& user) {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirsName     :" << user.firstName;
        cout << "\nLastName     :" << user.LastName;
        cout << "\nEmail        :" << user.email;
        cout << "\nPhone        :" << user.phone;
        cout << "\nUserName     :" << user.UserName;
        cout << "\nPassword     :" << user.Password;
        cout << "\nPermissions  :" << user.Permissions;
        cout << "\n___________________\n";

    }

public:
    static void ShowFindUserScreen() {
        _DrawScreenHeader("\tFind User Screen");

        string Username = "";

        cout << "Plz Enter Username : ";
        Username = clsInputValidate::ReadString();

        while (!clsUser::IsUserExists(Username)) {

            cout << "Username is not found  : enter : ";
            Username = clsInputValidate::ReadString();
        }

        clsUser user = clsUser::Find(Username);
        _PrintUserCard(user);
    }
};

