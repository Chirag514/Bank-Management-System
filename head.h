// defining the header file named b23mt1015_b23ci1007_b23mt1012_b23mt1023.h
#ifndef HEAD_H
#define HEAD_H

// including standard libraries
#include <stdio.h>
#include <string.h>

// defining structures
typedef struct {
    char name[50];
    char dob[11]; // Format: DD/MM/YYYY
    char aadhar[13]; // Aadhaar number
    int acc_no;
    char mobile[11];
    int age;
    char father_name[50];
    double balance;
} Account; 

typedef struct {
    int acc_no;
    double amount;
    char type[10]; // Deposit or Withdrawal
} Transaction; 

typedef struct {
    int acc_no;
    double loan_amount;
    char loan_type[20]; // Type of loan
} Loan;

// function prototypes
void createNewAccount();
void editAccount();
void viewAccountDetails();
void deleteAccount();
int handleLoan();
void handleBankStatement();
void handleReports();
void handleDepositWithdraw();
void showExchangeRates();
void displayDashboard();
void saveAccount(Account acc);
Account readAccount(int acc_no);
int accountExists(int acc_no);
void saveTransaction(Transaction trans);
void saveLoan(Loan loan);
void updateAccountDetails(Account acc);
void showCurrentLoans();
void repayLoan();
void loanAllotment();

// ending the header file
#endif // B23MT1015_B23CI1007_B23MT1012_B23MT1023_HEAD_H