#include <string>
#include <iostream>
#include <vector>

#include "transaction.h"

// CustomerProfile class declaration
using namespace std;

#ifndef CUSTOMER_PROFILE_H_
#define CUSTOMER_PROFILE_H_

class CustomerProfile {
    public:
        CustomerProfile(int p);
        void update(transaction t);
        void fill(int postcode, float spendAverage, float freqAverage, float onlinePercentage, vector<vendorType> &vendorList);
    private:
        int postCode;
        float averageSpend;
        float averageFrequency;
        float onlinePurchasePercentage;
        vector<vendorType> vendors;
};

#endif