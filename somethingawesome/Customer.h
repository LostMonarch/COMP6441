// Customer class declaration - describes one card holder in the bank
#include "CustomerProfile.h"
#include "TransactionHistory.h"
#include "card.h"
#include <string>

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

class Customer {
    public:
        void detect();
        void addTransaction(transaction t);
    private:
        void updateProfile();
        void updateRisk();
        void notifyFraud();

        string name;
        Card creditCard;
        TransactionHistory history;
        float currentRisk;
        CustomerProfile profile;
};

#endif