#include<bits/stdc++.h>

using namespace std;

class Account {
protected:
    string accountNumber;
    string accountHolder;
    double balance;

public:
    Account(const string& accNum, const string& holder, double bal = 0.0)
        :accountNumber(accNum), accountHolder(holder),balance(bal) {}

    virtual void deposit(double amount) {
        balance+= amount;
        cout <<"Deposited: $" << amount << endl;
    }

    virtual bool withdraw(double amount) {
        if(amount > balance) {
            cout<<"Insufficient funds!" <<endl;
            return false;
        }
        balance-=amount;
        cout<<"Withdrawn: $"<<amount<<endl;
        return true;
    }

    double getBalance() const {
        return balance;
    }

    virtual void displayAccountInfo() const {
        cout<<"Account Number: "<< accountNumber<<endl;
        cout<<"Account Holder: "<< accountHolder<<endl;
        cout<<"Balance: $"<<balance<<endl;
    }
};

class SavingsAccount:public Account {
private:
    double interestRate;

public:
    SavingsAccount(const string& accNum, const string& holder, double bal = 0.0, double rate = 0.02)
        : Account(accNum, holder, bal), interestRate(rate) {}

    void applyInterest() {
        balance+=balance* interestRate;
        cout << "Interest applied. New balance: $" << balance <<endl;
    }

    void displayAccountInfo() const override {
        Account::displayAccountInfo();
       cout << "Interest Rate: " << interestRate * 100 << "%" <<endl;
    }
};

class CheckingAccount:public Account {
private:
    double overdraftLimit;

public:
    CheckingAccount(const string& accNum, const string& holder, double bal = 0.0, double limit = 500.0)
        :Account(accNum, holder, bal), overdraftLimit(limit) {}

    bool withdraw(double amount) override {
        if(amount > balance + overdraftLimit) {
           cout<<"Overdraft limit exceeded!"<<endl;
            return false;
        }
        balance-=amount;
       cout<<"Withdrawn: $"<<amount<<endl;
        return true;
    }

    void displayAccountInfo() const override {
        Account::displayAccountInfo();
        cout << "Overdraft Limit: $" << overdraftLimit <<endl;
    }
};

class Bank {
private:
    unordered_map<string, Account*> accounts;

public:
    ~Bank() {
        for (auto& pair : accounts) {
            delete pair.second;
        }
    }

    void openSavingsAccount(const string& accNum, const string& holder, double bal = 0.0, double rate = 0.02) {
        accounts[accNum] = new SavingsAccount(accNum, holder, bal, rate);
        cout << "Savings Account opened successfully!" << endl;
    }

    void openCheckingAccount(const string& accNum, const string& holder, double bal = 0.0, double limit = 500.0) {
        accounts[accNum] = new CheckingAccount(accNum, holder, bal, limit);
       cout << "Checking Account opened successfully!" << endl;
    }

    void deposit(const string& accNum, double amount) {
        if (accounts.find(accNum) != accounts.end()) {
            accounts[accNum]->deposit(amount);
        } else {
           cout << "Account not found!" <<endl;
        }
    }

    void withdraw(const string& accNum, double amount) {
        if (accounts.find(accNum) != accounts.end()) {
            accounts[accNum]->withdraw(amount);
        } else {
            cout << "Account not found!" <<endl;
        }
    }

    void checkBalance(const string& accNum) const {
        if (accounts.find(accNum) != accounts.end()) {
            cout << "Balance: $" << accounts.at(accNum)->getBalance() <<endl;
        } else {
           cout << "Account not found!" <<endl;
        }
    }

    void displayAccountInfo(const string& accNum) const {
        if (accounts.find(accNum) != accounts.end()) {
            accounts.at(accNum)->displayAccountInfo();
        } else {
            cout << "Account not found!" <<endl;
        }
    }
};

int main() {
    Bank bank;

    bank.openSavingsAccount("USE345", "Alice Joe", 600.0);
    bank.openCheckingAccount("LOP890", "Bob Dane", 800.0);

    bank.deposit("USE345", 200.0);
    bank.withdraw("LOP890", 100.0);

    bank.checkBalance("USE345");
    bank.displayAccountInfo("LOP890");

    return 0;
}
