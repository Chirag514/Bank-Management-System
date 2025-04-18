#include "head.h" // includng header file

// function to save account detsils
void saveAccount(Account acc) {
    FILE *fp;
    fp = fopen("accounts.txt", "a");
    // error handling for file not opened
    if (fp == NULL) {
        printf("\e[0;31mError opening file.\e[0m\n");
        return;
    }

    fwrite(&acc, sizeof(Account), 1, fp);
    fclose(fp); // close the file
}

// function to read account deatils
// function of account structure type
// it returns account structure of a particular account 
Account readAccount(int acc_no) {
    FILE *fp;
    Account acc;
    int found = 0;

    fp = fopen("accounts.txt", "r");

    // error handling for file not opened
    if (fp == NULL) {
        printf("\e[0;31mError opening file.\e[0m\n");
        acc.acc_no = -1;
        return acc;
    }
    // returning the desired account
    while (fread(&acc, sizeof(Account), 1, fp)) {
        if (acc.acc_no == acc_no) {
            fclose(fp); // close the file when read done
            return acc;
        }
    }

    fclose(fp); // close the file
    acc.acc_no = -1; // Account not found
    return acc;
}

// checking the existance of particular account
int accountExists(int acc_no) {
    FILE *fp;
    Account acc;
    int found = 0;

    fp = fopen("accounts.txt", "r");
    // error handling for file not opened
    if (fp == NULL)
    {
        return 0;
    }
    // if account exists return 1
    while (fread(&acc, sizeof(Account), 1, fp)) {
        if (acc.acc_no == acc_no) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp); // close the file
    return 0; // account does not exist
}

// function to update account details
void updateAccountDetails(Account acc) {
    FILE *fp;
    FILE *temp_fp;
    Account tempAcc;

    // Open accounts file and temporary file for editing
    fp = fopen("accounts.txt", "r");
    temp_fp = fopen("temp.txt", "w");
    // error handling for file not opened
    if (fp == NULL || temp_fp == NULL) {
        printf("\e[0;31mError opening file.\e[0m\n");
        return;
    }

    // Read and write account data
    while (fread(&tempAcc, sizeof(Account), 1, fp)) {
        // if account found start asking for new deatils
        if (tempAcc.acc_no == acc.acc_no) {
            // Write updated account data
            fwrite(&acc, sizeof(Account), 1, temp_fp);
        } else {
            // Write original account data
            fwrite(&tempAcc, sizeof(Account), 1, temp_fp);
        }
    }

    // Close the files
    fclose(fp);
    fclose(temp_fp);

    // Replace old file with new one
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");
}

// function to save transaction
void saveTransaction(Transaction trans) {
    FILE *fp;
    fp = fopen("transactions.txt", "a");
    
    // error handling for file not opened
    if (fp == NULL) {
        printf("\e[0;31mError opening file.\e[0m\n");
        return;
    }

    // saving the transaction to file
    fwrite(&trans, sizeof(Transaction), 1, fp);
    fclose(fp); // close the file
}

// function to save loan
void saveLoan(Loan loan) {
    FILE *fp;
    fp = fopen("loans.txt", "a");
    // error handling for file not opened
    if (fp == NULL) {
        printf("\e[0;31mError opening file.\e[0m\n");
        return;
    }

    // saving the loan to file
    fwrite(&loan, sizeof(Loan), 1, fp);
    fclose(fp); // close the file
}
