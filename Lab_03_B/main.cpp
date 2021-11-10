#include <iostream>
#include <string>
#include <vector>

#define STOP "stop"

using namespace std;

void backwards(vector<string> &vect);

void print_vect(const vector<string> &vect);

int main() {
    vector<string> str_vect;

    while (true) {
        cout << "Enter a string (\"stop\" to quit): ";
        string string;
        getline(cin, string); // Get whole string, including spaces.

        if (string == STOP) {
            break;
        } else if (string.empty()) { // Check for empty string.
            cout << "Invalid input. String is empty. ";
        } else {
            //Add to end of vector.
            str_vect.push_back(string);
        }
    }

    cout << endl;

    //Print results. Check if vector is empty.
    if (str_vect.empty()) {
        cout << "No strings were entered." << endl;
    } else {
        print_vect(str_vect);

        backwards(str_vect);
        cout << endl;

        print_vect(str_vect);
    }

    return 0;
}

//Reverse strings, sort vector, reverse vector.
void backwards(vector<string> &vect) {
    for (string &i: vect) {
        reverse(i.begin(), i.end());
    }
    sort(vect.begin(), vect.end());
    reverse(vect.begin(), vect.end());
}

//Simple function to print a vector.
void print_vect(const vector<string> &vect) {
    for (const string &i: vect) {
        cout << i << endl;
    }
}