// Transaction history class declaration - keeps track of all transactions performed using a single card
#include <vector>
#include "transaction.h"

using namespace std;

class transactionHistory {
    public:
        void addTransaction(transaction t);
        void detect();
    private:
        vector<transaction> history;
}