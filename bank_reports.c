// including header file
#include "head.h"

// function to handle statements
void handleBankStatement(){
    int acc_no;
    Transaction trans;
    FILE *fp;
    int found = 0;

    printf("\nEnter account number for bank statement: ");
    scanf("%d", &acc_no);

    fp = fopen("transactions.txt", "r");
    // error handling for file not opened
    if (fp == NULL) {
        printf("\e[0;31mError opening file.\e[0m\n");
        return;
    }

    printf("\n\e[0;36mBank statement for account number %d:\e[0m\n", acc_no);
    while (fread(&trans, sizeof(Transaction), 1, fp)) {
        if (trans.acc_no == acc_no) {
            printf("Transaction type: %s, Amount: %.2f\n", trans.type, trans.amount);
            found = 1;
        }
    }

    fclose(fp); // close the file
    // if no acoount found
    if (!found) {
        printf("\e[0;34mNo transactions found.\e[0m\n");
    }
}

// function to handle reports
void handleReports() {
    // Add code here to handle different reports like total balance in the bank, number of customers, etc.
    printf("\n\e[0;36mBank Reports:\e[0m\n");

    FILE *accounts_fp = fopen("accounts.txt", "r");
    // error handling for file not opened
    if (accounts_fp == NULL) {
        printf("\e[0;31mNo accounts data exists.\e[0m\n");
        fclose(accounts_fp);
        return;
    }

    FILE *loans_fp = fopen("loans.txt", "r");
    // error handling for file not opened
    if (loans_fp == NULL) {
        printf("\e[0;31mNo Loans exists\e[0m\n");
        //return;
    }

    Account acc;
    Loan loan;
    double total_balance = 0;
    int num_customers = 0;
    double total_loans = 0;

    // Calculate total balance and number of customers
    while (fread(&acc, sizeof(Account), 1, accounts_fp)) {
        total_balance += acc.balance;
        num_customers++;
    }

    // Calculate total loans
    while (fread(&loan, sizeof(Loan), 1, loans_fp)) {
        total_loans += loan.loan_amount;
    }

    // Close the files
    fclose(accounts_fp);
    fclose(loans_fp);

    // Display reports
    printf("Total balance in the bank: %.2f\n", total_balance);
    printf("Number of customers: %d\n", num_customers);
    printf("Total loans given: %.2f\n", total_loans);
}