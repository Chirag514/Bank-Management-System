# Banking System Simulation

A console-based banking system application developed in C, designed to manage bank accounts, transactions, loans, and generate reports.

## Features

- **Account Management**:
  - Create, edit, view, and delete accounts.
  - Store account details (name, DOB, Aadhar, balance, etc.).
- **Loan Management**:
  - Apply for new loans.
  - Repay existing loans.
  - View current loans.
- **Transactions**:
  - Deposit and withdraw funds.
  - Track transaction history (bank statements).
- **Reports**:
  - Dashboard displaying total bank balance, number of customers, and total loans.
- **Exchange Rates**:
  - Display currency exchange rates (USD, EUR, GBP to INR).

## Installation

1. **Prerequisites**:
   - GCC compiler (to compile C code).
   - Terminal or command-line interface.

2. **Compilation**:
   ```bash
   gcc main.c bank_operations.c bank_reports.c data_management.c -o banking_system
