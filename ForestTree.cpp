/**
 * Course: CSIS217 Section 1
 * Advanced Data Structure Project composed of multiple files
 * Current File: ForestTree.cpp
 * Purpose: Implements the ForestTree class to manage the hierarchical
 *          structure of accounts, allowing operations like adding accounts,
 *          transactions, deleting transactions, and generating reports.
 * Author: [Your Name]
 * Date: [Date of Submission]
 *
 * Description:
 *  - ForestTree: Represents a collection of accounts organized in a forest structure.
 *  - Methods provided include account creation, transaction management, and hierarchical
 *    reporting of accounts.
 *
 * Functions:
 *  - ForestTree(): Constructor to initialize an empty forest tree.
 *  - ~ForestTree(): Destructor to clean up dynamically allocated memory.
 *  - void addAccount(const string& number, const string& description): Adds a new account
 *      to the forest if it doesn't already exist.
 *  - void addTransaction(const string& accountNumber, double amount, char debitCredit):
 *      Adds a transaction to a specified account.
 *  - void deleteTransaction(const string& accountNumber, int index): Deletes a transaction
 *      from the specified account using the transaction index.
 *  - Account* searchAccount(const string& number): Searches for an account by number
 *      and returns a pointer to the account if found.
 *  - void printAccountDetails(const string& number, const string& filename): Prints
 *      detailed account information to a file, including subaccounts and transactions.
 *  - void printForestTree(const string& filename): Writes the hierarchical structure
 *      of the entire forest tree to a file.
 *  - void printAccountHierarchy(ostream& os, Account* account, int level): Helper function
 *      to recursively print account hierarchy.
 */

#include "ForestTree.h"
#include <fstream>
#include <iostream>
#include <cctype>
#include <algorithm>

#include <filesystem>

using namespace std;

// Constructor: Initializes an empty forest tree
ForestTree::ForestTree() {}

// Destructor: Cleans up dynamically allocated memory
ForestTree::~ForestTree() {
    for (auto& accountPair : accounts) {
        delete accountPair.second; // Deletes each Account object
    }
}

// Adds a new account to the forest tree if it doesn't already exist
void ForestTree::addAccount(const string& number, const string& description) {
    // Trim account number and description before use
    string trimmedNumber = number;
    trimmedNumber.erase(0, trimmedNumber.find_first_not_of(" \t"));
    trimmedNumber.erase(trimmedNumber.find_last_not_of(" \t") + 1);

    string trimmedDescription = description;
    trimmedDescription.erase(0, trimmedDescription.find_first_not_of(" \t"));
    trimmedDescription.erase(trimmedDescription.find_last_not_of(" \t") + 1);

    // Validate account number
    if (!isValidAccountNumber(trimmedNumber)) {
        cout << "Error: Invalid account number. Must be numeric.\n";
        return;
    }

    // Ensure description is not empty
    if (trimmedDescription.empty()) {
        cout << "Error: Description cannot be empty.\n";
        return;
    }

    // Check if account already exists
    if (accounts.find(trimmedNumber) != accounts.end()) {
        cout << "Error: Account already exists.\n";
        return;
    }

    // Create a new account and add it to the tree
    Account* newAccount = new Account(trimmedNumber, trimmedDescription);
    accounts[trimmedNumber] = newAccount;  // Add to the forest
}


// Adds a transaction to a specific account by its account number
void ForestTree::addTransaction(const string& accountNumber, double amount, char debitCredit) {
    if (!isValidAccountNumber(accountNumber)) {
        cout << "Error: Invalid account number. Must be numeric.\n";
        return;
    }

    if (!isValidAmount(amount)) {
        cout << "Error: Transaction amount must be non-negative.\n";
        return;
    }

    if (!isValidTransactionType(debitCredit)) {
        cout << "Error: Invalid transaction type. Use 'D' for Debit or 'C' for Credit.\n";
        return;
    }

    auto it = accounts.find(accountNumber);
    if (it != accounts.end()) {
        it->second->addTransaction(Transaction(accountNumber, amount, debitCredit));
    } else {
        cout << "Error: Account not found.\n";
    }
}

// Deletes a transaction from a specified account using the transaction index
void ForestTree::deleteTransaction(const string& accountNumber, int index) {
    if (!isValidAccountNumber(accountNumber)) {
        cout << "Error: Invalid account number. Must be numeric.\n";
        return;
    }

    auto it = accounts.find(accountNumber);
    if (it != accounts.end()) {
        // Call deleteTransaction in Account class
        it->second->deleteTransaction(index); // The index is validated in Account
    } else {
        cout << "Error: Account not found.\n";
    }
}



// Searches for an account in the forest tree using its unique account number
Account* ForestTree::searchAccount(const string& number) {
    // Trim account number before using it for searching
    string trimmedNumber = number;
    trimmedNumber.erase(0, trimmedNumber.find_first_not_of(" \t"));
    trimmedNumber.erase(trimmedNumber.find_last_not_of(" \t") + 1);

    // Validate that the account number is numeric
    if (!isValidAccountNumber(trimmedNumber)) {
        cout << "Error: Invalid account number. Must be numeric.\n";
        return nullptr;
    }

    auto it = accounts.find(trimmedNumber);
    if (it != accounts.end()) {
        return it->second;
    }

    
    return nullptr;
}


// Writes detailed information about an account to a specified file
void ForestTree::printAccountDetails(const string& number, const string& filename) {
    if (!isValidAccountNumber(number)) {
        cout << "Error: Invalid account number. Must be numeric.\n";
        return;
    }

    if (!isValidFilename(filename)) {
        cout << "Error: Invalid filename. Please avoid special characters and empty input.\n";
        return;
    }

    // Check if the filename includes a directory path
    filesystem::path filePath(filename);
    
    // If the path contains a directory, check if it exists
    if (filePath.has_parent_path() && !filesystem::exists(filePath.parent_path())) {
        cout << "Error: The directory does not exist. Please provide a valid filename.\n";
        return;
    }

    // Attempt to open the file for writing
    ofstream outFile(filename);
    if (outFile.is_open()) {
        auto it = accounts.find(number);
        if (it != accounts.end()) {
            it->second->printDetails(outFile);
        } else {
            outFile << "Error: Account not found.\n";
        }
        outFile.close();
    } else {
        cout << "Error: Could not open file \"" << filename << "\" for writing.\n";
    }
}

// Writes the hierarchical structure of the entire forest tree to a specified file
void ForestTree::printForestTree(const string& filename) {
    if (!isValidFilename(filename)) {
        cout << "Error: Invalid filename. Please avoid special characters and empty input.\n";
        return;
    }

    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& accountPair : accounts) {
            if (accountPair.second->parent == nullptr) {
                printAccountHierarchy(outFile, accountPair.second, 0);
            }
        }
        outFile.close();
    } else {
        cout << "Error: Could not open file \"" << filename << "\" for writing.\n";
    }
}

// Helper function to recursively write the account hierarchy
void ForestTree::printAccountHierarchy(ostream& os, Account* account, int level) {
    if (account) {
        account->printHierarchy(os, level);
    }
}

// Validates that the account number contains only numeric characters
bool ForestTree::isValidAccountNumber(const string& accountNumber) const {
    return !accountNumber.empty() && all_of(accountNumber.begin(), accountNumber.end(), ::isdigit);
}


// Validates that the transaction amount is non-negative
bool ForestTree::isValidAmount(double amount)const {
    return amount >= 0;
}

// Validates that the transaction type is either 'D' (Debit) or 'C' (Credit)
bool ForestTree::isValidTransactionType(char debitCredit)const {
    return debitCredit == 'D' || debitCredit == 'C';
}

// Validates that the filename is non-empty and contains no invalid characters
bool ForestTree::isValidFilename(const string& filename)const {
    if (filename.empty()) {
        return false;
    }

    static const string invalidChars = "\\/:?\"<>|"; // Invalid characters for filenames
    return none_of(filename.begin(), filename.end(), [&](char c) {
        return invalidChars.find(c) != string::npos;
    });
}
