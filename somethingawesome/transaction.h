// Declaraction for the structure of a credit card transaction
#include <ctime>

#include "vendorType.h"

#ifndef TRANSACTION_H_
#define TRANSACTION_H_

typedef struct {
    int card;
    int postcode;
    int value;
    time_t when;
    bool online;
    vendorType vendor;
} transaction;

#endif