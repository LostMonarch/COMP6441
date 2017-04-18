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