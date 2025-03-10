#pragma once
#include<iostream>
#include"clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>
using namespace std;

class clsAddNewUserScreen : protected clsScreen
{

    static void _ReadUserInfo(clsUser& user) {
        cout << "\nEnter FirstName :";
        user.firstName = clsInputValidate::ReadString();
        cout << "\nEnter LastName :";
        user.LastName = clsInputValidate::ReadString();
        cout << "\nEnter email :";
        user.email = clsInputValidate::ReadString();
        cout << "\nEnter phone :";
        user.phone = clsInputValidate::ReadString();
        cout << "\nEnter Password :";
        user.Password = clsInputValidate::ReadString();
        cout << "\nEnter Permissions :";
        user.Permissions = _ReadPermissionsToSet();

    }

    static int _ReadPermissionsToSet()
    {

        int Permissions = 0;
        char Answer = 'n';


        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {


            Permissions += clsUser::enPermissions::pListClients;
        }


        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }

        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pTranactions;
        }

         cout << "\nManage Users? y/n? ";
            cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }
        cout << "\nLogin Register? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pLoginRegister;
        }
        cout << "\nCurrency Exchange? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pCurrencyExchange;
        }


        return Permissions;

    }

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
    static void ShowAddNewUserScreen() {
        _DrawScreenHeader("\t Add New User Screen.");

        string UserName = "";

        cout << "Plz Enter Username : ";
        UserName = clsInputValidate::ReadString();

        while (clsUser::IsUserExists(UserName)) {

            cout << "User Name is  found  : enter another one : ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser user = clsUser::GetAddNewUserObject(UserName);

        cout << "\n\nAdd New client Info:";
        cout << "\n_______________________\n";
        _ReadUserInfo(user);

        clsUser::enSaveResults result;
        result = user.Save();
        switch (result)
        {
        case clsUser::enSaveResults::svFaildEmptyObject:
            cout << "User Not sucssuflly cuz it's empty :-(\n";
            break;
        case clsUser::enSaveResults::svSucceeded:
            cout << "User Added sucssuflly :-)\n";
            _PrintUserCard(user);
            break;

        case clsUser::enSaveResults::svFaildUserNameExists:
            cout << "User NOT Added cuz the Username is already exits :-(\n";
            break;
        default:
            break;
        }
     

    }
};

