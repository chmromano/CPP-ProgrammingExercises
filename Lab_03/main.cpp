#include <iostream>
#include <string>
#include <vector>

#define STOP "stop"

using namespace std;

int main() {
    bool run = true;
    vector<string> str_vect;

    int longest_len = 0;
    int longest_index;

    for (int i = 0; run; i++) {
        cout << "Enter a string (\"stop\" to quit): ";
        string string;
        cin >> string;

        if (string == STOP) {
            run = false;
        } else {
            str_vect.push_back(string);
            if (string.size() > longest_len) {
                longest_len = string.size();
                longest_index = i;
            }
        }
    }

    int j = 0;
    for(string str: str_vect) {
        j++;
        cout << j << ": " << str << endl;
    }

    cout << "Entered " << j << " strings" << endl;
    cout << "Longest string: " << str_vect[longest_index] << ", length: " << longest_len << endl;
    cout << "Vector size: " << str_vect.size() << ", vector capacity: " << str_vect.capacity() << endl;

    return 0;
}
