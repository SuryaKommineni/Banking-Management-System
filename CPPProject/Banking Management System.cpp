#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

class BMS;
int i = 0;

void deposit(BMS &obj);
void requestLoan(BMS &obj);
void updateAccount(BMS &obj);
void transferMoney(BMS obj[]);
int check(BMS obj[], int sno, long long int temp);
void withdraw(BMS &obj);
void display(BMS &obj);
void addaccount(BMS &obj);
void deleteAccount(BMS obj[], int &numAccounts);
int default_check(BMS obj[]);
void repay_loan(BMS &obj);

class BMS {
private:
    long long int accno;

public:
    string name;
    long long int mbno;
    char type;
    long int amount;
    long int loanAmount;

    BMS()
    {
        name = " ";
        mbno = 0;
        type = '\0';
        amount = 0;
        loanAmount = 0;
    }

    void enteraccno()
    {
        cin >> accno;
    }

    bool check_acc(long long int x)
    {
        return x == accno;
    }

    void setLoanAmount(long int loanAmt)
    {
        loanAmount = loanAmt;
    }

    long int getLoanAmount() const
    {
        return loanAmount;
    }
};

int default_check(BMS obj[])
{
    int sno, k;
    long long int mob;
    cout << "Enter your serial Number: ";
    cin >> sno;
    cout << "Enter Your mobile Number for verification: ";
    cin >> mob;
    k = check(obj, sno, mob);
    return k;
}

void addaccount(BMS &obj)
{
    int i = 0;
    cout << "Enter your Account Number: ";
    obj.enteraccno();
    cout << "Enter Your Name: ";
    getchar();
    getline(cin, obj.name);
    cout << "Enter Your Mobile Number: ";
    cin >> obj.mbno;
    cout << "Enter the Type of account you want to create (S/C): ";
    while (i < 3)
    {
        cin >> obj.type;
        if (obj.type == 'S' || obj.type == 's' || obj.type == 'C' || obj.type == 'c')
        {
            break;
        }
        else
        {
            cout << "Please Enter a valid expression " << endl;
            cout << "You have " << 2 - i << " attempts left : ";
            i++;
        }
    }
    if (i == 3)
    {
        exit(0);
    }
    deposit(obj);
}

void display(BMS &obj)
{
    cout << "NAME: " << obj.name << endl;
    cout << "ACCOUNT BALANCE: " << obj.amount << endl;
    cout << "LOAN AMOUNT: " << obj.getLoanAmount() << endl;
    cout << "ACCOUNT TYPE: " << (obj.type == 's' || obj.type == 'S' ? "SAVINGS" : "CURRENT") << endl;
}

void deposit(BMS &obj)
{
    cout << "Enter the Amount You want to Deposit,";
    int amount = 0;
    if (obj.type == 's' || obj.type == 'S')
    {
        do
        {
            cout << " Your Deposit amount should be at least(1000): ";
            cin >> amount;
        } while (amount < 1000);
        obj.amount += amount;
        cout << "Deposited Successfully in Your Account." << endl;
    }
    else
    {
        do
        {
            cout << " Your Deposit amount should be at least(5000): ";
            cin >> amount;
        } while (amount < 5000);
        obj.amount += amount;
        cout << "Deposited Successfully in Your Account." << endl;
    }
}

void requestLoan(BMS &obj)
{
    char ans;
    cout << "Do you want to apply for a loan? (Y/N): ";
    cin >> ans;
    if (ans == 'Y' || ans == 'y')
    {
        cout << "Enter the loan amount you want: ";
        cin >> obj.loanAmount;
        double interestRate = 0.05;
        double interestAmount = obj.loanAmount * interestRate;
        cout << "Loan Requested Successfully." << endl;
        cout << "Interest Amount: " << interestAmount << endl;
        obj.loanAmount += static_cast<long>(round(interestAmount));
    }
    else
    {
        obj.setLoanAmount(0);
        cout << "Loan request declined." << endl;
    }
}

void repay_loan(BMS &obj)
{
    if (obj.loanAmount == 0)
    {
        cout << "YOU HAVE NO LOAN CURRENTLY ON YOUR ACCOUNT.\n";
        return;
    }
    else
    {
        long repay;
        cout << "YOUR LOAN AMOUNT IS: " << obj.loanAmount << endl;
        cout << "ENTER AMOUNT YOU WANT TO REPAY: (EXCESS AMOUNT WILL BE ADDED TO YOUR ACCOUNT IF REPAID AMOUNT IS GREATER THAN LOAN AMOUNT)";
        cin >> repay;
        if (repay > obj.loanAmount)
        {
            repay = repay - obj.loanAmount;
            obj.loanAmount = 0;
            obj.amount += repay;
            cout << "Excess amount added to your account successfully" << endl;
        }
        else
        {
            obj.loanAmount -= repay;
            cout << "Amount of " << repay << " rupees is repaid into your loan amount\n";
        }
    }
}

void updateAccount(BMS &obj)
{
    cout << "Enter updated name: ";
    getchar();
    getline(cin, obj.name);
    cout << "Enter updated mobile number: ";
    cin >> obj.mbno;
    cout << "Account details updated successfully.\n";
}

void transferMoney(BMS obj[])
{
    long long int senderAcc, receiverAcc;
    int senderIndex, receiverIndex;
    long int transferAmount;
    cout << "Enter your account number (sender): ";
    cin >> senderAcc;
    for (int j = 0; j < i; ++j)
    {
        if (obj[j].check_acc(senderAcc))
        {
            senderIndex = j;
            break;
        }
    }
    if (!obj[senderIndex].check_acc(senderAcc))
    {
        cout << "Sender account not found.\n";
        return;
    }
    cout << "Enter receiver's account number: ";
    cin >> receiverAcc;
    for (int j = 0; j < i; ++j)
    {
        if (obj[j].check_acc(receiverAcc))
        {
            receiverIndex = j;
            break;
        }
    }
    if (!obj[receiverIndex].check_acc(receiverAcc))
    {
        cout << "Receiver account not found.\n";
        return;
    }
    cout << "Enter the amount to transfer: ";
    cin >> transferAmount;
    if (transferAmount > obj[senderIndex].amount)
    {
        cout << "Insufficient funds to transfer.\n";
    }
    else
    {
        obj[senderIndex].amount -= transferAmount;
        obj[receiverIndex].amount += transferAmount;
        cout << "Transfer successful.\n";
    }
}

void withdraw(BMS &obj)
{
    int amount = 0;
    cout << "Enter the amount you want to withdraw from your account: ";
    cin >> amount;
    if (amount > obj.amount)
    {
        cout << "Insufficient funds. Please enter a valid amount.\n";
    }
    else
    {
        obj.amount -= amount;
    }
}

int check(BMS obj[], int sno, long long int temp)
{
    sno = sno / 50;
    if (sno >= i || sno < 0)
    {
        cout << "Invalid Serial Number" << endl;
        return -1;
    }
    if (obj[sno].mbno == temp)
    {
        return sno;
    }
    else
    {
        cout << "Invalid Mobile Number\n";
        return -1;
    }
}

void deleteAccount(BMS obj[], int &numAccounts)
{
    int serialNumber;
    cout << "Enter the Serial Number of the account you want to delete: ";
    cin >> serialNumber;

    if (serialNumber < 0 || serialNumber >= numAccounts || obj[serialNumber].name == " ")
    {
        cout << "Invalid Serial Number. Please enter a valid Serial Number.\n";
        return;
    }

    for (int j = serialNumber; j < numAccounts - 1; ++j)
    {
        obj[j] = obj[j + 1];
    }

    obj[numAccounts - 1] = BMS();

    numAccounts--;

    cout << "Account deleted successfully.\n";
}

int main()
{
    BMS obj[100];
    int ch;
    int k = 1;
    int numAccounts = 0;

    while (k)
    {
        cout << "*********************************************************WELCOME TO SRM BANK********************************************\n";
        cout << "PRESS 1 TO CREATE ACCOUNT\n";
        cout << "PRESS 2 TO DISPLAY YOUR ACCOUNT DETAILS\n";
        cout << "PRESS 3 TO REQUEST A LOAN\n";
        cout << "PRESS 4 TO REPAY YOUR LOAN\n";
        cout << "PRESS 5 TO UPDATE ACCOUNT DETAILS\n";
        cout << "PRESS 6 TO TRANSFER MONEY\n";
        cout << "PRESS 7 TO DEPOSIT MONEY\n";
        cout << "PRESS 8 TO WITHDRAW MONEY FROM ACCOUNT\n";
        cout << "PRESS 9 TO CHECK ACCOUNT BALANCE AND DUES\n";
        cout << "PRESS 10 TO DELETE AN ACCOUNT\n";
        cout << "PRESS 11 TO EXIT\n";
        cout << "***************************************************************************************************************************\n";
        cout << "Enter Your Choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            addaccount(obj[i]);
            cout << "Please Remember Your Serial Number is: " << i * 50 << endl
                 << "This Number is Required for any other Queries regarding Your account. " << endl;
            i++;
            numAccounts++;
            break;
        case 2:
            int r;
            r = default_check(obj);
            if (r >= 0)
                display(obj[r]);
            else
                cout << "Try Again entering Valid Input" << endl;
            break;
        case 3:
            r = default_check(obj);
            if (r >= 0)
                requestLoan(obj[r]);
            else
                cout << "Try Again entering Valid Input" << endl;
            break;
        case 4:
            r = default_check(obj);
            if (r != -1)
                repay_loan(obj[r]);
            else
                cout << "Account does not exist or you have not entered the valid serial number or mobile number\n";
            break;
        case 5:
            r = default_check(obj);
            if (r >= 0)
                updateAccount(obj[r]);
            else
                cout << "Try Again entering Valid Input" << endl;
            break;
        case 6:
            transferMoney(obj);
            break;
        case 7:
            r = default_check(obj);
            if (r >= 0)
            {
                deposit(obj[r]);
            }
            break;
        case 8:
            r = default_check(obj);
            if (r >= 0)
                withdraw(obj[r]);
            break;
        case 9:
            r = default_check(obj);
            if (r >= 0)
            {
                cout << "----------------------------------------------------------------------------------\n";
                cout << "|	Account Balance: " << obj[r].amount << "                                        \n";
                cout << "|	Loan Amount: " << obj[r].loanAmount << "                                        \n";
                cout << "----------------------------------------------------------------------------------\n";
            }
            break;
        case 10:
            deleteAccount(obj, numAccounts);
            break;
        case 11:
            cout << "Thank You For Visiting Our Bank";
            k = 0;
            break;
        default:
            cout << "Invalid Choice. Please enter a valid choice." << endl;
        }
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        system("cls");
    }
    return 0;
}

