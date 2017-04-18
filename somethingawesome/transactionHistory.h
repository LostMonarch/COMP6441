// Transaction history class declaration - keeps track of all transactions performed using a single card
#include <vector>
#include "transaction.h"

using namespace std;

#ifndef TRANSACTION_HISTORY_H_
#define TRANSACTION_HISTORY_H_

class TransactionHistory {
    public:
        void addTransaction(transaction t);
        void detect();
    private:
        vector<transaction> history;
};

#endif