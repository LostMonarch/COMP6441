// Bank class declaraction - the bank represents the highest level of the fraud detection system, holding customers and the fraud detector itself
#include "Customer.h"
#include "FraudDetector.h"

#include <string>
#include <unordered_map>

#ifndef BANK_H_
#define BANK_H_

using namespace std;

class Bank {
    public:
        void customersFromFile(string f);
        void addCustomer(Customer &c);
        void start();
        void addFraudDetector(detectorTypeID id);
        void trainFromFile(string f);
        void displayCustomerInfo();
    private:
        void detect();
        vector<string> splitRegex(string &s, string delim);

        unordered_map<string, Customer> customers;
        FraudDetector detector;
};

#endif