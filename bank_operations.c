#include <string.h> // including required standard libraries
#include "head.h" // including header file

// Function to consume any leftover characters in the input buffer
void consumeLeftOver() {                                                         
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}// this function will consume leftover characters when used

// function to create new account
void createNewAccount() {
    Account acc;
    char leftOver;
    

    // taking all the deatils of account from user
    printf("\nEnter account details:\n");
    printf("Name: ");
    consumeLeftOver(); // Consume leftover characters
    fgets(acc.name, sizeof(acc.name), stdin);
    // Remove newline character from the end of the string
    // strscpn funtion used to find '\n' char
    // then replacing it with '\0' char
    acc.name[strcspn(acc.name, "\n")] = '\0';                                  

    printf("DOB (DD/MM/YYYY): ");
    scanf("%s", acc.dob);

    printf("Aadhar number: ");
    scanf("%s", acc.aadhar);

    // input with data validation
    while(1) {
        printf("Account number: ");
        if (scanf("%d", &acc.acc_no) != 1) {
            printf("\e[0;31mInvalid input. Please enter an integer.\e[0m\n");
            // Clear the input buffer (optional)
            scanf("%*[^\n]"); // Discard any remaining characters in the input buffer                 // 3PROBLEM
            // return 1;
        } else break;
    }

    // Check if account already exists
    if (accountExists(acc.acc_no)) {
        printf("\e[0;31mAccount number already exists.\e[0m\n");
        return;
    }

    printf("Mobile number: ");
    scanf("%s", acc.mobile);

    // input with data validation
    while(1) {
        printf("Age: ");
        if (scanf("%d", &acc.age) != 1) {
            printf("\e[0;31mInvalid input. Please enter an integer.\e[0m\n");
            // Clear the input buffer (optional)
            scanf("%*[^\n]"); // Discard any remaining characters in the input buffer
            // return ;
        } else break;
    }

    printf("Father's name: ");
    // same as done in Name array
    consumeLeftOver(); // Consume leftover characters
    fgets(acc.father_name, sizeof(acc.father_name), stdin);
    // Remove newline character from the end of the string
    acc.father_name[strcspn(acc.father_name, "\n")] = '\0';

    // input with data validation
    while(1) {
        printf("Initial balance: ");
        if (scanf("%lf", &acc.balance) != 1) {
            printf("\e[0;31mInvalid input. Please enter an integer or decimal value.\e[0m\n");
            // Clear the input buffer (optional)
            scanf("%*[^\n]"); // Discard any remaining characters in the input buffer
            // return 1;
        } else break;
    }

    // Save account details
    saveAccount(acc);
    printf("\e[0;32mAccount created successfully!\e[0m\n");
}

// function to edit account deatils
void editAccount() {
    int acc_no;
    Account acc;
    FILE *fp;
    FILE *temp_fp;
    int found = 0;

    // input with data validation
    while(1) {
        printf("Enter account number to edit: ");
        if (scanf("%d", &acc_no) != 1) {
            printf("\e[0;31mInvalid input. Please enter an integer.\e[0m\n");
            // Clear the input buffer (optional)
            scanf("%*[^\n]"); // Discard any remaining characters in the input buffer
            // return 1;
        } else break;
    }

    // Open accounts file and temp file
    fp = fopen("accounts.txt", "r");
    temp_fp = fopen("temp.txt", "w");
    // error handling for file not opened
    if (fp == NULL || temp_fp == NULL) {
        printf("\e[0;31mError opening file.\e[0m\n");
        return;
    }

    // Read accounts file and write to temp file
    while (fread(&acc, sizeof(Account), 1, fp)) {
        if (acc.acc_no == acc_no) {
            found = 1;
            printf("\nEditing account %d\n", acc.acc_no);
            printf("Enter new details:\n");
            
            printf("New Name:"); 
            
            consumeLeftOver(); // Consume leftover characters
            fgets(acc.name, sizeof(acc.name), stdin);
            // Remove newline character from the end of the string
            acc.name[strcspn(acc.name, "\n")] = '\0';

            printf("DOB (DD/MM/YYYY): ");
            scanf("%s", acc.dob);

            printf("Aadhar number: ");
            scanf("%s", acc.aadhar);

            printf("Mobile number: ");
            scanf("%s", acc.mobile);
            
            // input with data validation
            while(1) {
                printf("Age: ");
                if (scanf("%d", &acc.age) != 1) {
                    printf("\e[0;31mInvalid input. Please enter an integer.\e[0m\n");
                    // Clear the input buffer (optional)
                    scanf("%*[^\n]"); // Discard any remaining characters in the input buffer
                    // return 1;
                } else break;
            }

            printf("Father's name: ");

            consumeLeftOver(); // Consume leftover characters
            fgets(acc.father_name, sizeof(acc.father_name), stdin);
            // Remove newline character from the end of the string
            acc.father_name[strcspn(acc.father_name, "\n")] = '\0';

        }

        fwrite(&acc, sizeof(Account), 1, temp_fp);
    }

    fclose(fp);
    fclose(temp_fp);

    // Replace old file with new one to edit details
    if (found) {
        remove("accounts.txt");                                                            
        rename("temp.txt", "accounts.txt");
        printf("\e[0;32mAccount edited successfully!\e[0m\n");
    } else {
        printf("\e[0;31mAccount not found.\e[0m\n");
        remove("temp.txt");
    }
}

// function to delete account details
void deleteAccount() {
    int acc_no;
    Account acc;
    Transaction trans;
    Loan loan;
    FILE *accounts_fp, *temp_accounts_fp, *transactions_fp, *temp_transactions_fp, *loans_fp, *temp_loans_fp;
    int account_found = 0;

    // Prompt the user for the account number to delete
    // input with data validation
    while(1) {
        printf("\nEnter account number to delete: ");
        if (scanf("%d", &acc_no) != 1) {
            printf("\e[0;31mInvalid input. Please enter an integer.\e[0m\n");
            // Clear the input buffer (optional)
            scanf("%*[^\n]"); // Discard any remaining characters in the input buffer
            // return 1;
        } else break;
    }

    // Opening the  files
    accounts_fp = fopen("accounts.txt", "r");
    temp_accounts_fp = fopen("temp_accounts.txt", "w");
    transactions_fp = fopen("transactions.txt", "r");
    temp_transactions_fp = fopen("temp_transactions.txt", "w");
    loans_fp = fopen("loans.txt", "r");
    temp_loans_fp = fopen("temp_loans.txt", "w");

    // error handling for file not opened
    if (!accounts_fp || !temp_accounts_fp || !transactions_fp || !temp_transactions_fp || !loans_fp || !temp_loans_fp) {
        printf("\e[0;31mError opening files.\e[0m\n");
        return;
    }

    // Process the accounts file
    while (fread(&acc, sizeof(Account), 1, accounts_fp)) {
        if (acc.acc_no == acc_no) {
            // Account found, skip writing it to the temp file
            account_found = 1;
            printf("\e[0;32mAccount number %d deleted.\e[0m\n", acc_no);
        } else {
            // Write other accounts to the temporary file
            fwrite(&acc, sizeof(Account), 1, temp_accounts_fp);
        }
    }

    // Process the transactions file
    while (fread(&trans, sizeof(Transaction), 1, transactions_fp)) {
        if (trans.acc_no != acc_no) {
            // Write transactions that are not associated with the account to the temporary file
            fwrite(&trans, sizeof(Transaction), 1, temp_transactions_fp);
        }
    }

    // Process the loans file
    while (fread(&loan, sizeof(Loan), 1, loans_fp)) {
        if (loan.acc_no != acc_no) {
            // Write loans that are not associated with the account to the temporary file
            fwrite(&loan, sizeof(Loan), 1, temp_loans_fp);
        }
    }

    // Close the files
    fclose(accounts_fp);
    fclose(temp_accounts_fp);
    fclose(transactions_fp);
    fclose(temp_transactions_fp);
    fclose(loans_fp);
    fclose(temp_loans_fp);

    // Replace old files with new files 
    if (account_found) {
        remove("accounts.txt");
        rename("temp_accounts.txt", "accounts.txt");

        remove("transactions.txt");
        rename("temp_transactions.txt", "transactions.txt");

        remove("loans.txt");
        rename("temp_loans.txt", "loans.txt");
        
        printf("\e[0;32mAll associated transactions and loans deleted.\e[0m\n");
    } else {
        printf("\e[0;31mAccount number %d not found.\e[0m\n", acc_no);
        // Remove the temporary files
        remove("temp_accounts.txt");
        remove("temp_transactions.txt");
        remove("temp_loans.txt");
    }
}

// function to show current loans
void showCurrentLoans() {
    FILE *fp = fopen("loans.txt", "r");
    // error handling for file not opened
    if (fp == NULL) {
        printf("\e[0;31mError opening loans file.\e[0m\n");
        return;
    }

    Loan loan;
    printf("\nCurrent loans:\n");
    while (fread(&loan, sizeof(Loan), 1, fp)) {
        printf("Account number: %d, Loan amount: %.2f\n", loan.acc_no, loan.loan_amount);
    }

    fclose(fp); // close the file
}

// function to repay loan
void repayLoan() {
    int acc_no;
    double repay_amount;
    Account acc;
    Loan loan;
    FILE *loans_fp, *temp_loans_fp, *accounts_fp, *temp_accounts_fp;
    int loan_found = 0;

    // Prompt the user for account number and repayment amount
    // input with data validation
    while(1) {
        printf("\nEnter account number: ");
        if (scanf("%d", &acc_no) != 1) {
            printf("\e[0;31mInvalid input. Please enter an integer.\e[0m\n");
            // Clear the input buffer (optional)
            scanf("%*[^\n]"); // Discard any remaining characters in the input buffer
            // return 1;
        } else break;
    }

    while(1) {
        printf("Enter repayment amount: ");
        if (scanf("%lf", &repay_amount) != 1) {
            printf("\e[0;31mInvalid input. Please enter an integer or decimal value.\e[0m\n");
            // Clear the input buffer (optional)
            scanf("%*[^\n]"); // Discard any remaining characters in the input buffer
            // return 1;
        } else break;
    }

    // Open the loan file and create a temporary file for loans
    loans_fp = fopen("loans.txt", "r");
    temp_loans_fp = fopen("temp_loans.txt", "w");

    // Open the accounts file and create a temporary file for accounts
    accounts_fp = fopen("accounts.txt", "r");
    temp_accounts_fp = fopen("temp_accounts.txt", "w");

    // error handling for file not opened
    if (!loans_fp || !temp_loans_fp || !accounts_fp || !temp_accounts_fp) {
        printf("\e[0;31mError opening files.\e[0m\n");
        return;
    }

    // Initialize variables to track the repayment process
    int loan_fully_repaid = 0;
    double total_repaid = 0;

    // Process the loans file
    while (fread(&loan, sizeof(Loan), 1, loans_fp)) {
        if (loan.acc_no == acc_no) {
            loan_found = 1;

            // Calculate repayment
            if (repay_amount >= loan.loan_amount) {
                // Full repayment of the loan
                total_repaid += loan.loan_amount;                           
                // Mark the loan as fully repaid
                loan_fully_repaid = 1;
                printf("Loan of amount %.2lf repaid for account %d.\n", loan.loan_amount, acc_no);
            } else {
                // Partial repayment
                total_repaid += repay_amount;
                loan.loan_amount -= repay_amount;
                repay_amount = 0;
                // Write the updated loan back to the temporary file
                fwrite(&loan, sizeof(Loan), 1, temp_loans_fp);
            }
        } else {
            // Write other loans to the temporary file
            fwrite(&loan, sizeof(Loan), 1, temp_loans_fp);
        }
    }

    // Close the loans files
    fclose(loans_fp);
    fclose(temp_loans_fp);

    // Replace the old loans file with the new file if a loan was found
    if (loan_found) {
        remove("loans.txt");
        rename("temp_loans.txt", "loans.txt");
    } else {
        printf("\e[0;31mLoan not found for the account.\e[0m\n");
        remove("temp_loans.txt"); // romove temp_loans file
    }

    // Read the account information from the original account file and write it to the temporary file
    while (fread(&acc, sizeof(Account), 1, accounts_fp)) {
        if (acc.acc_no == acc_no) {
            // Subtract the total repaid amount from the account balance
            acc.balance -= total_repaid;

            // Write the updated account information back to the temp account file
            fwrite(&acc, sizeof(Account), 1, temp_accounts_fp);
        } else {
            // Write other accounts to the temporary file
            fwrite(&acc, sizeof(Account), 1, temp_accounts_fp);
        }
    }

    // Close the account files
    fclose(accounts_fp);
    fclose(temp_accounts_fp);

    // Replace the old account file with the new file if an account was found
    remove("accounts.txt");
    rename("temp_accounts.txt", "accounts.txt");

    // Record the transaction
    if (total_repaid > 0) {
        Transaction trans;
        trans.acc_no = acc_no;
        trans.amount = -total_repaid; // Negative amount for repayment
        strcpy(trans.type, "Loan Repayment");
        saveTransaction(trans);
        printf("\e[0;32mLoan repayment recorded and account balance updated.\e[0m\n");
    }
}

// function for allotment of loan
void loanAllotment() {
    int acc_no;
    double loan_amount;
    Account acc;
    Loan loan;
    FILE *loans_fp, *accounts_fp;

    // Prompt the user for account number and loan amount
    // data input with validation
    while(1) {
        printf("\nEnter account number: ");
        if (scanf("%d", &acc_no) != 1) {
            printf("\e[0;31mInvalid input. Please enter an integer.\e[0m\n");
            // Clear the input buffer (optional)
            scanf("%*[^\n]"); // Discard any remaining characters in the input buffer
            // return 1;
        } else break;
    }

    while(1) {
        printf("Enter loan amount: ");
        if (scanf("%lf", &loan_amount) != 1) {
            printf("\e[0;31mInvalid input. Please enter an integer or decimal value.\e[0m\n");
            // Clear the input buffer (optional)
            scanf("%*[^\n]"); // Discard any remaining characters in the input buffer
            // return 1;
        } else break;
    }

    // Check if loan amount is positive
    if (loan_amount <= 0) {
        printf("\e[0;33mLoan amount must be greater than zero.\e[0m\n");
        return;
    }

    // Open the loans file in append mode
    loans_fp = fopen("loans.txt", "a");
    // error handling for file not opened
    if (loans_fp == NULL) {
        printf("\e[0;31mError opening loans file.\e[0m\n");
        return;
    }

    // Set up the loan structure and write it to the loans file
    loan.acc_no = acc_no;
    loan.loan_amount = loan_amount;
    fwrite(&loan, sizeof(Loan), 1, loans_fp);
    fclose(loans_fp);

    // Open the accounts file in read and write mode 'r+'
    accounts_fp = fopen("accounts.txt", "r+");
    // error handling for file not opened
    if (accounts_fp == NULL) {
        printf("\e[0;31mError opening accounts file.\e[0m\n");
        return;
    }

    // Search for the account and update its balance
    int found = 0;
    while (fread(&acc, sizeof(Account), 1, accounts_fp)) {
        if (acc.acc_no == acc_no) {
            // Move the file pointer back to the start of the account entry
            fseek(accounts_fp, -sizeof(Account), SEEK_CUR);
            // Add the loan amount to the account balance
            acc.balance += loan_amount;
            // Write the updated account information back to the file
            fwrite(&acc, sizeof(Account), 1, accounts_fp);
            found = 1;
            break;
        }
    }

    // Close the accounts file
    fclose(accounts_fp);

    // Display message
    if (found) {
        printf("\e[0;32mLoan of %.2lf allotted to account number %d and account balance updated.\e[0m\n", loan_amount, acc_no);
    } else {
        printf("\e[0;31mAccount number %d not found. Loan allotment failed.\e[0m\n", acc_no);
    }
}

// function to handle the loan
// menu for loan handling
int handleLoan() {
    while (1) 
    {
        printf("\n\e[0;36m** Loan Management System **\e[0m\n");
        printf("1. Check Your Current Loan\n");
        printf("2. Repay Your Loan\n");
        printf("3. New Loan Allotment\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showCurrentLoans();
                break;
            case 2:
                repayLoan();
                break;
            case 3:
                loanAllotment();
                break;
            case 4:
                return 0;
            default:
                printf("\e[0;31mInvalid choice. Please try again.\e[0m\n");    
        }
    }
}

// function to handle transactions
void handleDepositWithdraw() {
    Transaction trans;
    Account acc;

    printf("\nEnter transaction details:\n");

    while(1) {
        printf("Account number: ");
        if (scanf("%d", &trans.acc_no) != 1) {
            printf("\e[0;31mInvalid input. Please enter an integer.\e[0m\n");
            // Clear the input buffer (optional)
            scanf("%*[^\n]"); // Discard any remaining characters in the input buffer
            // return 1;
        } else break;
    }

    printf("Transaction type (Deposit/Withdrawal): ");
    scanf("%s", trans.type);

    while(1) {
        printf("Amount: ");
        if (scanf("%lf", &trans.amount) != 1) {
            printf("\e[0;31mInvalid input. Please enter an integer or decimal value.\e[0m\n");
            // Clear the input buffer (optional)
            scanf("%*[^\n]"); // Discard any remaining characters in the input buffer
            // return 1;
        } else break;
    }

    // Read account details
    acc = readAccount(trans.acc_no);
    if (acc.acc_no == -1) {
        printf("\e[0;31mAccount not found.\e[0m\n");
        return;
    }

    // Update account balance
    if (strcmp(trans.type, "Deposit") == 0) {
        acc.balance += trans.amount;
    } 
    else if (strcmp(trans.type, "Withdrawal") == 0)
    {
        if (acc.balance >= trans.amount) {
            acc.balance -= trans.amount;
        } else {
            printf("\e[0;31mInsufficient balance.\e[0m\n");
            return;
        }
    } 
    else {
        printf("\e[0;31mInvalid transaction type.\e[0m\n");
        return;
    }

    // Save updated account details
    updateAccountDetails(acc);
    // save transaction details
    saveTransaction(trans);
    printf("\e[0;32mTransaction successful!\e[0m\n");
}

// function to show different exchange rates
void showExchangeRates() {
    printf("\n\e[0;36mExchange rates:\e[0m\n");
    printf("1 USD = 74 INR\n");
    printf("1 EUR = 87 INR\n");
    printf("1 GBP = 101 INR\n");
}

// function to display dashboard of the bank
void displayDashboard() {
    // calling function handle reports to display data on dashboard
    handleReports();
}

void viewAccountDetails() {
    int acc_no;
    Account acc;
    FILE *accounts_fp;

    while(1) {
        printf("\nEnter account number to view: ");
        if (scanf("%d", &acc_no) != 1) {
            printf("\e[0;31mInvalid input. Please enter an integer.\e[0m\n");
            // Clear the input buffer (optional)
            scanf("%*[^\n]"); // Discard any remaining characters in the input buffer
            // return 1;
        } else break;
    }

    // Open the accounts file
    accounts_fp = fopen("accounts.txt", "r");
    // error handling for file not opened
    if (accounts_fp == NULL) {
        printf("\e[0;31mError opening accounts file.\e[0m\n");
        return;
    }

    // Read the account information from the file
    int found = 0;
    while (fread(&acc, sizeof(Account), 1, accounts_fp)) {
        if (acc.acc_no == acc_no) {
            found = 1;
            break;
        }
    }

    // Close the accounts file
    fclose(accounts_fp);

    // Display the account details if found
    if (found) {
        printf("\nAccount details:\n");
        printf("Name: %s\n", acc.name);
        printf("DOB: %s\n", acc.dob);
        printf("Aadhar number: %s\n", acc.aadhar);
        printf("Account number: %d\n", acc.acc_no);
        printf("Mobile number: %s\n", acc.mobile);
        printf("Age: %d\n", acc.age);
        printf("Father's name: %s\n", acc.father_name);
        printf("Current balance: %.2lf\n", acc.balance); // Display current balance
    } else {
        printf("\e[0;31mAccount not found.\e[0m\n");
    }
}