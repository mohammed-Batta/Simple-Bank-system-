#pragma once
#include <iostream>
using namespace std;

class clsPerson
{
	
private:
	string _FirstName;
	string _LastName;
	string _Email;
	string _Phone;

public:

	clsPerson(string FirstName, string lastName, string email, string phone)
	{
		_FirstName = FirstName;
		_LastName = lastName;
		_Email = email;
		_Phone = phone;

	}


	void setFirstName(string firstname) {
		_FirstName = firstname;
	}
	string getFirstName() {
		return _FirstName;
	}
	_declspec(property(get = getFirstName, put = setFirstName)) string firstName;

	void setLastName(string lastname) {
		_LastName = lastname;
	}
	string getLastName() {
		return _LastName;
	}
	_declspec(property(get = getLastName, put = setLastName)) string LastName;

	void setEmail(string email) {
		_Email = email;
	}
	string getEmail() {
		return _Email;
	}
	_declspec(property(get = getEmail, put = setEmail)) string email;

	void setPhone(string phone) {
		_Phone = phone;
	}
	string getPhone() {
		return _Phone;
	}
	_declspec(property(get = getPhone, put = setPhone)) string phone;


	void SendEmail(string Subject, string body) {
		cout << "\nThe following message sent successfully to email : " << _Email << endl;
		cout << "Subject : " << Subject << endl;
		cout << "Body : " << body << endl;
	}
	void SendSMS(string message) {
		cout << "\nThe following SMS message sent successfully to phone : " << _Phone << endl;
		cout << message << endl;
	}

	string FullName() {
		return _FirstName + " " + _LastName;
	}

	
};