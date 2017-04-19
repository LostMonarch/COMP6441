// This struct represents a transaction time - which will help classify customer behaviour
#ifndef TRANSACTION_TIME_H_
#define TRANSACTION_TIME_H_

typedef struct {
    int hours;
    int minutes;
} transactionTime;

typedef struct {
    int day;
    int year;
} transactionDate;

#endif
