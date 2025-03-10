#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsDepositScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTransferScreen.h"
#include "clsTransfersLogScreen.h";
#include <iomanip>
using namespace std;

class clsTransactionsScreen : protected clsScreen
{
    enum enTransactionsMenueOptions {   eDeposit = 1, eWithdraw, eShowTotalBalances, eTransfer, eShowTransferLogList, eGoBackToMainMenu};

    static short _ReadTransactionsMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }

    static  void _GoBackToTransactionsMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Transactions Menue...\n";
        system("pause>0");
        ShowTransactionsMenue();
    }

    static void _ShowDepositScreen() {
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen() {
        clsWithdrawScreen::ShowWithdrawScreen();
    }
    static void _ShowTotalBalancesScreen() {
        clsTotalBalancesScreen::ShowTotalBalancesScreen();
    }
    static void _ShowTransferScreen() {
        clsTransferScreen::ShowTransferScreen();
    }
    static void _ShowTransferLogListScreen() {
        clsTransfersLogScreen::ShowTransferLogList();
    }

    static void _PerfromTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOption)
    {
        switch (TransactionsMenueOption)
        {
        case enTransactionsMenueOptions::eDeposit:
        {
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionsMenue();
            break;
        }
        case enTransactionsMenueOptions::eWithdraw:
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionsMenue();
            break;

        case enTransactionsMenueOptions::eShowTotalBalances:     
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenue();
            break;

        case enTransactionsMenueOptions::eTransfer:
            system("cls");
            _ShowTransferScreen();
            _GoBackToTransactionsMenue();
            break;
        case enTransactionsMenueOptions::eShowTransferLogList:
            system("cls");
            _ShowTransferLogListScreen();
            _GoBackToTransactionsMenue();
            break;

        case enTransactionsMenueOptions::eGoBackToMainMenu:   
            break;
      
        }

    }



public:


    static void ShowTransactionsMenue()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pTranactions))
            return;
        system("cls");
        _DrawScreenHeader("\t Transactions Menu Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t Transactions Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Show Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Go Back To Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromTransactionsMenueOption((enTransactionsMenueOptions)_ReadTransactionsMenueOption());
    }

};

