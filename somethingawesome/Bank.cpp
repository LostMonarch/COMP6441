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
    customers.emplace(c.getName(), c);
}

// Display a summary of the customers currently in the bank
void Bank::displayCustomerInfo() {
    string customerName;
    Customer * customer;
    for (auto i = customers.begin(); i != customers.end(); i++) {
        customerName = i->first;
        customer = & i->second;
        cout << "Key: " << customerName << " Name: " << customer->getName() << "\n";
    }
}