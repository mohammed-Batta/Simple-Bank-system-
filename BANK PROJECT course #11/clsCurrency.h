#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "clsUtil.h"
#include "Global.h"
#include"clsDate.h"
#include "clsString.h"
using namespace std;

class clsCurrency 
{
	enum enMode { EmptyMode = 0,UpdateMode = 1 };
	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;	

	static clsCurrency _ConvertLineToCurrnecyObject(string line, string seperator = "#//#") {
		vector<string> data;
		data = clsString::SplitString(line, seperator);

		return clsCurrency(enMode::UpdateMode, data[0], data[1], data[2], stof(data[3]));
	}
	static void SaveCurrencyDataToFile(vector<clsCurrency>& data) {
		fstream file;
		file.open("Currencies.txt", ios::out); //overwrite mode

		if (file.is_open()) {
			string line;
			for (clsCurrency& c : data) {
					line = _ConvertCurrencyObjectToLine(c);
					file << line << endl;
			}
		}
		file.close();
	}
	 void _Update() {
		vector<clsCurrency> currencies = LoadCurrenciesDataFromFile();
		for (clsCurrency& c : currencies) {
			if (c._CurrencyCode == _CurrencyCode) {
				c = *this;
				break;
			}

		}
		SaveCurrencyDataToFile(currencies);
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string seperator = "#//#") {

		string line = Currency._Country + seperator
			+ Currency._CurrencyCode + seperator
			+ Currency._CurrencyName + seperator
			+ to_string(Currency._Rate);
		return line;
	}

	static clsCurrency _GetEmptyCurrencyObject() {
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);

	}

	static vector<clsCurrency> LoadCurrenciesDataFromFile() {
		vector<clsCurrency> data;
		fstream file;
		file.open("Currencies.txt", ios::in);

		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				clsCurrency currnecy = _ConvertLineToCurrnecyObject(line);

				data.push_back(currnecy);

			}
		}
		file.close();
		return data;
	}
	

public:

	 clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate) {
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}
	string getCountry() {
		return _Country;
	}
	string getCurrencyCode() {
		return _CurrencyCode;
	}
	string getCurrencyName() {
		return _CurrencyName;
	}

	void UpdateRate(float Rate) {
		_Rate = Rate;
		_Update();

	}
	float getRate() {
		return _Rate;
	}
	_declspec(property(get = getRate, put = UpdateRate)) float Rate;

	static clsCurrency FindByCounrty(string Country) {
		Country = clsString::ToUpperString(Country);
		fstream file;
		file.open("Currencies.txt", ios::in);

		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				clsCurrency Currency = _ConvertLineToCurrnecyObject(line);

				if (clsString::ToUpperString(Currency.getCountry()) == Country) {
					file.close();
					return Currency;
				}
			}
		}
		file.close();
		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCode(string CurrnecyCode) {
		CurrnecyCode = clsString::ToUpperString(CurrnecyCode);
		fstream file;
		file.open("Currencies.txt", ios::in);
		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				clsCurrency Currency = _ConvertLineToCurrnecyObject(line);
				if (Currency._CurrencyCode == CurrnecyCode) {
					file.close();
					return Currency;
				}
			}
		}
		file.close();
		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExists(string CurrencyCode) {
		clsCurrency currnecy = clsCurrency::FindByCode(CurrencyCode);
		return (!currnecy.IsEmpty());
	}

	static vector<clsCurrency> GetCurrenciesList() {
		return LoadCurrenciesDataFromFile();
	}

	float ConvertToUSD(float Amount) {
		return (float)(Amount / Rate);
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency currencyTo) {
		float AmountInUSD = ConvertToUSD(Amount);
		if (currencyTo.getCurrencyCode() == "USD")
			return AmountInUSD;
		else
			return (float)(AmountInUSD * currencyTo.Rate);
	}
};

