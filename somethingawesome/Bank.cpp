// Bank class implementation
#include "Bank.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <fstream>
#include <regex>
#include <boost/algorithm/string.hpp>

using namespace std;

// Split a string by a given delimiter
vector<string> Bank::splitRegex(string &s, string delim) {
    regex rgx(delim);
    vector<string> r;
    back_insert_iterator< vector<string> > backInserter = back_inserter(r);

    sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
    sregex_token_iterator end;

    for (; iter != end; ++iter) {
        *(backInserter++) = *iter;
    }

    return r;
}

// Use a file to find list of customers and add them to the Bank
void Bank::customersFromFile(string f) {
    ifstream input(f);
    vector<string> v;
    vector<string> tokens;
	back_insert_iterator< vector<string> > backInserter = back_inserter(v);

    // Read customer list line by line
    for(string line; getline(input, line);) {
        *(backInserter++) = line;
    }

    // Go through each customer entry, and create a new customer every time
    vector<string>::iterator i;
    string name;
    int cardNumber;
    int postCode;
    Customer * newCustomer;

    for(i = begin(v); i != end(v); ++i) {
        string s = * i;
        tokens = splitRegex(s, "\\s+");
        name = tokens[0];
        cardNumber = atoi(tokens[1].c_str());
        postCode = atoi(tokens[2].c_str());
        newCustomer = new Customer(name, cardNumber, postCode);
        addCustomer(* newCustomer);
    }
}

// Add a new Customer to the Bank
void Bank::addCustomer(Customer &c) {
    customers.emplace(c.getCard(), c);
}

// Display a summary of the customers currently in the bank
void Bank::displayCustomerInfo() {
    int cardNumber;
    Customer * customer;
    for (auto i = customers.begin(); i != customers.end(); i++) {
        cardNumber = i->first;
        customer = & i->second;
        cout << "Card Number: " << to_string(cardNumber) << " Name: " << customer->getName() << "\n";
    }
}

// Given a line from a file representing a list of transactions, return a new transaction using the parameters provided - a transaction parser
transaction Bank::newTransactionFromString(string &s) {
        vector<string> tokens;
        int cardNumber;
        int postCode;
        int volume;
        vector<string> timeComponents;
        vector<string> dateComponents;
        transactionTime time;
        transactionDate date;
        bool online;
        vendorType vendor;
        transaction newTransaction;

        tokens = splitRegex(s, "\\s+");
        cardNumber = atoi(tokens[0].c_str());
        postCode = atoi(tokens[1].c_str());
        volume = atoi(tokens[2].c_str());
        timeComponents = splitRegex(tokens[3], ":");
        dateComponents = splitRegex(tokens[4], "\\/");
        online = parseOnline(tokens[5]);
        vendor = parseVendorType(tokens[6]);
        time.hours = atoi(timeComponents[0].c_str());
        time.minutes = atoi(timeComponents[1].c_str());
        date.day = atoi(dateComponents[0].c_str());
        date.year = atoi(dateComponents[1].c_str());

        newTransaction.card = cardNumber;
        newTransaction.postcode = postCode;
        newTransaction.value = volume;
        newTransaction.when = time;
        newTransaction.day = date;
        newTransaction.online = online;
        newTransaction.vendor = vendor;

        return newTransaction;
}

// Given a string representing the 'online' component of a transaction, return the corresponding boolean value
bool Bank::parseOnline(string &s) {
    bool ret;
    boost::algorithm::trim(s);
    ret = s == "0" ? false : true;
    return ret;
}

// Given a string representing the 'vendor type' component of a transaction, return the corresponding enum value
vendorType Bank::parseVendorType(string &s) {
    boost::algorithm::trim(s);

    if(!s.compare("RETAIL_STANDARD")) {
        return RETAIL_STANDARD;
    } else if(!s.compare("RETAIL_HIGH_END")) {
        return RETAIL_HIGH_END;
    }  else if(!s.compare("CASH_WITHDRAWAL")) {
        return CASH_WITHDRAWAL;
    } else if(!s.compare("HOSPITALITY_STANDARD")) {
        return HOSPITALITY_STANDARD;
    } else if(!s.compare("HOSPITALITY_HIGH_END")) {
        return HOSPITALITY_HIGH_END;
    } else if(!s.compare("BILL")) {  
        return BILL;
    } else if(!s.compare("HOUSEHOLD")) {
        return HOUSEHOLD;
    } else {
        cout << "Unrecognised vendor type!\n";
        return RETAIL_STANDARD;
    }
}

// Given a vendor type, return a string representing it
string Bank::vendorTypeToString(vendorType v) {
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

// Given a boolean indicating whether or not a transaction was online, return a string representing it
string Bank::onlineToString(bool o) {
    string ret;
    ret = o == true ? "Yes" : "No";
    return ret;
}

// Use file containing a list of transactions to learn about the 'normal' behaviour of each customer - a.k.a customer profiling
void Bank::learnAboutCustomers(string f) {
    ifstream input(f);
    vector<string> v;
	back_insert_iterator< vector<string> > backInserter = back_inserter(v);

    // Read transaction list line by line
    for(string line; getline(input, line);) {
        *(backInserter++) = line;
    }

    // Go through each customer entry, and create a new transaction every time
    vector<string>::iterator i;
    transaction newTransaction;

    for(i = begin(v); i != end(v); ++i) {
        string s = * i;
        newTransaction = newTransactionFromString(s);
        // Now that we have parsed the current transaction, assign it to the corresponding card holder's transaction history
        assignTransaction(newTransaction);
    }

    // Now that all new transactions have been assigned, check that we have been successful so far
    for (auto it : customers) {
        Customer c = it.second;
        c.profileCustomer();
    } 
}

// Given a transaction, display a summary of it's parameters
void Bank::displayTransactionSummary(transaction t) {
    cout << "----------------------\n";
    cout << "Transaction:\n";
    cout << "card: " << to_string(t.card) << "\n";
    cout << "postcode: " << to_string(t.postcode) << "\n";
    cout << "volume: " << to_string(t.value) << "\n";
    cout << "time: " << to_string(t.when.hours) << ":" << to_string(t.when.minutes) << "\n";
    cout << "date: " << to_string(t.day.day) << "/" << to_string(t.day.year) << "\n";
    cout << "online: " << onlineToString(t.online) << "\n";
    cout << "vendor type: " << vendorTypeToString(t.vendor) << "\n";       
}

// Assign a transaction to the corresponding card holder's transaction history
void Bank::assignTransaction(transaction t) {
    customers.at(t.card).addTransaction(t);
}