// TransactionHistory class implementation
#include "TransactionHistory.h"
#include <iostream>

// Add a new transaction to the history
void TransactionHistory::addTransaction(transaction t) {
    history.push_back(t);
}

// A simple sanity check for customer transaction assignment
void TransactionHistory::check() {
    cout << to_string(history.size()) << "\n";
}