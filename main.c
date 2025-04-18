// including the header file
#include "head.h"
#include "bank_reports.c"
#include "bank_operations.c"
#include "data_management.c"




// main function
int main() {
    // variable to take choice of user
    int choice;
    printf("\n\e[1;36m*****  Welcome to Banking System Simulation  *****\e[0m\n");
    // running continous while loop untill '10' is entered by user
    while (1) {
        printf("\n\e[0;36m*******  Menu  *******\e[0m\n");
        printf("1.  Create new account\n");
        printf("2.  Edit account\n");
        printf("3.  View account details\n");
        printf("4.  Delete account\n");
        printf("5.  Loan\n");
        printf("6.  Bank statement\n");
        printf("7.  Deposit/Withdraw money\n");
        printf("8.  Currency exchange (only showing exchange rates)\n");
        printf("9.  Dashboard\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // switch statement to call diff func based on user's choice
        switch (choice) {
            case 1:
                createNewAccount();
                break;
            case 2:
                editAccount();
                break;
            case 3:
                viewAccountDetails();
                break;
            case 4:
                deleteAccount();
                break;
            case 5:
                handleLoan();
                break;
            case 6:
                handleBankStatement();
                break;
            case 7:
                handleDepositWithdraw();
                break;
            case 8:
                showExchangeRates();
                break;
            case 9:
                displayDashboard();
                break;
            case 10:
                return 0;
            // error handling
            default:
                printf("\e[0;31mInvalid choice. Please try again.\e[0m\n");
        }
    }
}