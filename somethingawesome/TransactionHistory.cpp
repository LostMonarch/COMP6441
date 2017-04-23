// TransactionHistory class implementation
#include "TransactionHistory.h"

// Add a new transaction to the history
void TransactionHistory::addTransaction(transaction t) {
    history.push_back(t);
}