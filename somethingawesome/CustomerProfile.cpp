// CustomerProfile class implementation
#include "CustomerProfile.h"

// Initialise a new customer profile with default values for each parameter
CustomerProfile::CustomerProfile(int p) {
    postCode = p;
    averageSpend = 0;
    averageFrequency = 0;
    onlinePurchasePercentage = 0;
}

// Fill a customer profile with values for each parameter calculated during the customer profiling phase
void CustomerProfile::fill(float spendAverage, float freqAverage, float onlinePercentage, vector<vendorType> &vendorList, vector<int> &codeList) {
    postCode = postcode;
    averageSpend = spendAverage;
    averageFrequency = freqAverage;
    onlinePurchasePercentage = onlinePercentage;
    vendors = vendorList;
    postcodes = codeList;
}