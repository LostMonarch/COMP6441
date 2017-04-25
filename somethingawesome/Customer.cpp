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

// Using the customer's transaction history, fill out their customer profile - effectively establishing what we will consider 'normal' behaviour for the customer
void Customer::profileCustomer() {
    int transactionCounter = 0;
    float averageSpend = 0;
    float averageFrequency = 0;
    int onlinePurchaseCounter = 0;
    float onlinePurchasePercentage = 0;
    vector<vendorType> vendors;
    vector<int> postCodes;
    int lastDay; 
    int currDay;

    // Get the customer's transaction history to be used for profiling
    vector<transaction> transactions = history->getHistory();

    // Get the day on which the customer made their first purchase
    currDay = transactions[0].day.day;

    // Go through each transaction in the customer's transaction history and calculate parameters for their profile
    for(transaction t : transactions) {
        transactionCounter++;
        // Add to the total spend accumulator
        averageSpend = (float) (averageSpend + t.value);
        // Add the vendor type for this transaction to the list of vendors if it isn't already in the list
        if(find(vendors.begin(), vendors.end(), t.vendor) == vendors.end()) {
            vendors.push_back(t.vendor);
        }
        // Add the postcode for this transaction to the list of postcodes if it isn't already in the list
        if(find(postCodes.begin(), postCodes.end(), t.postcode) == postCodes.end()) {
            postCodes.push_back(t.postcode);
        }
        // If the purchase was online, increment the total number of online purchases
        if(t.online) {
            onlinePurchaseCounter++;
        }
        // Add to the total number of day diffs (will be used to calculate the average number of days between purchases)
        if(transactionCounter > 1) {
            currDay = t.day.day;
            averageFrequency = (float) (averageFrequency + (currDay - lastDay));
        }
        // Keep track of the current day for comparison with the next day
        lastDay = currDay;
    }

    // To finish calculating averages, divide them by the total number of transactions in the customer's history
    averageSpend = averageSpend / getNumTransactions();
    averageFrequency = averageFrequency / getNumTransactions();
    onlinePurchasePercentage = (float) onlinePurchaseCounter / getNumTransactions();

    // Summarise information for the user
    cout << "------------------------------\nProfiling Summary            |\n------------------------------\n";
    cout << "Customer: " << name << "\n";
    cout << "Card number: " << to_string(creditCard.number) << "\n";
    cout << "Postcode: " << to_string(profile->getPostcode()) << "\n";
    cout << "Average spend per transaction: " << to_string(averageSpend) << "\n";
    cout << "Average number of days between transactions: " << to_string(averageFrequency) << "\n";
    cout << "Percentage of purchases made online: " << to_string(onlinePurchasePercentage * 100) << "%\n";
    cout << "Commonly visited vendor types: ";
    for(vendorType v : vendors) {
         cout << vendorTypeToString(v) << " ";
    }
    cout << "\n";
    cout << "Commonly visited postcodes: ";
    for(int c : postCodes) {
         cout << to_string(c) << " ";
    }
    cout << "\n";

    // Finally, use the calculated information to populate the customer's profile
    profile->fill(averageSpend, averageFrequency, onlinePurchasePercentage, vendors, postCodes);
}

// Given a vendor type, return a string representing it
string Customer::vendorTypeToString(vendorType v) {
    switch(v) {
        case RETAIL_STANDARD:
            return "RETAIL_STANDARD";
        case RETAIL_HIGH_END:
            return "RETAIL_HIGH_END";
        case CASH_WITHDRAWAL:
            return "CASH_WITHDRAWAL";
        case HOSPITALITY_STANDARD:
            return "HOSPITALITY_STANDARD";
        case HOSPITALITY_HIGH_END:
            return "HOSPITALITY_HIGH_END";
        case BILL:
            return "BILL";
        case HOUSEHOLD:
            return "HOUSEHOLD";
        default:
            cout << "Unknown enum value\n";
            return "UNKNOWN";
    }
}