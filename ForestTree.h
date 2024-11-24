/**
 * Course: CSIS217 Section 71
 * Advanced Data Structure Project composed of 6 files
 * Current File: ForestTree.h
 * Purpose: Defines the ForestTree class, managing a tree of accounts and
 *          supporting various operations like adding accounts, transactions,
 *          and generating hierarchical reports.
 * Authors: Abdallah Al Jawhary, Jad Aintrazy, Omar Mohtar, Khaled Kaed Bey
 * Date: 26/11/2024
 *
 * Fields:
 *  - unordered_map<string, Account*> accounts: Stores all accounts by their
 *    unique account numbers.
 *
 * Functions:
 *  - ForestTree(): Constructor to initialize an empty forest tree.
 *  - ~ForestTree(): Destructor to clean up dynamically allocated memory.
 *  - void addAccount(const string& number, const string& description):
 *      Adds a new account to the forest tree.
 *  - void addTransaction(const string& accountNumber, double amount,
 *                        char debitCredit):
 *      Adds a transaction to an account and updates balances up the hierarchy.
 *  - void deleteTransaction(const string& accountNumber, int index):
 *      Deletes a transaction from an account by its index.
 *  - Account* searchAccount(const string& number):
 *      Searches for and returns an account by its number.
 *  - void printAccountDetails(const string& number, const string& filename):
 *      Writes the details of a specific account to a file.
 *  - void printForestTree(const string& filename):
 *      Writes the hierarchical structure of the forest tree to a file.
 */

#ifndef FOREST_TREE_H
#define FOREST_TREE_H

#include <unordered_map>
#include <string>
#include <ostream>
#include "Account.h"

using namespace std;

/**
 * Class: ForestTree
 * Purpose: Manages a hierarchical structure of accounts, supporting operations
 *          like adding accounts, managing transactions, and generating reports.
 */
class ForestTree {
private:
    // Stores all accounts by their unique account numbers
    unordered_map<string, Account*> accounts;

    // Helper function to recursively print the account hierarchy
    void printAccountHierarchy(ostream& os, Account* account, int level);

    // Validation utility functions
    // Validate numeric account number
    bool isValidAmount(double amount) const;                     // Validate non-negative amounts
    bool isValidTransactionType(char debitCredit) const;         // Validate 'D' or 'C'
    bool isValidFilename(const string& filename) const;          // Validate valid filenames

public:
 bool isValidAccountNumber(const string& accountNumber) const;
    // Constructor and Destructor
    ForestTree();  // Initializes an empty forest tree
    ~ForestTree(); // Cleans up dynamically allocated memory

    // Account and Transaction Management
    void addAccount(const string& number, const string& description);  // Adds a new account
    void addTransaction(const string& accountNumber, double amount, char debitCredit);  // Adds a transaction
    void deleteTransaction(const string& accountNumber, int index);  // Deletes a transaction by index

    // Account Search
    Account* searchAccount(const string& number);  // Searches for an account by its number

    // Reporting
    void printAccountDetails(const string& number, const string& filename);  // Prints account details to a file
    void printForestTree(const string& filename);  // Prints the entire forest tree structure to a file
};

#endif
