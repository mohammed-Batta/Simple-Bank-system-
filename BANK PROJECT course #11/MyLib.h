#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

/*
int x = 10;
   int & y = x; // I gave a diffenent identifier to var x (they both have the same Ref)
   cout << &x << endl;
   cout << &y << endl;
   y = 20;


   cout << x << endl;
   cout << y << endl;


*/

/*
    cout << "---------|--------------------------------|------------| " << endl;
    cout << "  Code   |            Name                |    Mark    | " << endl;
    cout << "---------|--------------------------------|------------| " << endl;
    cout << setw(9) << "C101" << "|" << setw(32) << "introduction to Programming 1" << "| " << setw(9) << "95" << "  | " << endl;
    cout << setw(9) << "C102" << "|" << setw(32) << "Computer  Hardware" << "| " << setw(9) << "88" << "  | " << endl;
    cout << setw(9) << "C1035243" << "|" << setw(32) << "Network"  << "| " << setw(9) << "75" << "  | " << endl;
    cout << "---------|--------------------------------|------------| " << endl;
*/

//                 int format
	//     printf("The pages number = %0*d",3,1);
	//     printf("The pages number = %d",3);

	//                float formt 
	// float PI = 3.142242342;
	// printf("%.*f",3,PI); // 3.143
	//printf("%.3f",7.0); // 7.000
	/*
	char Name[] = "Mohammed Abu-Hadhoud";
	char SchoolName[] = "Programming Advices";

	// print string and String
	printf("Dear %s, How are you?\n\n", Name);
	printf("Welcome to %s School!\n\n", SchoolName);

	char c = 'S';
	printf("Setting the width of c :%*c \n", 1, c);
	printf("Setting the width of c :%*c \n", 2, c);
	printf("Setting the width of c :%*c \n", 3, c);
	printf("Setting the width of c :%*c \n", 4, c);
	printf("Setting the width of c :%*c \n", 5, c);

	*/
namespace MyInput {
	
	vector<string> SplitString(string text, string sprater = " ") {
		string word = "";
		int SpraterPosition = 0;

		vector<string> vWords;
		while ((SpraterPosition = text.find(sprater)) != text.npos) {

			word = text.substr(0, SpraterPosition);

			if (!word.empty())
				vWords.push_back(word);

			text.erase(0, SpraterPosition + sprater.length());
		}
		if (!text.empty())
			vWords.push_back(text);

		return vWords;
	}

	

	int ReadIntNumber(string msg) {
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

	int ReadPositiveValidIntNumber(string msg) {
		int number = ReadIntNumber(msg);
		while (number <= 0) {
			string errorMsg = "The number should be a positive,Enter agian ";
			number = ReadIntNumber(errorMsg);
		}
		return number;
	}


	int ReadIntNumberBetween(int From, int To, string msg) {
		int number = ReadIntNumber(msg);
		while (number < From || number > To) {
			string errorMsg = "number it's in the requried range ! . enter agian : ";
			number = ReadIntNumber(errorMsg);
		}

		return number;
	}
}

namespace MyMath {

	void RecursionPrintNumberFromNdownToM(int N, int M) {

		if (N >= M) {
			cout << N << endl;
			RecursionPrintNumberFromNdownToM(--N, M);
		}

	}

	int RecursionMathPower(int Base, int Power) { // # My methode
		// Recursion is the idea of ( A CALL STACK ) but be carefull this methode leads to stack overflow with big numbers
		static int sum = 1;
		if (Power >= 1) {
			sum *= Base;
			RecursionMathPower(Base, --Power);
		}
		return sum;
	}

	int Pow(int Base, int Power) { // # His methode
		// Recursion is the idea of ( A CALL STACK ) but be carefull this methode leads to stack overflow with big numbers
		if (Power == 0) 
			return 1;
		else 
		{
		return (Base * RecursionMathPower(Base, --Power));
		}
}
	
}
