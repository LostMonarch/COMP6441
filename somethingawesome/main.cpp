// Behavioural credit card fraud detector - main routine
#include <iostream>
#include "Bank.h"

#define PRINT_SUMMARY 1

int main(int argc, char* argv[]) {
    Bank * b = new Bank();

    // Indicate that the fraud detection system is starting
    cout << "Starting credit card fraud detector...\n";

    // Use the first command line argument to add a list of customers to the bank
    cout << "Adding customers...\n";    
    b->customersFromFile(argv[1]);

    // Summarise customers who are now part of the system
    #if PRINT_SUMMARY == 1
    b->displayCustomerInfo();
    #endif

    // Learn about the behaviour of each customer using a list of transactions - also known as customer profiling
    cout << "Using transaction history to learn about customers...\n";
    b->learnAboutCustomers(argv[2]);

    // Train the fraud detection system using a list of transactions whose fraudulence is already known - (the machine learning part)
    

    return 0;
}