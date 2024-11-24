/**
 * Course: CSIS217 Section 71
 * Advanced Data Structure Project composed of 6 files
 * Current File: Account.h
 * Purpose: Defines the Account class, representing an account with a unique
 *          number, description, balance, parent-child relationships, and
 *          transactions.
 * Authors: Abdallah Al Jawhary, Jad Aintrazy, Omar Mohtar, Khaled Kaed Bey
 * Date: 26/11/2024
 *
 * Fields:
 *  - string number: The unique account number.
 *  - string description: A brief description of the account.
 *  - double balance: The current balance of the account.
 *  - Account* parent: Pointer to the parent account, if any.
 *  - vector<shared_ptr<Account>> children: Vector of child accounts.
 *  - vector<Transaction> transactions: List of transactions for the account.
 *
 * Functions:
 *  - Account(string number, string description, Account* parent = nullptr):
 *      Constructor to initialize account details and its parent.
 *  - void addChild(shared_ptr<Account> child):
 *      Adds a child account to the current account.
 *  - void addTransaction(const Transaction& transaction):
 *      Adds a transaction to the account and updates its balance.
 *  - void deleteTransaction(int index):
 *      Removes a transaction by index and updates balance.
 *  - void printDetails(ostream& os) const:
 *      Prints the account details, including transactions.
 */

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include "Transaction.h"

using namespace std;

/**
 * The Account class represents an account with a numeric account number,
 * a description, balance, parent-child relationships, and transactions.
 */
class Account {
public:
    string number;                         // Unique numeric account number
    string description;                    // Description of the account
    double balance;                        // Current balance of the account
    Account* parent;                       // Pointer to the parent account
    vector<shared_ptr<Account>> children;  // List of child accounts
    vector<Transaction> transactions;      // List of transactions

    // Constructor
    Account(string number, string description, Account* parent = nullptr);

    // Adds a child account
    void addChild(shared_ptr<Account> child);

    // Adds a transaction to the account and updates the balance
    void addTransaction(const Transaction& transaction);

    // Deletes a transaction by index and updates the balance
    void deleteTransaction(int index);

    // Validates that the account number is numeric
    static bool isValidAccountNumber(const string& accountNumber);

    // Creates an account after validating number and description
    bool createAccount(const string& number, const string& description);

    // Prints the account details
    void printDetails(ostream& os) const;

    // Recursively prints the account hierarchy
    void printHierarchy(ostream& os, int level) const;

    // Destructor
    ~Account();
};

#endif
