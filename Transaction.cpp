/**
 * Course: CSIS217 Section 71
 * Advanced Data Structure Project composed of 6 files
 * Current File: Transaction.cpp
 * Purpose: Implements the Transaction class, including its constructor
 *          and overloaded << operator.
 * Authors: Khaled Kaed Bey, Jad Aintrazy, Omar Mohtar, Abdallah Al Jawhary
 * Date: [Date of Submission]
 */
#include <algorithm> // Required for all_of

#include "Transaction.h"

// Constructor to initialize transaction details with validation
Transaction::Transaction(const string& accountNumber, double amount, char debitCredit) {
    if (!isValidAccountNumber(accountNumber)) {
        throw invalid_argument("Error: Invalid account number. Must contain only numeric characters.");
    }

    if (!isValidAmount(amount)) {
        throw invalid_argument("Error: Transaction amount must be non-negative.");
    }

    if (!isValidTransactionType(debitCredit)) {
        throw invalid_argument("Error: Invalid transaction type. Use 'D' for Debit or 'C' for Credit.");
    }

    this->accountNumber = accountNumber;
    this->amount = amount;
    this->debitCredit = debitCredit;
}

// Overloaded << operator to print transaction details
ostream& operator<<(ostream& os, const Transaction& t) {
    os << "Account: " << t.accountNumber << ", Amount: " << t.amount
       << ", Type: " << (t.debitCredit == 'D' ? "Debit" : "Credit");
    return os;
}

// Validates account number format (only numeric)
bool Transaction::isValidAccountNumber(const string& accountNumber) {
    return !accountNumber.empty() && all_of(accountNumber.begin(), accountNumber.end(), ::isdigit);
}

// Validates transaction type (must be 'D' or 'C')
bool Transaction::isValidTransactionType(char debitCredit) {
    return debitCredit == 'D' || debitCredit == 'C';
}

// Validates transaction amount (must be non-negative)
bool Transaction::isValidAmount(double amount) {
    return amount >= 0;
}
