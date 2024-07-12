#include<bits/stdc++.h>
using namespace std;



double addnums(double n, double m);
double subtractnums(double n, double m);
double multiplynums(double n, double m);
double dividenums(double n, double m);

int main() {
    double num1, num2;
    char operation;
    bool keepRunning = true;

    while (keepRunning) {
        cout<<"Enter first number: ";
        cin>>num1;
        cout<<"Enter an operator (+, -, *, /): ";
        cin>>operation;
        cout<<"Enter second number: ";
        cin>>num2;

        switch(operation) {
            case '+':
                cout<<"Result: "<<addnums(num1, num2)<<endl;
                break;
            case '-':
                cout<<"Result: "<<subtractnums(num1, num2)<<endl;
                break;
            case '*':
                cout<<"Result: "<<multiplynums(num1, num2)<<endl;
                break;
            case '/':
                if(num2 != 0) {
                    cout<<"Result: "<<dividenums(num1, num2)<<endl;
                } else {
                    cout<<"Error: Division by zero is not allowed."<<endl;
                }
                break;
            default:
                cout<<"Error: Invalid operator."<<endl;
                break;
        }

        char choice;
        cout<<"Do you want to perform another calculation? (y/n): ";
        cin>>choice;
        if(choice != 'y' && choice != 'Y'){
            keepRunning = false;
        }
    }

    cout<<"Calculator exiting..."<<endl;
    return 0;
}

// Function definitions
double addnums(double n, double m) {
    return n+m;
}

double subtractnums(double n, double m) {
    return n-m;
}

double multiplynums(double n, double m) {
    return n*m;
}

double dividenums(double n, double m) {
    return n/m;
}
