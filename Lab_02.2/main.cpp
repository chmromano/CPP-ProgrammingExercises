#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#define STOP "stop"

using namespace std;

int main() {
    int i;
    vector<string> str_vect;

    int longest_len = 0;
    int longest_index;

    // Loop until user enters "stop".
    i = 0;
    while (true) {
        cout << "Enter a string (\"stop\" to quit): ";
        string string;
        getline(cin, string); // Get whole string, including spaces.

        if (string == STOP) {
            break;
        } else if (string.empty()) { // Check for empty string.
            cout << "Invalid input. String is empty. ";
        } else {
            //Add to end of vector and check for longest string.
            str_vect.push_back(string);
            if (string.size() > longest_len) {
                longest_len = static_cast<int> (string.size());
                longest_index = i;
            }
            i++;
        }
    }

    //Print results. Check if vector is empty.
    if (str_vect.empty()) {
        cout << "\nNo string were entered." << endl;
        cout << "Vector size: " << str_vect.size() << ", vector capacity: " << str_vect.capacity() << endl;
    } else {
        cout << "\nIndex | String" << endl;

        i = 0;
        for (const string &str: str_vect) {
            cout << setw(static_cast<int> (strlen("Index"))) << i << " | " << str
                 << endl;
            i++;
        }

        cout << "\nEntered " << i << " strings." << endl;
        cout << "Longest string: \"" << str_vect[longest_index] << "\", length: " << longest_len << endl;
        cout << "Vector size: " << str_vect.size() << ", vector capacity: " << str_vect.capacity() << endl;
    }

    return 0;
}