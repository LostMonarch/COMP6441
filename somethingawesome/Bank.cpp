// Bank class implementation
#include "Bank.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <fstream>
#include <regex>

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

// Use file containing a list of transactions to learn about the 'normal' behaviour of each customer - a.k.a customer profiling
void Bank::learnAboutCustomers(string f) {
    ifstream input(f);
    vector<string> v;
    vector<string> tokens;
	back_insert_iterator< vector<string> > backInserter = back_inserter(v);

    // Read transaction list line by line
    for(string line; getline(input, line);) {
        *(backInserter++) = line;
    }

    // Go through each customer entry, and create a new customer every time
    vector<string>::iterator i;
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

    for(i = begin(v); i != end(v); ++i) {
        string s = * i;
        tokens = splitRegex(s, "\\s+");
        cardNumber = atoi(tokens[0].c_str());
        postCode = atoi(tokens[1].c_str());
        volume = atoi(tokens[2].c_str());
        timeComponents = splitRegex(tokens[3], ":");
        dateComponents = splitRegex(tokens[3], "/");
        cout << to_string(cardNumber) << " " << to_string(postCode) << " " << to_string(volume) << " " << to_string(timeComponents.size()) << " " << to_string(dateComponents.size()) << "\n"; 
    }
}