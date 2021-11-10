#include <iostream>
#include <vector>
#include <iomanip>
#include <numeric>

using namespace std;

int count_digits(double tmp);

int main() {
    int spacing = 0;

    vector<double> doubles_vect;
    while (true) {
        cout << "Enter a double: ";

        double tmp;
        cin >> tmp;

        // Input checking.
        if (!cin.good()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. ";
        } else if (tmp >= 0) {
            //Append to vector.
            doubles_vect.push_back(tmp);

            //Count digits.
            int digits = count_digits(tmp) + 4; //4 to account for the '.' and 3 decimals.
            if (digits > spacing) spacing = digits;
        } else {
            break;
        }
    }

    cout << endl;

    if (doubles_vect.empty()) {
        cout << "No numbers were entered." << endl;
    } else {
        //Sort the vector.
        sort(doubles_vect.begin(), doubles_vect.end());
        //Just trying stuff out and learning. const double &i means working with the original vector element,
        //but without being able to modify it. I assume it's good in this case since I'm just printing the value.
        for (const double &i: doubles_vect) {
            cout << fixed << right << setw(spacing) << setprecision(3) << i << endl;
        }
    }

    return 0;
}

//Function to count the digits in the integer-part of the double.
int count_digits(double tmp) {
    int digits = 0;
    while (tmp > 1) {
        tmp /= 10;
        digits++;
    }
    return digits;
}