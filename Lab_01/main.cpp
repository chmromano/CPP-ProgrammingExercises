#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

int mean(const int *array, int n);

int main() {
    srand(time(nullptr)); // Apparently nullptr is the better way to use NULL in C++.

    cout << "Enter number of integers to generate: ";
    int n_numbers;
    while (true) {
        cin >> n_numbers;
        // Input checking.
        // cin.good() returns true if none of the stream's error flags are set. If a different type than expected is
        // entered, the failbit error state flag is set for the stream.
        if (n_numbers <= 0 || !cin.good()) {
            // cin.clear() clears the error flags of cin.
            cin.clear();
            // cin.ignore() ignores the rest of the line up to a certain character or EOF. The first argument specifies
            // the max number of characters to ignore. numeric_limits<streamsize>::max() is the size of the buffer, so
            // all characters are ignored. Second argument is the "up to a certain character" character (in this case '\n').
            // So it ignores all characters in the buffer until '\n' (or EOF) is encountered.
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter a number greater than 0: ";
        } else {
            break;
        }
    }

    cout << "\nIndex | Number" << endl;

    int *numbers;
    numbers = new int[n_numbers];
    // Generate the random numbers.
    for (int i = 0; i < n_numbers; i++) {
        numbers[i] = rand() % 100;
        cout << setw((int) strlen("Index")) << i << " | " << setw((int) strlen("Number")) << numbers[i]
             << endl;
    }

    cout << "\nMean: " << mean(numbers, n_numbers) << endl;

    delete numbers;
    return 0;
}

int mean(const int *array, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += array[i];
    }
    return sum / n;
}