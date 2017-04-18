#include <string>
#include <iostream>
#include <vector>

#include "transaction.h"

// CustomerProfile class declaration
using namespace std;

class CustomerProfile {
    public:
        void update(transaction t);
    private:
        int postcode;
        float averageSpend;
        float averageFrequency;
        float onlinePurchasePercentage;
        vector<vendorType> vendors;
};