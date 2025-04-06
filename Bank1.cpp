#include<iostream>
#include<string>
#include<iomanip>
#include<vector>
#include<fstream>

using namespace std;
string FileName = "Clients.txt";
string sep = "#//#";
struct stClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string PhoneNumber;
	double AccountBalance = 0;
	bool MarkedForDelete = false;
};
enum enMainMenue {eShowClients =1 , eAddNewClients=2 , eDeleteClient=3 , eUpdateClient=4 , eFindClient=5 ,eTransactions = 6 , eExit=7};
enum enTransaction { eDeposit = 1, eWithDraw = 2, eTotalBalances = 3, eMainMenue = 4 };
void ShowMainMenueScreen();
void ShowTransactionsScreen();
enMainMenue MainMenueChoice()
{
	short Choice = 0;
	do
	{
		cout << "Choose what do you want to do ? [1 to 7]  :   ";
		cin >> Choice;
	} while (Choice < 1 || Choice >7);
	
	return enMainMenue(Choice);
}
enTransaction TransactionChoice()
{
	short Choice = 0;
	do
	{
		cout << "Choose what do you want to do ? [1 to 4]  :   ";
		cin >> Choice;
	} while (Choice < 1 || Choice >4);
	return enTransaction(Choice);
}

string ReadAccountNumber(string Message)
{
	string AccountNumber;
	cout<< Message;
	cin >> AccountNumber;
	return AccountNumber;
}
vector<string> Split(string S)
{
	vector<string> vWords;
	short pos = 0;
	string word = "";
	while ((pos = S.find(sep)) != string::npos)
	{
		word = S.substr(0, pos);
		if (!word.empty())
		{
			vWords.push_back(word);
		}
		S = S.erase(0, pos + sep.length());
	}
	if (!S.empty())
	{
		vWords.push_back(S);
	}
	return vWords;

}
stClient ConvertDataLineToRecord(string DataLine)
{
	stClient Client;
	vector<string> vClients = Split(DataLine);
	Client.AccountNumber = vClients.at(0);
	Client.PinCode = vClients.at(1);
	Client.Name = vClients.at(2);
	Client.PhoneNumber = vClients.at(3);
	Client.AccountBalance = stod(vClients.at(4));
	return Client;

	
}
vector<stClient> LoadDataFromFile()
{
	vector<stClient> vClients;
	
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		stClient Client;
		string Line;
		while (getline(MyFile, Line))
		{
			Client = ConvertDataLineToRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;

}
void ShowClient(stClient Client)
{
	cout << "||  " << setw(15) << left << Client.AccountNumber << "||  " << setw(10) << left << Client.PinCode << "||  " << setw(40) << left << Client.Name << "||  " << setw(12) << left << Client.PhoneNumber << "||  " << setw(12) << left << Client.AccountBalance<<"||" << endl;
}
void ShowClientsScreen()
{
	vector<stClient> vClients = LoadDataFromFile();
	cout << "\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).\n";
	cout << " _____________________________________________________________________________________________________________\n";
	cout << " -------------------------------------------------------------------------------------------------------------\n";
	cout << "||  " << setw(15) << left << "Account Number" << "||  " << setw(10) << left << "Pin Code" << "||  " << left << setw(40) << "Client Name" << "||  " << left << setw(12) << "Phone" << "||  " << setw(12) << left << "Balance     ||" << endl;
	cout << " _____________________________________________________________________________________________________________\n";
	cout << " -------------------------------------------------------------------------------------------------------------\n";
	for (stClient& Client : vClients)
	{
		ShowClient(Client);
	}
	cout << " _____________________________________________________________________________________________________________\n";
	cout << " -------------------------------------------------------------------------------------------------------------\n";
}
stClient ReadClientInfo(string AccountNumber)
{
	
	stClient Client;
	Client.AccountNumber = AccountNumber;
	cout << "Enter Pin Code            :     ";
	cin >> Client.PinCode;
	cout << "Enter Name                :     ";
	cin.ignore();
	getline(cin, Client.Name);
	cout << "Enter Phone Number        :     ";
	cin >> Client.PhoneNumber;
	cout << "Enter Account Balance     :     ";
	cin >> Client.AccountBalance;
	return Client;
}
bool IsClientExit(string AccountNumber )
{
	
	vector<stClient> vClients = LoadDataFromFile();
	for (stClient& Client : vClients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			return true;
		}
	}
	return false;

}
bool FindClient(string AccountNumber, stClient& C)
{

	vector<stClient> vClients = LoadDataFromFile();
	for (stClient& Client : vClients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			C = Client;
			return true;
		}
	}
	return false;

}
string ConvertRecordToDataLine(stClient Client)
{
	string DataLine = "";
	DataLine += Client.AccountNumber + sep;
	DataLine += Client.PinCode + sep;
	DataLine += Client.Name + sep;
	DataLine += Client.PhoneNumber + sep;
	DataLine += to_string(Client.AccountBalance) ;
	return DataLine;

}
void SaveRecordToFile(stClient Client)
{
	fstream MyFile;
	MyFile.open(FileName, ios::app);
	if (MyFile.is_open())
	{
		string Line = ConvertRecordToDataLine(Client);
		MyFile << Line << endl;
		MyFile.close();
	}
}
void AddNewClient()
{
	string AccountNumber = ReadAccountNumber("Enter Account Number      :     ");
	while (IsClientExit(AccountNumber))
	{
		cout << "\nClient With Account Number [" << AccountNumber << "] Already Exists , Please Enter anohter one   :    ";
		cin >> AccountNumber;
	}
	stClient Client = ReadClientInfo(AccountNumber);
	SaveRecordToFile(Client);
}
void AddNewClients()
{
	char Answer;
	do
	{
		system("cls");
		cout << "Adding New Client  :\n\n";
		AddNewClient();
		cout << "Client Added SuccessFully , Do you want to Add more Clients (Y/N)   :   ";
		cin >> Answer;
		
	} while (toupper(Answer) == 'Y');
	
	

}
void ShowAddNewClientsScreen()
{
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	cout << "\t\tAdd New Clients Screen\n";
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	AddNewClients();

}
void PrintClientData(stClient Client)
{
	cout << "\nThe Following Are the Client Details     :     \n";
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	cout << "Account Number       :    " << Client.AccountNumber << endl;
	cout << "Pin Code             :    " << Client.PinCode << endl;
	cout << "Full Name            :    " << Client.Name << endl;
	cout << "Phone Number         :    " << Client.PhoneNumber << endl;
	cout << "Account Balance      :    " << Client.AccountBalance << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";

}

void SaveDataToFile(vector<stClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open())
	{
		for (stClient& Client : vClients)
		{
			if (Client.MarkedForDelete == false)
			{
				string DataLine = ConvertRecordToDataLine(Client);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
}
void MarkedForDelete(vector<stClient> &vClients, string AccountNumber)
{
	for (stClient& Client : vClients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			Client.MarkedForDelete=  true;
			return;
		}
	}
	
}
void DeleteClient()
{
	stClient Client;
	string AccountNumber = ReadAccountNumber("Enter Account Number      :     ");
	if (FindClient(AccountNumber , Client))
	{
		PrintClientData(Client);
		char Answer;
		cout << "\nAre you sure you want to Delete this Client (Y/N)   :    ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			vector<stClient> vClients = LoadDataFromFile();
			MarkedForDelete(vClients, AccountNumber);
			SaveDataToFile(vClients);
			cout << "Client Deleted SuccessFully.\n\n";
		}
		
		
	}
	else
	{
		cout << "Client With Account Number [" << AccountNumber << "] was not Found :-(\n\n";
	}
	
}
void ShowDeleteClientScreen()
{
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	cout << "\t\tDelete Client Screen\n";
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	DeleteClient();
}
void UpdateDataInFile(vector<stClient> &vClients, stClient C)
{
	for (stClient& Client : vClients)
	{
		if (Client.AccountNumber == C.AccountNumber)
		{
			Client = C;
			return;
		}
	}
}
void UpdateClient()
{
	stClient Client;
	string AccountNumber = ReadAccountNumber("Enter Account Number      :     ");
	if (FindClient(AccountNumber, Client))
	{
		PrintClientData(Client);
		char Answer;
		cout << "\nAre you sure you want to Update this Client (Y/N)   :    ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Client = ReadClientInfo(AccountNumber);
			vector<stClient> vClients = LoadDataFromFile();
			UpdateDataInFile(vClients,Client);
			SaveDataToFile(vClients);
			cout << "Client Updated SuccessFully.\n\n";
		}


	}
	else
	{
		cout << "Client With Account Number [" << AccountNumber << "] was not Found :-(\n\n";
	}
}
void ShowUpdateClientScreen()
{
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	cout << "\t\tUpdate Client Screen\n";
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	UpdateClient();
}
void ShowFindClientScreen()
{
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	cout << "\t\Find Client Screen\n";
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	stClient Client;
	string AccountNumber = ReadAccountNumber("Enter Account Number      :     ");
	if (FindClient(AccountNumber, Client))
	{
		PrintClientData(Client);
	}
	else
	{
		cout << "Client With Account Number [" << AccountNumber << "] was not Found :-(\n\n";
	}
}
float ReadDeposit(string Message)
{
	float Deposit = 0;
	cout << Message;
	cin >> Deposit;
	return Deposit;
}
void Deposit(double Deposit,vector<stClient> &vClients ,  stClient& C)
{
	for (stClient& Client : vClients)
	{
		if (Client.AccountNumber == C.AccountNumber)
		{
			Client.AccountBalance += Deposit;
			return;
		}
	}
}
void PerformDeposit()
{
	string AccountNumber = ReadAccountNumber("Please Enter Account Number   :    ");
	stClient Client;
	while (!FindClient(AccountNumber, Client))
	{
		cout << "Client With [" << AccountNumber << "] Does not Exist\n";
		cout << "Please Enter it Again   :    ";
		cin >> AccountNumber;
	}
	PrintClientData(Client);
	double deposit = ReadDeposit("Please Enter Deposit Amount   :    ");
	char Answer;
	cout << "\n\n Are you sure you want to Perform this Transaction (Y/N)   :    ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		vector<stClient> vClients = LoadDataFromFile();
		Deposit(deposit, vClients, Client);
		SaveDataToFile(vClients);
		cout << "\n Money Deposited SuccessFully\n\n";
	}
}
void ShowDepositScreen()
{
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	cout << "\t\tDeposit Screen\n";
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	PerformDeposit();


}
void PerformWithDraw()
{
	string AccountNumber = ReadAccountNumber("Please Enter Account Number   :    ");
	stClient Client;
	while (!FindClient(AccountNumber, Client))
	{
		cout << "Client With [" << AccountNumber << "] Does not Exist\n";
		cout << "Please Enter it Again   :    ";
		cin >> AccountNumber;
	}
	PrintClientData(Client);
	double WithDraw = ReadDeposit("Please Enter Deposit Amount   :    ");
	while (WithDraw > Client.AccountBalance)
	{
		cout << "\nAmount Exceeds the Balance , you can WithDraw Up to " << Client.AccountBalance << endl;
		cout << "Please Enter another Amount   :    ";
		cin >> WithDraw;
	}
	char Answer;
	cout << "\n\n Are you sure you want to Perform this Transaction (Y/N)   :    ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		vector<stClient> vClients = LoadDataFromFile();
		Deposit(-1*WithDraw, vClients, Client);
		SaveDataToFile(vClients);
		cout << "\n Money WithDrew SuccessFully\n\n";
	}
}
void ShowWithDrawScreen()
{
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	cout << "\t\WithDraw Screen\n";
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	PerformWithDraw();
}
void ShowTotalBalance(stClient Client)
{
	cout << "||  " << setw(15) << left << Client.AccountNumber << "||  " << setw(40) << left << Client.Name << "||  " << setw(20) << left << Client.AccountBalance<<"\t\t\t    ||" << endl;
}
float TotalBalances(vector<stClient> vClients)
{
	float TotalBalances = 0;
	for (stClient& Client : vClients)
	{
		TotalBalances += Client.AccountBalance;
	}
	return TotalBalances;
}
void ShowTotalBalancesScreen()
{
	vector<stClient> vClients = LoadDataFromFile();
	cout << "\t\t\t\tClient List (" << vClients.size() << ") Client(s).\n";
	cout << " ____________________________________________________________________________________________________________\n";
	cout << " ------------------------------------------------------------------------------------------------------------\n";
	cout << "||  " << setw(15) << left << "Account Number" << "||  " << left << setw(40) << "Client Name" << "||  " << setw(20) << left << "Balance\t\t\t\t    ||" << endl;
	cout << " ____________________________________________________________________________________________________________\n";
	cout << " ------------------------------------------------------------------------------------------------------------\n";
	for (stClient& Client : vClients)
	{
		ShowTotalBalance(Client);
	}
	cout << " ____________________________________________________________________________________________________________\n";
	cout << " ------------------------------------------------------------------------------------------------------------\n\n";
	cout << "\t\t\t\tTotal Balances  =   " << std::fixed<< TotalBalances(vClients) <<endl<< endl;
}
void GoBackToTransactionMenueScreen()
{
	cout << "\nPlease Enter Any Keys to go back to The Main Menue Screen...\n\n";
	system("pause");
	ShowTransactionsScreen();
}
void PerformTransactionActions(enTransaction Choice)
{
	switch (Choice)
	{
	case enTransaction::eDeposit:
		system("cls");
		ShowDepositScreen();
		GoBackToTransactionMenueScreen();
		break;
	case enTransaction::eWithDraw:
		system("cls");
		ShowWithDrawScreen();
		GoBackToTransactionMenueScreen();
		break;
	case enTransaction::eTotalBalances:
		system("cls");
		ShowTotalBalancesScreen();
		GoBackToTransactionMenueScreen();
		break;
	case enTransaction::eMainMenue:
		system("cls");
		ShowMainMenueScreen();
		break;

	}
}
void ShowTransactionsScreen()
{
	system("cls");
	cout << "====================================================================\n";
	cout << "\t\t\tTransactions Menue Screen\n";
	cout << "====================================================================\n";
	cout << "\t\t[1] Deposit.\n";
	cout << "\t\t[2] WithDraw.\n";
	cout << "\t\t[3] TotalBalances.\n";
	cout << "\t\t[4] Main Menue.\n";
	cout << "====================================================================\n\n";
	PerformTransactionActions(enTransaction(TransactionChoice()));
}
void ShowEndScreen()
{
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	cout << "\t\tProgram Ends :-) \n";
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";
}
void GoBackToMainMenueScreen()
{
	
	cout << "\nPlease Enter Any Keys to go back to The Main Menue Screen...\n\n";
	system("pause");
	ShowMainMenueScreen();
}
void PerformMenueActions(enMainMenue Choice)
{
	switch (Choice)
	{
	case enMainMenue::eShowClients:
	{
		system("cls");
		ShowClientsScreen();
		GoBackToMainMenueScreen();
		break;
	}
	case enMainMenue::eAddNewClients:
	{
		system("cls");
		ShowAddNewClientsScreen();
		GoBackToMainMenueScreen();

		break;
	}
	case enMainMenue::eDeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenueScreen();
		break;
	case enMainMenue::eUpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenueScreen();
		break;
	case enMainMenue::eFindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenueScreen();
		break;
	case enMainMenue::eTransactions:
		system("cls");
		ShowTransactionsScreen();
		GoBackToMainMenueScreen();
		break;
	case enMainMenue::eExit:
		system("cls");
		ShowEndScreen();
		GoBackToMainMenueScreen();
		break;

	}
}
void ShowMainMenueScreen()
{
	system("cls");
	cout << "====================================================================\n";
	cout << "\t\t\tMain Menue Screen\n";
	cout << "====================================================================\n\n";
	cout << "\t\t[1] Show Client List.\n";
	cout << "\t\t[2] Add New Clients.\n";
	cout << "\t\t[3] Delete Client.\n";
	cout << "\t\t[4] Update Client Info.\n";
	cout << "\t\t[5] Find Client.\n";
	cout << "\t\t[6] Transactions.\n";
	cout << "\t\t[7] Exit.\n";
	cout << "====================================================================\n\n";
	PerformMenueActions(MainMenueChoice());

}


int main()
{
	ShowMainMenueScreen();
}