#include <iostream>
#https://www.onlinegdb.com/#editor_1include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

class BankAccount
{
private:
    int accNo;
    char name[50];
    float balance;

public:
    void createAccount()
    {
        cout << "\nEnter Account Number : ";
        cin >> accNo;

        cin.ignore();

        cout << "Enter Customer Name : ";
        cin.getline(name, 50);

        cout << "Enter Initial Balance : ";
        cin >> balance;
    }

    void showAccount() const
    {
        cout << "\nAccount Number : " << accNo;
        cout << "\nCustomer Name  : " << name;
        cout << "\nBalance        : " << balance << endl;
    }

    int getAccNo() const
    {
        return accNo;
    }

    float getBalance() const
    {
        return balance;
    }

    void deposit(float amt)
    {
        balance += amt;
    }

    bool withdraw(float amt)
    {
        if (amt <= balance)
        {
            balance -= amt;
            return true;
        }
        return false;
    }
};

// Create Account
void createNewAccount()
{
    BankAccount acc;

    ofstream outFile("bank.dat", ios::binary | ios::app);

    acc.createAccount();

    outFile.write((char *)&acc, sizeof(acc));

    outFile.close();

    cout << "\nAccount Created Successfully!\n";
}

// Display All Accounts
void displayAllAccounts()
{
    BankAccount acc;

    ifstream inFile("bank.dat", ios::binary);

    if (!inFile)
    {
        cout << "\nNo Records Found!\n";
        return;
    }

    cout << "\n========== ACCOUNT LIST ==========\n";

    while (inFile.read((char *)&acc, sizeof(acc)))
    {
        acc.showAccount();
        cout << "\n----------------------------\n";
    }

    inFile.close();
}

// Search Account
void searchAccount()
{
    int accNo;
    bool found = false;

    cout << "\nEnter Account Number : ";
    cin >> accNo;

    BankAccount acc;

    ifstream inFile("bank.dat", ios::binary);

    while (inFile.read((char *)&acc, sizeof(acc)))
    {
        if (acc.getAccNo() == accNo)
        {
            cout << "\nAccount Found!\n";
            acc.showAccount();
            found = true;
            break;
        }
    }

    inFile.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

// Deposit
void depositMoney()
{
    int accNo;
    float amount;

    cout << "\nEnter Account Number : ";
    cin >> accNo;

    cout << "Enter Amount to Deposit : ";
    cin >> amount;

    BankAccount acc;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    bool found = false;

    while (file.read((char *)&acc, sizeof(acc)))
    {
        if (acc.getAccNo() == accNo)
        {
            acc.deposit(amount);

            file.seekp(-sizeof(acc), ios::cur);

            file.write((char *)&acc, sizeof(acc));

            cout << "\nAmount Deposited Successfully!\n";

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

// Withdraw
void withdrawMoney()
{
    int accNo;
    float amount;

    cout << "\nEnter Account Number : ";
    cin >> accNo;

    cout << "Enter Amount to Withdraw : ";
    cin >> amount;

    BankAccount acc;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    bool found = false;

    while (file.read((char *)&acc, sizeof(acc)))
    {
        if (acc.getAccNo() == accNo)
        {
            if (acc.withdraw(amount))
            {
                file.seekp(-sizeof(acc), ios::cur);

                file.write((char *)&acc, sizeof(acc));

                cout << "\nWithdrawal Successful!\n";
            }
            else
            {
                cout << "\nInsufficient Balance!\n";
            }

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

// Delete Account
void deleteAccount()
{
    int accNo;

    cout << "\nEnter Account Number : ";
    cin >> accNo;

    BankAccount acc;

    ifstream inFile("bank.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);

    bool found = false;

    while (inFile.read((char *)&acc, sizeof(acc)))
    {
        if (acc.getAccNo() != accNo)
        {
            outFile.write((char *)&acc, sizeof(acc));
        }
        else
        {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    remove("bank.dat");
    rename("temp.dat", "bank.dat");

    if (found)
        cout << "\nAccount Deleted Successfully!\n";
    else
        cout << "\nAccount Not Found!\n";
}

int main()
{
    int choice;

    do
    {
        cout << "\n\n========== BANK MANAGEMENT SYSTEM ==========\n";
        cout << "1. Create Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Search Account\n";
        cout << "4. Deposit Money\n";
        cout << "5. Withdraw Money\n";
        cout << "6. Delete Account\n";
        cout << "7. Exit\n";

        cout << "\nEnter Your Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createNewAccount();
            break;

        case 2:
            displayAllAccounts();
            break;

        case 3:
            searchAccount();
            break;

        case 4:
            depositMoney();
            break;

        case 5:
            withdrawMoney();
            break;

        case 6:
            deleteAccount();
            break;

        case 7:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 7);

    return 0;
}
