// Customer class declaration - describes one card holder in the bank
#include "CustomerProfile.h"
#include "TransactionHistory.h"
#include "card.h"
#include <string>

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

class Customer {
    public:
        Customer(string n, int c, int p);
        void detect();
        void addTransaction(transaction t);
        string getName();
        int getCard();
        void checkHistory();
        void profileCustomer();
        int getNumTransactions() { return history->getNumTransactions(); };
    private:
        void updateProfile();
        void updateRisk();
        void notifyFraud();
        string vendorTypeToString(vendorType v);
        
        // Members
        string name;
        Card creditCard;
        TransactionHistory * history;
        float currentRisk;
        CustomerProfile * profile;
};

#endif