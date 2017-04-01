#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

#define USAGE_CORRECT 2
#define SUCCESS 0
#define FAILURE 1

int main (int argc, char *argv[]) {

	// Make sure input has been entered correctly
	if(argc != USAGE_CORRECT) {
		cout << "Incorrect usage, please try again\n";
		return FAILURE;
	} else {
		cout << "Ciphertext entered, thinking hard...\n";
	}

	string in = argv[1];
	stringstream stream;
	stream.str(in);
	string item;
	vector<string> v;
	back_insert_iterator< vector<string> > backInserter = back_inserter(v);

	// Go through each token in the input ciphertext and store them in a vector
	while(getline(stream, item, ' ')) {
		*(backInserter++) = item;
	}

	// The length of each token should be constant for this encryption technique
	vector<string>::iterator i = v.begin();
	string first = *i;
	int tokenSize = first.size();
	int vectorSize = v.size();

	// Knowing the tokens and their sizes, we can decode the message
	for(int i = 0; i < tokenSize; i++) {
		for(int j = 0; j < vectorSize; j++) {
			string currElement = v.at(j);
			cout << currElement.at(i);
		}
	}
	cout << "\n";

	return SUCCESS;
}