#pragma warning(disable : 4996)
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "clsDate.h"
#include "clsPerson.h"
#include "Global.h"
#include "clsString.h"
using namespace std;

class clsBankClient : public clsPerson
{
	enum enMode{EmptyMode = 0,UpdateMode = 1,AddNewMode = 2};


	enMode _Mode;
	string _AccountNumber;
	string _PINCODE;
	double _AccountBalance;
	bool _MarkForDelete = false;



	string _PrepareTransferLogRecord(double amount,clsBankClient ClientDestanation,string username) {
		string line = "", sepreater = "#//#";
		line += clsDate::GetSystemDateTimeString() + sepreater + _AccountNumber + sepreater + ClientDestanation.getAccountNumber()
			+ sepreater + to_string(amount) + sepreater + to_string(_AccountBalance)  +sepreater + to_string(ClientDestanation.AccountBalance) + sepreater + username;
		return line;
	}

	static clsBankClient _ConvertLineToClientObject(string line, string seperator = "#//#") {
		vector<string> data;
		data = clsString::SplitString(line, seperator);

		return clsBankClient(enMode::UpdateMode, data[0], data[1], data[2], data[3], data[4], data[5], stod(data[6]));
	}
	static string _ConvertClientObjectToLine(clsBankClient client, string seperator = "#//#") {
		
		string line = client.firstName + seperator
			+ client.LastName + seperator
			+ client.email + seperator
			+ client.phone + seperator
			+ client.getAccountNumber() + seperator
			+ client.PinCode + seperator
			+ to_string(client.AccountBalance);
		return line;
	}

	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);

	}
	static vector<clsBankClient> LoadClientDataFromFile() {
		vector<clsBankClient> data;
		fstream file;
		file.open("Clients.txt", ios::in);

		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				clsBankClient clinet = _ConvertLineToClientObject(line);

				data.push_back(clinet);
				
			}
		}
		file.close();
		return data;
	}


	static void SaveClientDataToFile(vector<clsBankClient>& data) {
		fstream file;
		file.open("Clients.txt", ios::out); //overwrite mode

		if (file.is_open()) {
			string line;
			for (clsBankClient & c : data) {
				if (c.MarkedForDelete() == false) {
					line = _ConvertClientObjectToLine(c);
					file << line << endl;
				}
			}
		}
		file.close();
	 }

	void _Update(){
		vector<clsBankClient> clients = LoadClientDataFromFile();
		for (clsBankClient& c : clients) {
			if (c.getAccountNumber() == _AccountNumber) {
				c = *this;
				break;
			}

		}
		SaveClientDataToFile(clients);
	}
	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}
	void _AddNew() {
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}
public:
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PINCODE, double AccountBalance) 
		:clsPerson(FirstName, LastName, Email, Phone) {
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PINCODE = PINCODE;
		_AccountBalance = AccountBalance;
	}

	struct stTransferLog {
		string DateTime;
		string AccountNumberFrom;
		string AccountNumberTo;
		double Amount;
		double AccountBalanceFrom;
		double AccountBalanceTo;
		string User;

	};
	static vector<stTransferLog> GetTeansferLogList() {
		vector<stTransferLog> data;
		fstream file;
		file.open("Transfer.txt", ios::in);

		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				stTransferLog log = ConvertLineToTransferRecord(line);

				data.push_back(log);

			}
		}
		file.close();
		return data;
	}
	static stTransferLog ConvertLineToTransferRecord(string line, string seperator = "#//#") {
		vector<string> data;
		data = clsString::SplitString(line, seperator);

		stTransferLog log;
		log.DateTime = data[0];
		log.AccountNumberFrom = data[1];
		log.AccountNumberTo = data[2];
		log.Amount = stod(data[3]);
		log.AccountBalanceFrom = stod(data[4]);
		log.AccountBalanceTo = stod(data[5]);
		log.User = data[6];
		return log;
	}

	 bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	string getAccountNumber() {
		return _AccountNumber;
	}

	void setPINCODE(string pinCode) {
		_PINCODE = pinCode;
	}
	string getPINCODE() {
		return _PINCODE;
	}
	_declspec(property(get = getPINCODE, put = setPINCODE)) string PinCode;

	void setAccountBalance(double AccountBalance) {
		_AccountBalance = AccountBalance;
	}
	double getAccountBalance() {
		return _AccountBalance	;
	}
	

	_declspec(property(get = getAccountBalance, put = setAccountBalance)) double AccountBalance;

	static clsBankClient Find(string AccountNumber) {
	 
		fstream file;
		file.open("Clients.txt", ios::in);

		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				clsBankClient clinet = _ConvertLineToClientObject(line);

				if (clinet.getAccountNumber() == AccountNumber) {
					file.close();
					return clinet;

				}
			}
		}
		file.close();
		return _GetEmptyClientObject();
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber) {

		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	static clsBankClient Find(string AccountNumber, string PINCODE) {
		fstream file;
		file.open("Clients.txt", ios::in);

		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				clsBankClient clinet = _ConvertLineToClientObject(line);

				if (clinet.getAccountNumber() == AccountNumber && clinet.PinCode == PINCODE) {
					file.close();
					return clinet;
				}
			}
		}
		file.close();
		return _GetEmptyClientObject();
	}

	
	bool Deposit(double Amount) {
		_AccountBalance += Amount;
		enSaveResults result =  Save();
		
		return result == enSaveResults::svSucceeded ? true : false;
	}

	bool Withdraw(double Amount) {
		if (Amount > _AccountBalance)
			return false;

		_AccountBalance -= Amount;
		enSaveResults result = Save();

		return result == enSaveResults::svSucceeded ? true : false;
	}


	void TransferLog(double amount , clsBankClient clientDestantion,string username) {
		string Data = _PrepareTransferLogRecord(amount,clientDestantion,username);
		fstream MyFile;
		MyFile.open("Transfer.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << Data << endl;

			MyFile.close();
		}
	}

	bool Transfer(double amount ,clsBankClient & clientToTransferTo) {
		if (amount > AccountBalance)
			return false;
		Withdraw(amount);
		clientToTransferTo.Deposit(amount);
		TransferLog(amount,clientToTransferTo,CurrentUser.UserName);
		return true;
	}

	static bool IsClientExists(string AccountNumber) {
		clsBankClient client = clsBankClient::Find(AccountNumber);
		return (!client.IsEmpty());
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1 , svFaildAccountNumberExists =2};

	enSaveResults Save() {
		switch (_Mode)
		{
		case enMode::EmptyMode:
			return enSaveResults::svFaildEmptyObject;

		case enMode::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;

		case enMode::AddNewMode:
			if(clsBankClient::IsClientExists(_AccountNumber))
				return enSaveResults::svFaildAccountNumberExists;

			_AddNew();
			_Mode = enMode::UpdateMode;
			return enSaveResults::svSucceeded;

		default:
			break;
		}
	}

	bool MarkedForDelete() {
		return _MarkForDelete;
	}

	bool Delete() {
		vector<clsBankClient> clients = LoadClientDataFromFile();

		for (clsBankClient& c : clients) {
			if (c.getAccountNumber() == _AccountNumber) {
				c._MarkForDelete = true;
				break;
			}
		}
		SaveClientDataToFile(clients);
		*this = _GetEmptyClientObject();

		if (_Mode == enMode::EmptyMode)
			return true;
		else
			return false;
	}

	static vector<clsBankClient> GetClientsList() {
		return LoadClientDataFromFile();
	}

	

	static double GetTotalBalances(){
		vector<clsBankClient> vClients = clsBankClient::GetClientsList();

		double Total = 0;

		for (clsBankClient& client : vClients)
			Total += client.AccountBalance;

		return Total;
	}
};

