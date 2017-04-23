// Customer class implementation
#include "Customer.h"

// Customer constructor
Customer::Customer(string n, int c, int p) {
    name = n;
    creditCard.owner = n;
    creditCard.number = c;
    history = new TransactionHistory();
    currentRisk = 0;
    profile = new CustomerProfile(p);
}

// Returns the Customer's name
string Customer::getName() {
    return name;
}

// Returns the Customer's credit card number
int Customer::getCard() {
    return creditCard.number;
}

// Add a transaction to the customer's transaction history
void Customer::addTransaction(transaction t) {
    history->addTransaction(t);
}

// A simple sanity check to make sure transactions have been assigned properly
void Customer::checkHistory() {
    history->check();
}