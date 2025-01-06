#pragma warning(disable:4996)

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include "MyLib.h"

using namespace std;

enum class enMainMenuChoices { ShowClientList = 1,AddNewClient =2,DeleteClient =3,UpdateClient = 4,FindClinet =5,Transactions = 6,Exit =7 };
enum class enTransactionsChoices { DepositScreen = 1,Withdraw ,TotalBalances ,MainMenu = 4 };
const string ClientsFileName = "Clients.txt";

struct sClient {
	string AccountNumber;
	string PINCODE;
	string Name;
	string Phone;
	double AccountBalance;
};

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

void PrintClientRecordForList(sClient& Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PINCODE;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintClientRecordForTransactionsMenu(sClient& Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}


void PrintClientRecord(sClient client) {
	cout << "Account Number  : " << client.AccountNumber << endl;
	cout << "PIN CODE        : " << client.PINCODE << endl;
	cout << "Name            : " << client.Name << endl;
	cout << "Phone           : " << client.Phone << endl;
	cout << "Account Balance : " << client.AccountBalance << endl;
}

string ConvertRecordToLine(sClient client, string sperator = "#//#") {
	return (client.AccountNumber + sperator + client.PINCODE + sperator + client.Name + sperator + client.Phone + sperator + to_string(client.AccountBalance));
}

sClient ReadClientDataFromUser(string AccountNumber) {

	sClient client;

	client.AccountNumber = AccountNumber;
	cout << "Enter PIN CODE  : ";
	getline(cin >> ws, client.PINCODE);


	cout << "Enter Name  : ";
	getline(cin, client.Name);



	cout << "Enter Phone  : ";
	getline(cin, client.Phone);


	cout << "Enter Account Balance  : ";
	cin >> client.AccountBalance;

	return client;
}

sClient ConvertLineToRecord(string line, string sprater = "#//#") {
	vector<string> vData = SplitString(line, sprater);
	sClient client;

	client.AccountNumber = vData[0];
	client.PINCODE = vData[1];
	client.Name = vData[2];
	client.Phone = vData[3];
	client.AccountBalance = stod(vData[4]);

	return client;
}

vector<sClient> ReadClientDataFromFile(string FileName) {

	vector<sClient> vClients;
	fstream MyFile;
	string line = "";
	MyFile.open(FileName, ios::in);

	
	if (MyFile.is_open()) {

		while (getline(MyFile, line))
			vClients.push_back(ConvertLineToRecord(line));

		MyFile.close();
	}

	return vClients;
}


void AddDataLineToFile(string FileName,string DataLine) {
	fstream MyFile;

	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open()) {
		MyFile << DataLine << endl;
		MyFile.close();
	}

}
bool FindClinetByAccountNumber(string AccountNumber, vector<sClient>& vClients, sClient& c) {

	for (sClient& client : vClients) {
		if (client.AccountNumber == AccountNumber) {
			c = client;
			return true;

		}
	}
	return false;
}


void AddNewClient(string AccountNumber) {
	AddDataLineToFile(ClientsFileName,ConvertRecordToLine(ReadClientDataFromUser(AccountNumber)));
}

void AddClients(vector<sClient>& AllClientsData) {
	char AddMore = 'y';
	string AccountNumberTemp = "";
	sClient clinent;
	do {
		system("cls");
		cout << "\n--------------------------------\n";
		cout << "\tAdd New Clients Screen\n";
		cout << "--------------------------------\n\n";
		cout << "Adding New Client:\n ";
		cout << "Enter Account Number : ";

		getline(cin >> ws, AccountNumberTemp);
		
		while (FindClinetByAccountNumber(AccountNumberTemp, AllClientsData, clinent)) {
			cout << "Clinet with [" << AccountNumberTemp << "] already exists , Enter another account number : ";
			getline(cin, AccountNumberTemp);
		}
		AddNewClient(AccountNumberTemp);
		AllClientsData = ReadClientDataFromFile(ClientsFileName);
		cout << "Client Added Successfully , Do you want to Add more clients (Y = Yes,N = No) ? ";
		cin >> AddMore;

	} while (tolower(AddMore) == 'y');
}


bool DeleteClientByAccountNumber(string AccountNumberToBeFound, vector<sClient> & ALLDATA) {

	sClient client;
	char DeleteConfermition = 'y';

	if (FindClinetByAccountNumber(AccountNumberToBeFound, ALLDATA, client)) {
		PrintClientRecord(client);

		cout << "Are you sure you want to delete this client ? (y,n) : ";
		cin >> DeleteConfermition;

		if (tolower(DeleteConfermition) == 'y') {
			fstream MyFile;
			MyFile.open(ClientsFileName, ios::out);

			if (MyFile.is_open()) {
				for (sClient c : ALLDATA) {
					if(c.AccountNumber != client.AccountNumber)
						MyFile << ConvertRecordToLine(c) << endl;
				}
				ALLDATA = ReadClientDataFromFile(ClientsFileName);
				cout << "\nClinet deleted successfully" << endl;

				MyFile.close();
				return true;
			}

		}
	}

	else
		cout << "\nThe Client with Account Number (" << AccountNumberToBeFound << ") Not Found!";

	return false;
}

bool UpdateClientByAccountNumber(string AccountNumberToBeFound, vector<sClient>& ALLDATA) {

	sClient client;
	char UpdateConfermition = 'y';

	if (FindClinetByAccountNumber(AccountNumberToBeFound, ALLDATA, client)) {
		PrintClientRecord(client);

		cout << "Are you sure you want to update this client ? (y,n) : ";
		cin >> UpdateConfermition;

		if (tolower(UpdateConfermition) == 'y') {
			fstream MyFile;
			MyFile.open(ClientsFileName, ios::out);

			if (MyFile.is_open()) {
				for (sClient & c : ALLDATA) {
					if (client.AccountNumber == c.AccountNumber) {
						cout << "Enter PIN CODE : ";
						getline(cin >> ws, c.PINCODE);
						cout << "Enter Name : ";
						getline(cin, c.Name);
						cout << "Enter phone : ";
						getline(cin, c.Phone);
						cout << "Enter Account Balance : ";
						cin >> c.AccountBalance;
						MyFile << ConvertRecordToLine(c) << endl;
					}
					else
						MyFile << ConvertRecordToLine(c) << endl;

				}
				cout << "\nClinet Updated successfully" << endl;

				MyFile.close();
				return true;
			}

		}
	}

	else
		cout << "\nThe Client with Account Number (" << AccountNumberToBeFound << ") Not Found!";

	return false;
}

void PrintAllClientsData(vector <sClient> vClients)
{
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")Client(s).";
	cout <<"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout <<"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	for (sClient & Client : vClients)
	{
		PrintClientRecordForList(Client);
		cout << endl;
	}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

void ShowMainMenu() {
	system("cls");
	cout << "==========================================\n";
	cout << "\t\t Main menu Screen \n";
	cout << "==========================================\n"; 
	cout << "\t[1] Show Client List." << endl;
	cout << "\t[2] Add new Client. " << endl;
	cout << "\t[3] Delete Client." << endl;
	cout << "\t[4] Update Client Info." << endl;
	cout << "\t[5] Find client." << endl;
	cout << "\t[6] Transactions." << endl;
	cout << "\t[7] Exit." << endl;
	cout << "==========================================\n";


}

void ShowTransactionsMenu() {
	system("cls");
	cout << "==========================================\n";
	cout << "\t\t Transactions menu Screen \n";
	cout << "==========================================\n";
	cout << "\t[1] Deposit." << endl;
	cout << "\t[2] Withdraw. " << endl;
	cout << "\t[3] Total Balances." << endl;
	cout << "\t[4] Main menu." << endl;
	cout << "==========================================\n";


}


void EndScreen() {
	cout << "\n\nPress any key to go back to Main Menue..." << endl;
	system("pause>0");

}

void AddNewClinetScreen(vector<sClient> & AllClientsData){
	AddClients(AllClientsData);
}

void DeleteClinetScreen(vector<sClient> & AllClientsData) {
	cout << "\n--------------------------------\n";
	cout << "\tDelete Client Screen\n";
	cout << "--------------------------------\n\n";
	cout << "Plz enter Account Number : ";
	string AccountNumber = "";
	cin >> AccountNumber;
	DeleteClientByAccountNumber(AccountNumber, AllClientsData);
}
void UpdatelientScreen(vector<sClient>& AllClientsData) {
	cout << "\n--------------------------------\n";
	cout << "\tUpdate Client Screen\n";
	cout << "--------------------------------\n\n";
	cout << "Plz enter Account Number : ";
	string AccountNumber = "";
	cin >> AccountNumber;
	UpdateClientByAccountNumber(AccountNumber, AllClientsData);
}

void FindClientScreen(vector<sClient>& AllClientsData) {
	cout << "\n--------------------------------\n";
	cout << "\tFind Client Screen\n";
	cout << "--------------------------------\n\n";
	cout << "Plz enter Account Number : ";
	string AccountNumber = "";
	cin >> AccountNumber;
	sClient client;
	if (FindClinetByAccountNumber(AccountNumber, AllClientsData, client))
		PrintClientRecord(client);
	else
		cout << "\nClient [" << AccountNumber << "] Not Found !";
}

void Deposit(double DepositAmount,string AccountNumber,sClient & client , vector<sClient>& AllClientsData) {
	client.AccountBalance += DepositAmount;
	fstream MyFile;
	MyFile.open(ClientsFileName, ios::out);

	if (MyFile.is_open()) {
		for (sClient& c : AllClientsData) {
			if (AccountNumber == c.AccountNumber) {
				MyFile << ConvertRecordToLine(client) << endl;

			}
			else {
				MyFile << ConvertRecordToLine(c) << endl;

			}

		}
		MyFile.close();
	}
}

void DepositScreen(vector<sClient> & AllClientsData) {
	double DepositAmount = 0.0;
	string AccountNumber = "";
	sClient client;
	char confirmation = 'y';
	cout << "\n--------------------------------\n";
	cout << "\tDeposit Screen\n";
	cout << "--------------------------------\n\n";

	cout << "Plz enter Account Number : ";
	cin >> AccountNumber;
	while (!FindClinetByAccountNumber(AccountNumber, AllClientsData, client)) {
		cout << "\nClient [" << AccountNumber << "] Not Found ! \n";

		cout << "Plz enter Account Number : ";
		cin >> AccountNumber;
	}
	
		PrintClientRecord(client);
		cout << "\nPlz enter deposit amount : ";
		cin >> DepositAmount;
		if (DepositAmount > 0) {
			cout << "Are you sure : [y,n]";
			cin >> confirmation;
			if (tolower(confirmation) == 'y') {
				Deposit(DepositAmount,AccountNumber,client,AllClientsData);
					cout << "Done successfully !";
				

			}
		}
	

}

void WithDrawScreen(vector<sClient>& AllClientsData) {
	double WithDrawAmount = 0.0;
	string AccountNumber = "";
	sClient client;
	char confirmation = 'y';
	cout << "\n--------------------------------\n";
	cout << "\tWithDraw Screen\n";
	cout << "--------------------------------\n\n";

	cout << "Plz enter Account Number : ";
	cin >> AccountNumber;
	while (!FindClinetByAccountNumber(AccountNumber, AllClientsData, client)) {
		cout << "\nClient [" << AccountNumber << "] Not Found ! \n";

		cout << "Plz enter Account Number : ";
		cin >> AccountNumber;
	}

	PrintClientRecord(client);
	cout << "\nPlz enter withdraw amount : ";
	cin >> WithDrawAmount;
	while (WithDrawAmount > client.AccountBalance) {
		cout << "Amount Excedded ! \n\n";
		cout << "\nPlz enter withdraw amount : ";
		cin >> WithDrawAmount;

	}
		cout << "Are you sure : [y,n]";
		cin >> confirmation;
		if (tolower(confirmation) == 'y') {
			Deposit(-WithDrawAmount, AccountNumber, client, AllClientsData);
			cout << "Done successfully !";


		}
	
	
}

void TotalBalances(vector<sClient> & AllClientsData) {
	double sum = 0.0;
	cout << "\n\t\t\t\t\tClient List (" << AllClientsData.size() << ")Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	for (sClient& Client : AllClientsData)
	{
		sum += Client.AccountBalance;
		PrintClientRecordForTransactionsMenu(Client);
		cout << endl;
	}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "\t\t\t\t\tTotal Balances = " << sum << endl;
}

enTransactionsChoices TransactionsScreen(enTransactionsChoices choice) {
	vector<sClient> AllClientsData = ReadClientDataFromFile(ClientsFileName);

	switch (choice)
	{
	case enTransactionsChoices::DepositScreen:
		system("cls");
		DepositScreen(AllClientsData);
		EndScreen();
		break;
	case enTransactionsChoices::Withdraw:
		system("cls");
		WithDrawScreen(AllClientsData);
		EndScreen();
		break;
	case enTransactionsChoices::TotalBalances:
		system("cls");
		TotalBalances(AllClientsData);
		EndScreen();
		break;
	case enTransactionsChoices::MainMenu:
		return enTransactionsChoices::MainMenu;
	default:
		break;
	}

	return enTransactionsChoices::DepositScreen;
}

void TransactionsStart() {
	enTransactionsChoices MenuChoiec;
	do {
		ShowTransactionsMenu();
		MenuChoiec = (enTransactionsChoices)MyInput::ReadNumberValidInRange(1, 4, "Choose from [1 to 4] : ");
		MenuChoiec=TransactionsScreen(MenuChoiec);
	} while (MenuChoiec != enTransactionsChoices::MainMenu);
}

void MainMenuScreen(enMainMenuChoices choice) {
	
	vector<sClient> AllClientsData = ReadClientDataFromFile(ClientsFileName);
	switch (choice)
	{
	case enMainMenuChoices::ShowClientList:
		system("cls");
		PrintAllClientsData(AllClientsData);
		EndScreen();
		break;
	case enMainMenuChoices::AddNewClient:
		system("cls");
		AddNewClinetScreen(AllClientsData);
		EndScreen();
		break;
	case enMainMenuChoices::DeleteClient:
		system("cls");
		DeleteClinetScreen(AllClientsData);
		EndScreen();
		break;
	case enMainMenuChoices::UpdateClient:
		system("cls");
		UpdatelientScreen(AllClientsData);
		EndScreen();
		break;
	case enMainMenuChoices::FindClinet:
		system("cls");
		FindClientScreen(AllClientsData);
		EndScreen();
		break;
	case enMainMenuChoices::Transactions:
		system("cls");
		TransactionsStart();
	default:
		break;
	}

}

void Start() {

	short MenuChoiec = 0;
	do {
		ShowMainMenu();
		MenuChoiec = MyInput::ReadNumberValidInRange(1, 7, "Choose from [1 to 7] : ");
		MainMenuScreen((enMainMenuChoices)MenuChoiec);
	} while (MenuChoiec != 7);

}

int main()
{
	srand((unsigned)time(NULL));

	Start();

	return 0;
}

