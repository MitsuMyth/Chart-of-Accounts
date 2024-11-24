/**
* Course: CSIS217 Section 1
 * Advanced Data Structure Project composed of 6 files
 * Current File: Transaction.h
 * Purpose: Defines the Transaction class representing a single transaction
 *          with details such as account number, amount, and transaction type.
 * Author: [Your Name]
 * Date: [Date of Submission]
 *
 * Fields:
 *  - string accountNumber: The account associated with the transaction.
 *  - double amount: The transaction amount.
 *  - char debitCredit: 'D' for debit, 'C' for credit transaction.
 *
 * Functions:
 *  - Transaction(string accountNumber, double amount, char debitCredit):
 *      Constructor to initialize the transaction fields.
 *  - friend ostream& operator<<(ostream& os, const Transaction& t):
 *      Overloaded operator to display transaction details.
 */

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>
#include <stdexcept> // For exception handling

using namespace std;

/**
 * The Transaction class represents a single financial transaction
 * associated with an account, including amount and type (debit/credit).
 */
class Transaction {
public:
    string accountNumber;   // Account associated with the transaction
    double amount;          // Transaction amount
    char debitCredit;       // 'D' for Debit, 'C' for Credit

    // Constructor
    Transaction(const string& accountNumber, double amount, char debitCredit);

    // Overloaded << operator to print transaction details
    friend ostream& operator<<(ostream& os, const Transaction& t);

    // Validates account number format (only numeric)
    static bool isValidAccountNumber(const string& accountNumber);

    // Validates transaction type (must be 'D' or 'C')
    static bool isValidTransactionType(char debitCredit);

    // Validates transaction amount (must be non-negative)
    static bool isValidAmount(double amount);
};

#endif
