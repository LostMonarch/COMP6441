// Bank class implementation
#include "Bank.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <fstream>

using namespace std;

// Use a file to find list of customers and add them to the Bank
void Bank::customersFromFile(string f) {
    std::ifstream input(f);

    for(std::string line; getline(input, line);) {
        cout << "hello\n";
    }
}
