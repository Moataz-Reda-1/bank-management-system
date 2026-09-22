#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance = 0;
    bool MarkForDelete = false;
};

struct stUser
{
    string Name;
    string Password;
    int Permissions;
    bool MarkForDelete = false;
};

enum enChoices {
    enShowAllClients = 1,
    enAddClients = 2,
    enDeleteClient = 3,
    enUpdateClientInfo = 4,
    enFindClient = 5,
    enTransactions = 6,
    enManageUsers = 7,
    enLogOut = 8
};

enum enPermissions
{
    pShowClients = 1,
    pAddClient = 2,
    pDeleteClient = 4,
    pUpdateClient = 8,
    pFindClient = 16,
    pTransactions = 32,
    pManageUsers = 64
};

enum enTransChoices {
    eDiposite = 1,
    eWithDraw = 2,
    eBalances = 3,
    eMainMenue = 4,
};

enum enUsersMenuChoices
{
    eListUsers = 1,
    eAddUser = 2,
    eDeleteUser = 3,
    eUpdateUser = 4,
    eFindUser = 5,
    eMainMenu = 6
};


const string ClientsFile = "E:\\Course 8\\Clients.txt";
const string UsersFile = "E:\\Course 8\\Users.txt";

stUser CurrentUser;

void cls()
{
    system("cls");
}

void ShowMainMenue()
{
    system("cls");
    cout << "===========================================" << endl;
    cout << "            Main Menue Screen" << endl;
    cout << "===========================================" << endl;
    cout << "\t[1] Show Client List. " << endl;
    cout << "\t[2] Add New Client. " << endl;
    cout << "\t[3] Delete Client. " << endl;
    cout << "\t[4] Update Client Info. " << endl;
    cout << "\t[5] Find Client. " << endl;
    cout << "\t[6] Transations. " << endl;
    cout << "\t[7] Manage Users. " << endl;
    cout << "\t[8] LogOut. " << endl;
    cout << "===========================================" << endl;
}

string ReadUserName()
{
    string Name;
    cout << "Enter Username ? ";
    getline(cin >> ws, Name);
    return Name;
}

string ReadPassword()
{
    string Password;
    cout << "Enter Password ? ";
    cin >> Password;
    return Password;
}

stUser ReadUserInfo()
{
    stUser User;
    User.Name = ReadUserName();
    User.Password = ReadPassword();
    return User;
}

enChoices ReadMainMenuChoice()
{
    short Choice = 0;
    do
    {
        cout << "Choose what do you want to do ? [1 to 8]? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 8);
    return enChoices(Choice);
}

enUsersMenuChoices ReadUsersMenueChoice()
{
    short Choice = 0;
    do
    {
        cout << "Choose what do you want to do ? [1 to 6]? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 6);
    return enUsersMenuChoices(Choice);
}

bool IsFound(string AccountNumber, vector<stClient>& vClients, stClient& Client)
{
    for (stClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

bool IsClientExists(string AccountNumber, vector<stClient>& vClients)
{
    for (stClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
            return true;
    }
    return false;
}

bool IsFound(string Name, vector<stUser>& vUsers, stUser& User)
{
    for (stUser& U : vUsers)
    {
        if (U.Name == Name)
        {
            User = U;
            return true;
        }
    }
    return false;
}

bool IsUserExists(string Username, vector<stUser>& vUsers)
{
    for (stUser& User : vUsers)
    {
        if (User.Name == Username)
            return true;
    }
    return false;
}

vector<string> SplitString(string str, string delim)
{
    vector<string> Words;
    size_t pos = 0;

    while ((pos = str.find(delim)) != std::string::npos)
    {
        string sword = str.substr(0, pos);

        if (sword != "")
        {
            Words.push_back(sword);
        }
        str.erase(0, pos + delim.length());
    }
    if (str != "")
    {
        Words.push_back(str);
    }
    return Words;
}

stClient ConvertLineDataToRecord(string LineData, string Separator = "#//#")
{
    stClient Client;
    vector<string> Data = SplitString(LineData, Separator);

    Client.AccountNumber = Data[0];
    Client.PinCode = Data[1];
    Client.Name = Data[2];
    Client.Phone = Data[3];
    Client.AccountBalance = stod(Data[4]);

    return Client;
}

stUser ConvertUserLineDataToRecord(string LineData, string Separator = "#//#")
{
    stUser User;
    vector<string> Data = SplitString(LineData, Separator);

    if (Data.size() > 0) User.Name = Data[0];
    if (Data.size() > 1) User.Password = Data[1];
    if (Data.size() > 2) User.Permissions = stoi(Data[2]);

    return User;
}

string ConvertRecordToLine(stClient ClientData, string Separator = "#//#")
{
    string S1 = "";
    S1 += ClientData.AccountNumber + Separator;
    S1 += ClientData.PinCode + Separator;
    S1 += ClientData.Name + Separator;
    S1 += ClientData.Phone + Separator;
    S1 += to_string(ClientData.AccountBalance) + Separator;

    return S1;
}

string ConvertRecordToLine(stUser User, string Separator = "#//#")
{
    string S1 = "";
    S1 += User.Name + Separator;
    S1 += User.Password + Separator;
    S1 += to_string(User.Permissions);

    return S1;
}

vector<stClient> LoadDataFromFileToVector(string FileName)
{
    vector<stClient> vClients;
    stClient Client;
    fstream File;
    File.open(FileName, ios::in);
    if (File.is_open())
    {
        string Line;
        while (getline(File, Line))
        {
            if (Line != "")
            {
                Client = ConvertLineDataToRecord(Line);
                vClients.push_back(Client);
            }
        }
        File.close();
    }
    return vClients;
}

vector<stUser> LoadUserDataFromFileToVector(string FileName)
{
    vector<stUser> vUsers;
    fstream File;
    File.open(FileName, ios::in);
    if (File.is_open())
    {
        string Line;
        while (getline(File, Line))
        {
            if (Line != "")
            {
                stUser User = ConvertUserLineDataToRecord(Line);
                vUsers.push_back(User);
            }
        }
        File.close();
    }
    return vUsers;
}

void PrintOneClient(stClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(30) << left << Client.Name;
    cout << "| " << setw(18) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintUserCard(stUser User)
{
    cout << "| " << setw(30) << left << User.Name;
    cout << "| " << setw(18) << left << User.Password;
    cout << "| " << setw(12) << left << User.Permissions;
}

stClient ReadNewClient(vector<stClient>& vClients)
{
    stClient Client;
    cout << "Enter Account Number ? ";
    getline(cin >> ws, Client.AccountNumber);

    while (IsClientExists(Client.AccountNumber, vClients))
    {
        cout << "\nClient With [" << Client.AccountNumber
            << "] already exists, Enter Another Account Number ? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter PinCode ? ";
    getline(cin, Client.PinCode);
    cout << "Enter Name ? ";
    getline(cin, Client.Name);
    cout << "Enter Phone ? ";
    getline(cin, Client.Phone);
    cout << "Enter Account Balance ? ";
    cin >> Client.AccountBalance;
    return Client;
}

void SaveVectorToFile(string FileName, vector<stClient>& vClients)
{
    fstream File;
    File.open(FileName, ios::out);
    if (File.is_open())
    {
        for (stClient& Client : vClients)
        {
            if (Client.MarkForDelete == false)
            {
                string Line = ConvertRecordToLine(Client);
                File << Line << endl;
            }
        }
        File.close();
    }
}

void SaveVectorToFile(string FileName, vector<stUser>& vUsers)
{
    fstream File;
    File.open(FileName, ios::out);
    if (File.is_open())
    {
        for (stUser& User : vUsers)
        {
            if (User.MarkForDelete == false)
            {
                string Line = ConvertRecordToLine(User);
                File << Line << endl;
            }
        }
        File.close();
    }
}

bool MarkForDelete(string AccountNumber, vector<stClient>& vClients)
{
    for (stClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

bool MarkForDelete(string Username, vector<stUser>& vUsers)
{
    for (stUser& U : vUsers)
    {
        if (U.Name == Username)
        {
            U.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

void PrintAccountDetails(stClient Client)
{
    cout << "\nThe following are the client details : \n" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Acount Number   : " << Client.AccountNumber << endl;
    cout << "PinCode         : " << Client.PinCode << endl;
    cout << "Name            : " << Client.Name << endl;
    cout << "Phone           : " << Client.Phone << endl;
    cout << "Account Balance : " << Client.AccountBalance << "$" << endl;
    cout << "--------------------------------------------" << endl;
}

void PrintUserDetails(stUser User)
{
    cout << "\nThe following are the User details : \n" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Username    : " << User.Name << endl;
    cout << "Password    : " << User.Password << endl;
    cout << "Permissions : " << User.Permissions << endl;
    cout << "--------------------------------------------" << endl;
}

void PrintAccountDetails(string AccountNumber, vector<stClient>& vClients)
{
    for (stClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
            PrintAccountDetails(C);
    }
}

stClient ChangeClientRecord(string AccountNumber)
{
    stClient Client;
    Client.AccountNumber = AccountNumber;

    cout << "\nEnter PinCode ? ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name ? ";
    getline(cin, Client.Name);
    cout << "Enter Phone ? ";
    getline(cin, Client.Phone);
    cout << "Enter Account Balance ? ";
    cin >> Client.AccountBalance;

    return Client;
}

void PrintClientsBalancesCard(stClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(30) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAllCLients(vector<stClient>& vClients)
{
    cls();
    cout << "\n\t\t\tClient List ( " << sizeof(vClients) << " )  Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(30) << "Client Name";
    cout << "| " << left << setw(18) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (stClient& Client : vClients)
    {
        if (Client.MarkForDelete == false)
        {
            PrintOneClient(Client);
            cout << endl;
        }
    }
    cout << "________________________________________________";
    cout << "________________________________________________" << endl;
}

void ShowAddNewClientsScreen()
{
    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "         Adding New Clients Screen      " << endl;
    cout << "-----------------------------------------" << endl;
}

void AddNewClient(vector<stClient>& vClients)
{
    stClient Client;
    cout << "Add New Client : \n\n";
    Client = ReadNewClient(vClients);
    vClients.push_back(Client);
    SaveVectorToFile(ClientsFile, vClients);
}

void AddNewClients(vector<stClient>& vClients)
{
    char AddNew = 'Y';
    do
    {
        ShowAddNewClientsScreen();
        AddNewClient(vClients);
        cout << "\nClient Added Successfully, Do You Want To Add More Clients ? (Y / N) ? ";
        cin >> AddNew;
    } while (toupper(AddNew) == 'Y');
}

void ShowDeleteClientScreen()
{
    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "             Delete Client Screen        " << endl;
    cout << "-----------------------------------------" << endl;
}

bool DeleteClient(vector<stClient>& vClients)
{
    string AccountNumber;
    stClient Client;
    char Delete = 'N';

    ShowDeleteClientScreen();
    cout << "\nPlease Enter Account Number ? ";
    cin >> AccountNumber;
    if (IsFound(AccountNumber, vClients, Client))
    {
        PrintAccountDetails(Client);
        cout << "\n\nAre you sure you want to delete this client ? (Y/ N) ? ";
        cin >> Delete;
    }
    else
        cout << "\nClient With Account Number [" << AccountNumber << "] is Not Found ! " << endl;

    if (toupper(Delete) == 'Y')
    {
        MarkForDelete(AccountNumber, vClients);
        SaveVectorToFile(ClientsFile, vClients);
        cout << "\nClient Deleted Successfully.\n" << endl;
        return true;
    }
    return false;
}

void ShowUpdateClientScreen()
{
    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "             Update Client Screen        " << endl;
    cout << "-----------------------------------------" << endl;
}

bool UpdateClientInfo(vector<stClient>& vClients)
{
    string AccountNumber;
    stClient Client;
    char Update = 'N';

    ShowUpdateClientScreen();
    cout << "\nPlease Enter Account Number ? ";
    cin >> AccountNumber;
    if (IsFound(AccountNumber, vClients, Client))
    {
        PrintAccountDetails(Client);
        cout << "\n\nAre you sure you want to Update this client ? (Y/ N) ? ";
        cin >> Update;
    }
    else
        cout << "\nClient With Account Number [" << AccountNumber << "] is Not Found ! " << endl;

    if (toupper(Update) == 'Y')
    {
        for (stClient& Client : vClients)
        {
            if (Client.AccountNumber == AccountNumber)
            {
                Client = ChangeClientRecord(AccountNumber);
                break;
            }
        }
        SaveVectorToFile(ClientsFile, vClients);
        cout << "\nClient Updated Successfully.\n" << endl;
        return true;
    }
    return false;
}

void ShowFindClientScreen()
{
    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "             Find Client Screen        " << endl;
    cout << "-----------------------------------------" << endl;
}

void FindClient(vector<stClient>& vClients)
{
    stClient Client;
    string AccountNumber;

    ShowFindClientScreen();
    cout << "\nEnter Account Number? ";
    cin >> AccountNumber;
    if (IsFound(AccountNumber, vClients, Client))
        PrintAccountDetails(Client);
    else
        cout << "\nClient With Account Number [" << AccountNumber << "] is Not Found ! " << endl;
}

void ShowDepositeScreen()
{
    cls();
    cout << "-----------------------------------------" << endl;
    cout << "            Deposite Screen        " << endl;
    cout << "-----------------------------------------" << endl;
}

void ShowWithDrawScreen()
{
    cls();
    cout << "-----------------------------------------" << endl;
    cout << "           WithDraw Screen        " << endl;
    cout << "-----------------------------------------" << endl;
}

void ShowTransactionsScreen()
{
    system("cls");
    cout << "===========================================" << endl;
    cout << "             Transcations Screen          " << endl;
    cout << "===========================================" << endl;
    cout << "\t[1] Deposite. " << endl;
    cout << "\t[2] WithDraw. " << endl;
    cout << "\t[3] Total Balances. " << endl;
    cout << "\t[4] MainMenue." << endl;
    cout << "===========================================" << endl;
}

enTransChoices ReadTransactionsChoice()
{
    short Choice = 0;
    do
    {
        cout << "What do you want to do ? [ 1 to 4 ] ? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 4);
    return enTransChoices(Choice);
}

bool ReadDeposite(const string AccountNumber, vector<stClient>& vClients)
{
    double Amount = 0;
    cout << "Please Enter Deposite amount ? ";
    cin >> Amount;

    char Answer = 'N';
    cout << "\nAre You Sure You Want To Perform this Transaction ? (Y / N) ? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
    {
        for (stClient& Client : vClients)
        {
            if (Client.AccountNumber == AccountNumber)
            {
                Client.AccountBalance += Amount;
                cout << "\nDone Succssefully, New Balance = " << Client.AccountBalance << endl;
                return true;
            }
        }
    }

    return false;
}

bool Deposite(vector<stClient>& vClients)
{
    string AccountNumber;
    do
    {
        cout << "\nPlease Enter Account Number? ";
        cin >> AccountNumber;
        if (!IsClientExists(AccountNumber, vClients))
        {
            cout << "\nClient With [" << AccountNumber << "] does not exist ." << endl;
        }
    } while ((IsClientExists(AccountNumber, vClients) == false));

    PrintAccountDetails(AccountNumber, vClients);

    return ReadDeposite(AccountNumber, vClients);
}

bool ReadWithDraw(const string AccountNumber, vector<stClient>& vClients)
{
    double Amount = 0;
    cout << "Please Enter WithDraw amount ? ";
    cin >> Amount;

    for (stClient& Client : vClients)
    {
        if (Client.AccountNumber == AccountNumber)
        {
            while (Client.AccountBalance - Amount < 0)
            {
                cout << "\nAmount Exceeds the balance, You can with draw upto : " << Client.AccountBalance << endl;
                cout << "\nPlease Enter another amount ? ";
                cin >> Amount;
            }

            char Answer = 'N';
            cout << "\nAre You Sure You Want To Perform this Transaction ? (Y / N) ? ";
            cin >> Answer;

            if (toupper(Answer) == 'Y')
            {
                Client.AccountBalance -= Amount;
                cout << "\nDone Succssefully, New Balance = " << Client.AccountBalance << endl;
                return true;
            }
            break;
        }
    }

    return false;
}

bool WithDraw(vector<stClient>& vClients)
{
    string AccountNumber;
    do
    {
        cout << "\nPlease Enter Account Number? ";
        cin >> AccountNumber;
        if (!IsClientExists(AccountNumber, vClients))
        {
            cout << "\nClient With [" << AccountNumber << "] does not exist ." << endl;
        }
    } while ((IsClientExists(AccountNumber, vClients) == false));

    PrintAccountDetails(AccountNumber, vClients);
    return ReadWithDraw(AccountNumber, vClients);
}

double SumOfBalances(vector<stClient>& vClients)
{
    double Sum = 0;
    for (stClient& C : vClients)
    {
        if (C.MarkForDelete == false)
            Sum += C.AccountBalance;
    }
    return Sum;
}

void ShowTotalBalancesScreen(vector<stClient>& vClients)
{

    cout << "\n\t\t\tClient List ( " << sizeof(vClients) << " )  Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(30) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    for (stClient& Client : vClients)
    {
        if (Client.MarkForDelete == false)
        {
            PrintClientsBalancesCard(Client);
            cout << endl;
        }
    }
    cout << "________________________________________________";
    cout << "________________________________________________" << endl;
    cout << "\n\t\tTotal Balances = " << SumOfBalances(vClients) << "$" << endl;
}

void PerformTransactionsOptions(vector<stClient>& vClients)
{
    ShowTransactionsScreen();
    enTransChoices Choice = ReadTransactionsChoice();

    while (Choice != eMainMenue)
    {
        switch (Choice)
        {
        case eDiposite:
        {
            ShowDepositeScreen();
            if (Deposite(vClients))
                SaveVectorToFile(ClientsFile, vClients);
            break;
        }
        case eWithDraw:
        {
            ShowWithDrawScreen();
            if (WithDraw(vClients))
                SaveVectorToFile(ClientsFile, vClients);
            break;
        }
        case eBalances:
        {
            cls();
            ShowTotalBalancesScreen(vClients);
            break;
        }
        }
        cout << "\nPress Any Key To Go Back To The Transactions Menue...";
        system("pause>0");
        ShowTransactionsScreen();
        Choice = ReadTransactionsChoice();
    }
}

int ReadPermissionsSet()
{
    int Permissions = 0;
    char Answer = 'N';

    cout << "\nDo you want to give full access ? (Y/N) ? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
        return -1;
    else

    {
        cout << "\nShow Client List ? (Y/N) ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
            Permissions |= pShowClients;

        cout << "\nAdd  New Client ? (Y/N) ?";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
            Permissions |= pAddClient;

        cout << "\nDelete Client ? (Y/N) ?";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
            Permissions |= pDeleteClient;

        cout << "\nUpdate Client ? (Y/N) ?";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
            Permissions |= pUpdateClient;

        cout << "\nFind Client ? (Y/N) ?";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
            Permissions |= pFindClient;

        cout << "\nTransations ? (Y/N) ?";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
            Permissions |= pTransactions;

        cout << "\nManage Users ? (Y/N) ?";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
            Permissions |= pManageUsers;

    }
    return Permissions;
}

stUser ChangeUserRecord(string Username)
{
    stUser User;
    User.Name = Username;

    cout << "\nEnter PassWord ? ";
    getline(cin >> ws, User.Password);

    char Answer = 'N';
    cout << "\nDo you want to give full Access ? ( Y / N ) ? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        User.Permissions = -1;
    else
        User.Permissions = ReadPermissionsSet();
    return User;
}

int GetPermission(enChoices Choice)
{
    switch (Choice)
    {
    case enShowAllClients:   return pShowClients;
    case enAddClients:       return pAddClient;
    case enDeleteClient:     return pDeleteClient;
    case enUpdateClientInfo: return pUpdateClient;
    case enFindClient:       return pFindClient;
    case enTransactions:     return pTransactions;
    case enManageUsers:      return pManageUsers;
    default:                 return 0;
    }
}

bool CheckAccess(enChoices Choice)
{
    if (CurrentUser.Permissions == -1)
        return true;

    int TargetPermission = GetPermission(Choice);

    if (TargetPermission == 0)
        return true;

    return (CurrentUser.Permissions & TargetPermission) != 0;
}

void ShowUsersList(vector<stUser>& vUsers)
{
    cout << "\n\t\t\tUser List ( " << vUsers.size() << " )  User(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(30) << "Username";
    cout << "| " << left << setw(18) << "Password";
    cout << "| " << left << setw(12) << "Permissions";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (stUser& User : vUsers)
    {
        if (User.MarkForDelete == false)
        {
            PrintUserCard(User);
            cout << endl;
        }
    }
    cout << "________________________________________________";
    cout << "________________________________________________" << endl;
}

void ShowAddNewUsersScreen()
{
    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "         Adding New Users Screen      " << endl;
    cout << "-----------------------------------------" << endl;
}

stUser ReadNewUser(vector<stUser>& vUsers)
{
    stUser User;
    cout << "Enter Username ? ";
    getline(cin >> ws, User.Name);

    while (IsUserExists(User.Name, vUsers))
    {
        cout << "\nUser With [" << User.Name << "] already exists, Enter Another Username ? ";
        getline(cin >> ws, User.Name);
    }

    cout << "Enter PassWord ? ";
    getline(cin, User.Password);

    User.Permissions = ReadPermissionsSet();

    return User;
}

void AddNewUser(vector<stUser>& vUsers)
{
    stUser User;
    cout << "Add New User : \n\n";
    User = ReadNewUser(vUsers);
    vUsers.push_back(User);
    SaveVectorToFile(UsersFile, vUsers);
}

void AddNewUsers(vector<stUser>& vUsers)
{
    char AddNew = 'Y';
    do
    {
        ShowAddNewUsersScreen();
        AddNewUser(vUsers);
        cout << "\nUser Added Successfully, Do You Want To Add More Users ? (Y / N) ? ";
        cin >> AddNew;
    } while (toupper(AddNew) == 'Y');
}

void ShowDeleteUserScreen()
{
    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "             Delete User Screen        " << endl;
    cout << "-----------------------------------------" << endl;
}

bool DeleteUser(vector<stUser>& vUsers)
{
    string Name;
    stUser User;
    char Delete = 'N';

    ShowDeleteUserScreen();
    cout << "\nPlease Enter Username ? ";
    cin >> Name;
    if (CurrentUser.Permissions == -1 )
    {
        cout << "\nYou Can Not Delete This User .\n";
        return false;
    }

    if (IsFound(Name, vUsers, User))
    {
        PrintUserDetails(User);
        cout << "\n\nAre you sure you want to delete this User ? (Y/ N) ? ";
        cin >> Delete;
    }
    else
        cout << "\nUser With Username [" << Name << "] is Not Found ! " << endl;

    if (toupper(Delete) == 'Y')
    {
        MarkForDelete(Name, vUsers);
        SaveVectorToFile(UsersFile, vUsers);
        cout << "\nUser Deleted Successfully.\n" << endl;
        return true;
    }
    return false;
}

void ShowUpdateUserScreen()
{
    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "             Update User Screen        " << endl;
    cout << "-----------------------------------------" << endl;
}

bool UpdateUser(vector<stUser>& vUsers)
{
    string Name;
    stUser User;
    char Update = 'N';

    ShowUpdateUserScreen();
    cout << "\nPlease Enter Username ? ";
    cin >> Name;
    if (IsFound(Name, vUsers, User))
    {
        PrintUserDetails(User);
    }
    else
        cout << "\nUser With Username [" << Name << "] is Not Found ! " << endl;

    if (toupper(Update) == 'Y')
    {
        for (stUser& U : vUsers)
        {
            if (U.Name == Name)
            {
                U = ChangeUserRecord(Name);
                break;
            }
        }
        SaveVectorToFile(UsersFile, vUsers);
        cout << "\nUser Updated Successfully.\n" << endl;
        return true;
    }
    return false;
}

void ShowFindUserScreen()
{
    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "             Find User Screen        " << endl;
    cout << "-----------------------------------------" << endl;
}

void FindUser(vector<stUser>& vUsers)
{
    stUser User;
    string Name;

    ShowFindUserScreen();
    cout << "\nEnter Username ? ";
    cin >> Name;
    if (IsFound(Name, vUsers, User))
        PrintUserDetails(User);
    else
        cout << "\nUser With Username [" << Name << "] is Not Found ! " << endl;
}

void ShowManageUsersMenu()
{
    system("cls");
    cout << "===========================================" << endl;
    cout << "         Manage Users Menue Screen" << endl;
    cout << "===========================================" << endl;
    cout << "\t[1] List Users. " << endl;
    cout << "\t[2] Add New User. " << endl;
    cout << "\t[3] Delete User. " << endl;
    cout << "\t[4] Update User. " << endl;
    cout << "\t[5] Find User. " << endl;
    cout << "\t[6] Main Menu. " << endl;
    cout << "===========================================" << endl;
}

void PerformUsersMenuOptions(vector<stUser>& vUsers)
{
    ShowManageUsersMenu();
    enUsersMenuChoices Choice = ReadUsersMenueChoice();

    while (Choice != eMainMenu)
    {
        switch (Choice)
        {
        case eListUsers:
        {
            cls();
            ShowUsersList(vUsers);
            break;
        }
        case eAddUser:
        {
            cls();
            AddNewUsers(vUsers);
            //vUsers = LoadUserDataFromFileToVector(UsersFile);
            break;
        }
        case eDeleteUser:
        {
            cls();
            DeleteUser(vUsers);
            break;
        }
        case eUpdateUser:
        {
            cls();
            UpdateUser(vUsers);
            break;
        }
        case eFindUser:
        {
            cls();
            FindUser(vUsers);
            break;
        }
        }
        cout << "\nPress Any Key To Go Back To Manage Users Menu...";
        system("pause>0");
        ShowManageUsersMenu();
        Choice = ReadUsersMenueChoice();
    }
}

void ShowLoginScreen()
{
    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "             LogIn Screen        " << endl;
    cout << "-----------------------------------------" << endl;
}

bool CheckUserInfo(stUser User)
{
    vector<stUser> vUsers = LoadUserDataFromFileToVector(UsersFile);
    for (stUser& U : vUsers)
    {
        if (U.Name == User.Name && U.Password == User.Password)
        {
            CurrentUser = U;
            return true;
        }
    }
    return false;
}

void ShowAccessDeniedScreen()
{
    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "Access Denied," << endl;
    cout << "You don't have permissions to do this," << endl;
    cout << "Please Contact Your Admin." << endl;
    cout << "-----------------------------------------" << endl;
}

void Login()
{
    bool LoginFaild = false;
    string Username, Password;
    do
    {
        ShowLoginScreen();
        if (LoginFaild)
        {
            cout << "Invalid Username/PassWord!\n";
        }
        Username = ReadUserName();
        Password = ReadPassword();

        stUser TempUser;
        TempUser.Name = Username;
        TempUser.Password = Password;

        LoginFaild = !CheckUserInfo(TempUser);

    } while (LoginFaild);
}

void StartProgramm()
{
    while (true)
    {
        Login();
        vector<stClient> vClients = LoadDataFromFileToVector(ClientsFile);
        vector<stUser> vUsers = LoadUserDataFromFileToVector(UsersFile);

        enChoices Choice;
        do
        {
            ShowMainMenue();
            Choice = ReadMainMenuChoice();

            if (!CheckAccess(Choice) && Choice != enLogOut)
            {
                ShowAccessDeniedScreen();
                cout << "\nPress Any Key To Go Back To The Main Menue...";
                system("pause>0");
                continue;
            }

            switch (Choice)
            {
            case enShowAllClients:
            {
                ShowAllCLients(vClients);
                cout << "\nPress Any Key To Go Back To The Main Menue...";
                system("pause>0");
                break;
            }
            case enAddClients:
            {
                AddNewClients(vClients);
                cout << "\nPress Any Key To Go Back To The Main Menue...";
                system("pause>0");
                break;
            }
            case enDeleteClient:
            {
                DeleteClient(vClients);
                cout << "\nPress Any Key To Go Back To The Main Menue...";
                system("pause>0");
                break;
            }
            case enUpdateClientInfo:
            {
                UpdateClientInfo(vClients);
                cout << "\nPress Any Key To Go Back To The Main Menue...";
                system("pause>0");
                break;
            }
            case enFindClient:
            {
                FindClient(vClients);
                cout << "\nPress Any Key To Go Back To The Main Menue...";
                system("pause>0");
                break;
            }
            case enTransactions:
            {
                PerformTransactionsOptions(vClients);
                break;
            }
            case enManageUsers:
            {
                PerformUsersMenuOptions(vUsers);
                break;
            }
            case enLogOut:
            {
                break;
            }
            }

        } while (Choice != enLogOut);
    }
}

int main()
{
    StartProgramm();
    return 0;
}