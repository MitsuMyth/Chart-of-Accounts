/**
 * Course: CSIS217 Section 1
 * Advanced Data Structure Project composed of multiple files
 * Current File: main.cpp
 * Purpose: Provides a menu-driven interface for managing a forest tree
 *          of accounts, allowing users to perform operations such as
 *          adding accounts, managing transactions, searching accounts,
 *          and generating reports.
 * Author: [Your Name]
 * Date: [Date of Submission]
 *
 * Description:
 *  - Main program that interacts with the ForestTree class.
 *  - Displays a menu for user input and performs corresponding actions
 *    on the forest tree data structure.
 *
 * Functions:
 *  - void displayMenu(): Displays the user menu for forest tree management.
 *  - void loadAccountsFromFile(ForestTree& tree, const string& filename): Loads
 *      accounts from a file and adds them to the forest tree.
 *  - int main(): The main entry point for the program.
 */

#include <iostream>
#include <fstream>
#include "ForestTree.h"
#include <limits> 

using namespace std;

// Function to display the menu options
void displayMenu() {
    cout << "\n=== Forest Tree Management ===\n";
    cout << "1. Add Account\n";
    cout << "2. Add Transaction\n";
    cout << "3. Delete Transaction\n";
    cout << "4. Search Account\n";
    cout << "5. Print Account Details\n";
    cout << "6. Print Forest Tree\n";
    cout << "7. Exit\n";
    cout << "Choose an option: ";
}

// Function to load accounts from a file
void loadAccountsFromFile(ForestTree& tree, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    cout << "Loading accounts from file: " << filename << endl;

    string line;
    while (getline(file, line)) {
        // Remove leading and trailing whitespace
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (line.empty()) continue; // Skip empty lines

        // Parse the line into account number and description
        size_t spaceIndex = line.find(' ');
        if (spaceIndex != string::npos) {
            string number = line.substr(0, spaceIndex);  // Account number
            string description = line.substr(spaceIndex + 1);  // Description

            // Trim the number and description to ensure no leading/trailing whitespace
            number.erase(0, number.find_first_not_of(" \t"));
            number.erase(number.find_last_not_of(" \t") + 1);
            description.erase(0, description.find_first_not_of(" \t"));
            description.erase(description.find_last_not_of(" \t") + 1);

            // Debugging output: show what's being read
            cout  << line << " -> Account number: " << number << ", Description: " << description << endl;

            // Ensure the account number is valid (numeric) using tree's method
            if (tree.isValidAccountNumber(number)) {
                // Attempt to add the account to the tree
                if (tree.searchAccount(number) == nullptr) {
                    tree.addAccount(number, description);
                } else {
                    cout << "Duplicate account found: " << number << " - Skipping." << endl;
                }
            } else {
                // Skip invalid account numbers and log the error
                cout << "Invalid account number found: " << number << " - Skipping." << endl;
            }
        } else {
            // Log invalid line format and skip
            cout << "Invalid line format: " << line << endl;
        }
    }

    file.close();
}

// Main function
int main() {
    ForestTree forestTree; // Initialize the forest tree
    int choice;            // User menu choice

    // Automatically load accounts from the file when the program starts
    loadAccountsFromFile(forestTree, "accountswithspace.txt");

    do {
        displayMenu(); // Display menu
        cin >> choice;

        switch (choice) {
        case 1: {
            // Add Account
            string number, description;
            cout << "Enter account number: ";
            cin >> number;
            cout << "Enter account description: ";
            cin.ignore(); // Clear input buffer
            getline(cin, description);
            forestTree.addAccount(number, description);
            break;
        }
        case 2: {
    // Add Transaction
    string accountNumber;
    double amount;
    char type;

    // Validate account number (must exist)
    bool validAccount = false;
    while (!validAccount) {
        cout << "Enter account number: ";
        cin >> accountNumber;

        // Check if account exists
        Account* account = forestTree.searchAccount(accountNumber);
        if (account) {
            validAccount = true;  // Account found, break out of the loop
        } else {
            cout << "Error: Account not found.\n";
        }
    }

    // Validate transaction amount (must be non-negative)
    bool validAmount = false;
    while (!validAmount) {
        cout << "Enter transaction amount: ";
        cin >> amount;
        
        // Check if the amount is valid (non-negative)
        if (cin.fail()) {
            cout << "Error: Invalid input. Please enter a valid transaction amount (numeric).\n";
            cin.clear();  // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input in the buffer
        } else if (amount >= 0) {
            validAmount = true;  // Valid amount
        } else {
            cout << "Error: Transaction amount must be non-negative.\n";
        }
    }

    // Validate transaction type (must be 'D' or 'C')
    bool validType = false;
    while (!validType) {
        cout << "Enter transaction type (D/C): ";
        cin >> type;

        // Check if the transaction type is valid ('D' or 'C')
        if (cin.fail()) {
            cout << "Error: Invalid input. Please enter a valid transaction type (D or C).\n";
            cin.clear();  // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input in the buffer
        } else if (type == 'D' || type == 'C') {
            validType = true;  // Valid type
        } else {
            cout << "Error: Invalid transaction type. Use 'D' for Debit or 'C' for Credit.\n";
        }
    }

    // If all inputs are valid, add the transaction
    forestTree.addTransaction(accountNumber, amount, type);
    break;
}


   
   

        case 3: {
            // Delete Transaction
            string accountNumber;
            int index;
            cout << "Enter account number: ";
            cin >> accountNumber;
            cout << "Enter transaction index to delete: ";
            cin >> index;
            forestTree.deleteTransaction(accountNumber, index);
            break;
        }
        case 4: {
            // Search Account
            string number;
            cout << "Enter account number to search: ";
            cin >> number;
            Account* account = forestTree.searchAccount(number);
            if (account) {
                cout << "Account found: " << account->number << " - " << account->description << "\n";
            } else {
                cout << "Account not found.\n";
            }
            break;
        }
        case 5: {
            // Print Account Details
            string number, filename;
            cout << "Enter account number: ";
            cin >> number;
            cout << "Enter filename to save details: ";
            cin.ignore();  // Clear the input buffer before using getline()
            getline(cin, filename);  // Now use getline to capture filenames with spaces
            forestTree.printAccountDetails(number, filename);
            break;
        }
        case 6: {
            // Print Forest Tree
            string filename;
            cout << "Enter filename to save forest tree: ";
            cin.ignore();  // Clear the input buffer before using getline()
            getline(cin, filename);  // Now use getline to capture filenames with spaces
            forestTree.printForestTree(filename);
            break;
        }
        case 7:
            // Exit
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
