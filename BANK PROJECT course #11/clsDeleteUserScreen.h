#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsUser.h"
#include "clsUtil.h"
using namespace std;


class clsDeleteUserScreen : protected clsScreen
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
    static void ShowDeleteUserScreen() {
        _DrawScreenHeader("\t Delete User Screen");
        string UserName = "";

        cout << "Plz Enter UserName : ";
        UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExists(UserName)) {

            cout << "UserName is not found  : enter : ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser user = clsUser::Find(UserName);
        _PrintUserCard(user);
        cout << "Are u sure u wanna delete this client : ";
        char Answer = 'n';
        cin >> Answer;
        if (tolower(Answer) == 'y') {

            if (user.Delete()) {
                cout << "User deleted Scussfully !";
                _PrintUserCard(user);

            }
            else
                cout << "ERORR";
        }

    }
};

