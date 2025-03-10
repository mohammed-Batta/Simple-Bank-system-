#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "clsPerson.h"
#include "clsUtil.h"
#include "Global.h"
#include"clsDate.h"
#include "clsString.h"
using namespace std;

class clsUser : public clsPerson
{
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;
	string _UserName;
	string _PassWord;
	int _Permissions;
	bool _MarkForDelete = false;
	const static short _EncryptionKey = 2;

	
	
	string _PrepareLoginRecord() {
		string line = "" , sepreater = "#//#";
		line += clsDate::GetSystemDateTimeString() +sepreater + _UserName + sepreater + clsUtil::EncryptText(_PassWord, _EncryptionKey) + sepreater + to_string(_Permissions);
		return line;
	}

	static clsUser _ConvertLineToUserObject(string line, string seperator = "#//#") {
		vector<string> data;
		data = clsString::SplitString(line, seperator);

		return clsUser(enMode::UpdateMode, data[0], data[1], data[2], data[3], data[4], clsUtil::DecryptText(data[5], _EncryptionKey), stoi(data[6]));
	}




	static string _ConvertUserObjectToLine(clsUser user, string seperator = "#//#") {

		string line = user.firstName + seperator
			+ user.LastName + seperator
			+ user.email + seperator
			+ user.phone + seperator
			+ user.UserName + seperator
			+ clsUtil::EncryptText(user.Password, _EncryptionKey) + seperator
			+ to_string(user.Permissions);
		return line;
	}

	static clsUser _GetEmptyUserObject() {
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);

	}
	static vector<clsUser> LoadUsersDataFromFile() {
		vector<clsUser> data;
		fstream file;
		file.open("Users.txt", ios::in);

		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				clsUser user = _ConvertLineToUserObject(line);

				data.push_back(user);

			}
		}
		file.close();
		return data;
	}


	static void SaveUserDataToFile(vector<clsUser>& data) {
		fstream file;
		file.open("Users.txt", ios::out); //overwrite mode

		if (file.is_open()) {
			string line;
			for (clsUser& c : data) {
				if (c.MarkedForDelete() == false) {
					line = _ConvertUserObjectToLine(c);
					file << line << endl;
				}
			}
		}
		file.close();
	}

	void _Update() {
		vector<clsUser> users = LoadUsersDataFromFile();
		for (clsUser& c : users) {
			if (c.UserName == _UserName) {
				c = *this;
				break;
			}

		}
		SaveUserDataToFile(users);
	}
	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}
	void _AddNew() {
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}
public:

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permissions)
		:clsPerson(FirstName, LastName, Email, Phone) {
		_Mode = Mode;
		_UserName = UserName;
		_PassWord = Password;
		_Permissions = Permissions;
	}
	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64, pLoginRegister = 128,pCurrencyExchange = 256
	};
	struct stLoginRegisterRecord {
		string DateTime;
		string Username;
		string Password;
		int stPermissions;
	};

	static stLoginRegisterRecord _ConvertLineToLoginRegisterStruct(string line, string seperator = "#//#") {
		vector<string> data;
		data = clsString::SplitString(line, seperator);
		stLoginRegisterRecord record;
		record.DateTime = data[0];
		record.Username = data[1];
		record.Password = clsUtil::DecryptText(data[2], _EncryptionKey);
		record.stPermissions = stoi(data[3]);
		return record;
	}

	static vector<stLoginRegisterRecord> LoadLoginRegisterationDataFromFile() {
		vector<stLoginRegisterRecord> data;
		fstream file;
		file.open("Login.txt", ios::in);

		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				stLoginRegisterRecord record = _ConvertLineToLoginRegisterStruct(line);

				data.push_back(record);

			}
		}
		file.close();
		return data;
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	string setUserName() {
		return _UserName;
	}

	string getUserName() {
		return _UserName;
	}
	_declspec(property(get = getUserName, put = setUserName)) string UserName;

	void setPassword(string password) {
		_PassWord = password;
	}
	string getPassword() {
		return _PassWord;
	}
	_declspec(property(get = getPassword, put = setPassword)) string Password;

	void setPermissions(int Permissions) {
		_Permissions = Permissions;
	}
	int getPermissions() {
		return _Permissions;
	}
	_declspec(property(get = getPermissions, put = setPermissions)) int Permissions;

	static clsUser Find(string UserName) {

		fstream file;
		file.open("Users.txt", ios::in); // read

		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				clsUser user = _ConvertLineToUserObject(line);

				if (user.UserName == UserName) {
					file.close();
					return user;

				}
			}
		}
		file.close();
		return _GetEmptyUserObject();
	}

	static clsUser GetAddNewUserObject(string username) {

		return clsUser(enMode::AddNewMode, "", "", "", "", username, "", -1);
	}

	static clsUser Find(string UserName, string Password) {
		fstream file;
		file.open("Users.txt", ios::in);

		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				clsUser user = _ConvertLineToUserObject(line);

				if (user.UserName == UserName && user.Password == Password) {
					file.close();
					return user;
				}
			}
		}
		file.close();
		return _GetEmptyUserObject();
	}


	

	static bool IsUserExists(string UserName) {
		clsUser user = clsUser::Find(UserName);
		return (!user.IsEmpty());
	}
	static bool IsUserExists(string UserName,string Password) {
		clsUser user = clsUser::Find(UserName, Password);
		return (!user.IsEmpty());
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserNameExists = 2 };

	enSaveResults Save() {
		switch (_Mode)
		{
		case enMode::EmptyMode:
			return enSaveResults::svFaildEmptyObject;

		case enMode::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;

		case enMode::AddNewMode:
			if (clsUser::IsUserExists(_UserName))
				return enSaveResults::svFaildUserNameExists;

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
		vector<clsUser> users = LoadUsersDataFromFile();

		for (clsUser& c : users) {
			if (c.UserName == _UserName) {
				c._MarkForDelete = true;
				break;
			}
		}
		SaveUserDataToFile(users);
		*this = _GetEmptyUserObject();

		if (_Mode == enMode::EmptyMode)
			return true;
		else
			return false;
	}

	static vector<clsUser> GetUsersList() {
		return LoadUsersDataFromFile();
	}
	static vector<stLoginRegisterRecord> GetLoginRegisterList() {
		return LoadLoginRegisterationDataFromFile();
	}
	 bool CheckAccessPermission(enPermissions Permission) {
		if (_Permissions == enPermissions::eAll)
			return true;

		if ((_Permissions & Permission) == Permission)
			return true;

		return false;
	}

	  void RegisterLogin() {
		  string loginData = _PrepareLoginRecord();
		 fstream MyFile;
		 MyFile.open("Login.txt", ios::out | ios::app);

		 if (MyFile.is_open())
		 {
			 MyFile << loginData << endl;

			 MyFile.close();
		 }
	 }
};

