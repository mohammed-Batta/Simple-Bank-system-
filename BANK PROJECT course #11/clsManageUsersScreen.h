#pragma once

#include<iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsDepositScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsWithdrawScreen.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
#include <iomanip>
using namespace std;

class clsManageUsersScreen : protected clsScreen
{
    enum enManageUsersMenueOptions { eListUsers = 1, eAddNewUser, eDeleteUser, eUpdateUser,eFindUser,eGoBackToMainMenu };

    static short _ReadManageUsersMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }

    static  void _GoBackToManageUsersMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Manage Users Menue...\n";
        system("pause>0");
       ShowManageUsersMenue();
    }

    static void _ShowListUsersScreen() {
        clsUsersListScreen::ShowUsersList();
    }

    static void _ShowAddNewUserScreen() {
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }
    static void _ShowDeleteUserScreen() {
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen() {
        clsUpdateUserScreen::ShowUpdateUserScreen();
     }

    static void _ShowFindUserScreen() {
        clsFindUserScreen::ShowFindUserScreen();
    }


    static void _PerfromManageUsersMenueOption(enManageUsersMenueOptions ManageUsersMenueOption)
    {
        switch (ManageUsersMenueOption)
        {
        case enManageUsersMenueOptions::eListUsers:
        {
            system("cls");
            _ShowListUsersScreen();
            _GoBackToManageUsersMenue();
            break;
        }
        case enManageUsersMenueOptions::eAddNewUser:
            system("cls");
            _ShowAddNewUserScreen();
            _GoBackToManageUsersMenue();
            break;

        case enManageUsersMenueOptions::eDeleteUser:
            system("cls");
            _ShowDeleteUserScreen();
            _GoBackToManageUsersMenue();
            break;

        case enManageUsersMenueOptions::eUpdateUser: 
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case enManageUsersMenueOptions::eFindUser:
            system("cls");
            _ShowFindUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case enManageUsersMenueOptions::eGoBackToMainMenu:
            break;

        }

    }



public:


    static void ShowManageUsersMenue()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
            return;
        system("cls");
        _DrawScreenHeader("\t Manage Users Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t Manage Users Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Go Back To Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromManageUsersMenueOption((enManageUsersMenueOptions)_ReadManageUsersMenueOption());
    }

};



