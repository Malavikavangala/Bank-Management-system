#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Account {
    int accNumber;
    char name[50];
    char accType;
    double balance;

public:
    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accNumber;
        cout << "Enter Account Holder Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Enter Account Type (S/Saving C/Current): ";
        cin >> accType;
        accType = toupper(accType);
        cout << "Enter Initial Balance: ";
        cin >> balance;
        cout << "\nAccount Created Successfully!\n";
    }

    void showAccount() const {
        cout << "Account Number: " << accNumber << endl;
        cout << "Holder Name: " << name << endl;
        cout << "Type: " << accType << endl;
        cout << "Balance: $" << balance << endl;
    }

    void deposit(double amt) {
        balance += amt;
    }

    void withdraw(double amt) {
        if (balance >= amt)
            balance -= amt;
        else
            cout << "Insufficient balance!\n";
    }

    int getAccNumber() const {
        return accNumber;
    }

    double getBalance() const {
        return balance;
    }

    char getAccType() const {
        return accType;
    }

    void report() const {
        cout << setw(10) << accNumber << setw(20) << name << setw(10) << accType << setw(12) << balance << endl;
    }
};

// File Handling Functions
void writeAccount() {
    Account ac;
    ofstream outFile("accounts.dat", ios::binary | ios::app);
    ac.createAccount();
    outFile.write(reinterpret_cast<char*>(&ac), sizeof(Account));
    outFile.close();
}

void displayAccount(int num) {
    Account ac;
    ifstream inFile("accounts.dat", ios::binary);
    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(Account))) {
        if (ac.getAccNumber() == num) {
            ac.showAccount();
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found)
        cout << "Account not found.\n";
}

void depositWithdraw(int num, int option) {
    Account ac;
    fstream file("accounts.dat", ios::binary | ios::in | ios::out);
    bool found = false;
    while (!file.eof() && file.read(reinterpret_cast<char*>(&ac), sizeof(Account))) {
        if (ac.getAccNumber() == num) {
            ac.showAccount();
            double amount;
            cout << "\nEnter amount: ";
            cin >> amount;
            if (option == 1)
                ac.deposit(amount);
            else
                ac.withdraw(amount);

            int pos = -1 * static_cast<int>(sizeof(Account));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&ac), sizeof(Account));
            cout << "Transaction successful.\n";
            found = true;
            break;
        }
    }
    file.close();
    if (!found)
        cout << "Account not found.\n";
}

void displayAll() {
    Account ac;
    ifstream inFile("accounts.dat", ios::binary);
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << setw(10) << "Acc No." << setw(20) << "Name" << setw(10) << "Type" << setw(12) << "Balance" << endl;
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(Account))) {
        ac.report();
    }
    inFile.close();
}

void menu() {
    int choice;
    do {
        cout << "\n\nBank Management System Menu\n";
        cout << "1. Create Account\n";
        cout << "2. View Account\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. View All Accounts\n";
        cout << "6. Exit\n";
        cout << "Select an option: ";
        cin >> choice;

        int num;
        switch (choice) {
            case 1:
                writeAccount();
                break;
            case 2:
                cout << "Enter Account Number: ";
                cin >> num;
                displayAccount(num);
                break;
            case 3:
                cout << "Enter Account Number: ";
                cin >> num;
                depositWithdraw(num, 1);
                break;
            case 4:
                cout << "Enter Account Number: ";
                cin >> num;
                depositWithdraw(num, 2);
                break;
            case 5:
                displayAll();
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }
    } while (choice != 6);
}

// Main Function
int main() {
    menu();
    return 0;
}

