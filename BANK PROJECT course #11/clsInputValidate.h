#pragma once
#include <iostream>
#include <iomanip>
#include "clsDate.h"
using namespace std;

class clsInputValidate
{

public:

	static int ReadPositiveValidIntNumber(string msg) {
		int number = ReadIntNumber(msg);
		while (number <= 0) {
			string errorMsg = "The number should be a positive,Enter agian ";
			number = ReadIntNumber(errorMsg);
		}
		return number;
	}

	static int ReadIntNumber(string msg) {
		int NUmber;
		cout << msg + " ";
		cin >> NUmber;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits <streamsize>::max(), '\n');
			cout << "Invalid input (the input should be a number)" << endl;
			cin >> NUmber;
		}
		return NUmber;
	}

	static int ReadIntNumberBetween(int From, int To, string msg) {
		int number = ReadIntNumber("");
		while (number < From || number > To) {
			number = ReadIntNumber(msg);
		}

		return number;
	}
	static short ReadShortNumberBetween(int From, int To, string msg) {
		short number = ReadIntNumber("");
		while (number < From || number > To) {
			number = ReadIntNumber(msg);
		}

		return number;
	}

	static double ReadDblNumber() {
		double NUmber;
		cin >> NUmber;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits <streamsize>::max(), '\n');
			cout << "Invalid input (the input should be a number)" << endl;
			cin >> NUmber;
		}
		return NUmber;
	}

	static double ReadDblNumberBetween(double From, double To) {
		double number = ReadDblNumber();
		while (number < From || number > To) {
			string errorMsg = "number it's in the requried range ! . enter agian : ";
			number = ReadDblNumber();
		}

		return number;
	}

	static bool IsNumberBetween( int number, int From, int To) {
		return (number >= From && number <= To);
	}
	static bool IsNumberBetween(short number, short From, short To) {
		return (number >= From && number <= To);
	}
	static bool IsNumberBetween(float number, float From, float To) {
		return (number >= From && number <= To);
	}
	static bool IsNumberBetween(double number, double From, double To) {
		return (number >= From && number <= To);
	}

	static bool IsDateBetween(clsDate date, clsDate From, clsDate To) {

		if ((clsDate::IsDate1AfterDate2(date, From) || clsDate::IsDate1EqualDate2(date, From))
			&& (clsDate::IsDate1BeforeDate2(date, To) || clsDate::IsDate1EqualDate2(date, To)))
			return true;
		if ((clsDate::IsDate1AfterDate2(date, To) || clsDate::IsDate1EqualDate2(date, To))
			&& (clsDate::IsDate1BeforeDate2(date, From) || clsDate::IsDate1EqualDate2(date, From)))
			return true;

		return false;

	}

	static bool IsValideDate(clsDate date) {
		return clsDate::IsValidDate(date);
	}

	static string ReadString()
	{
		string  S1 = "";
		getline(cin >> ws, S1);
		return S1;
	}

};

