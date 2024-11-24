/**
 * Course: CSIS217 Section 71
 * Advanced Data Structure Project composed of 6 files
 * Current File: Account.cpp
 * Purpose: Implements the Account class, including methods for adding
 *          children, transactions, and printing account details.
 * Authors: Abdallah Al Jawhary, Jad Aintrazy, Omar Mohtar, Khaled Kaed Bey
 * Date: 26/11/2024
 */

#include "Account.h"
#include <cctype>
#include <algorithm>

// Constructor to initialize account details
Account::Account(string number, string description, Account* parent)
    : number(move(number)), description(move(description)), balance(0), parent(parent) {}

// Adds a child account
void Account::addChild(shared_ptr<Account> child) {
    if (child) {
        children.push_back(move(child));
    } else {
        cerr << "Error: Attempted to add a null child to account " << number << endl;
    }
}

// Adds a transaction to the account
void Account::addTransaction(const Transaction& transaction) {
    transactions.push_back(transaction);
    balance += (transaction.debitCredit == 'D' ? transaction.amount : -transaction.amount);
}

// Deletes a transaction by index
void Account::deleteTransaction(int index) {
    if (index >= 0 && index < transactions.size()) {
        auto transaction = transactions[index];
        balance -= (transaction.debitCredit == 'D' ? transaction.amount : -transaction.amount);
        transactions.erase(transactions.begin() + index);
        cout << "Transaction successfully deleted.\n"; // Confirmation message
    } else {
        cerr << "Error: Invalid transaction index for account " << number << ". Index out of range.\n";
    }
}

// Validates the account number to ensure it contains only numeric characters
bool Account::isValidAccountNumber(const string& accountNumber) {
    return !accountNumber.empty() && all_of(accountNumber.begin(), accountNumber.end(), ::isdigit);
}

// Creates an account after validating the input
bool Account::createAccount(const string& number, const string& description) {
    if (!isValidAccountNumber(number)) {
        cerr << "Error: Invalid account number. Only numeric values are allowed.\n";
        return false;
    }

    if (description.empty()) {
        cerr << "Error: Description cannot be empty.\n";
        return false;
    }

    this->number = number;
    this->description = description;
    return true;
}

// Prints account details, including the index of each transaction
void Account::printDetails(ostream& os) const {
    // Print account number and the first 10 characters of the description
    os << "Account Number: " << number << "\n"
       << "Description: " << description.substr(0, 10) << "\n"  // Only first 10 characters
       << "Balance: $" << balance << "\n"
       << "Transactions:\n";

    // Print each transaction with its index
    for (int i = 0; i < transactions.size(); ++i) {
        const auto& transaction = transactions[i];
        os << "Index " << i << ": " << transaction << "\n";  // Print index with the transaction
    }
}


// Destructor
Account::~Account() {
    // No additional cleanup needed as children are managed using shared_ptr
}

// Prints the account hierarchy recursively
void Account::printHierarchy(ostream& os, int level) const {
    os << string(level * 4, ' ') << number << " - " << description
       << " (Balance: $" << balance << ")\n";

    if (!transactions.empty()) {
        os << string((level + 1) * 4, ' ') << "Transactions:\n";
        for (const auto& transaction : transactions) {
            os << string((level + 2) * 4, ' ') << transaction << "\n";
        }
    }

    for (const auto& child : children) {
        child->printHierarchy(os, level + 1);
    }
}
