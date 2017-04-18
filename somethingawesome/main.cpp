// Behavioural credit card fraud detector - main routine
#include <iostream>
#include "Bank.h"

#define PRINT_SUMMARY 0

int main(int argc, char* argv[]) {
    Bank * b = new Bank();

    // Indicate that the fraud detection system is starting
    cout << "Starting credit card fraud detector...\n";

    // Use the first command line argument to add a list of customers to the bank
    b->customersFromFile(argv[1]);

    // Summarise customers who are now part of the system
    #if PRINT_SUMMARY == 1
    b->displayCustomerInfo();
    #endif

    return 0;
}