// Declaraction for the structure of a credit card transaction
#include "vendorType.h"
#include "transactionTime.h"

#ifndef TRANSACTION_H_
#define TRANSACTION_H_

typedef struct {
    int card;
    int postcode;
    int value;
    transactionTime when;
    bool online;
    vendorType vendor;
} transaction;

#endif