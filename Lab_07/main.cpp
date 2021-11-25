#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm> // One compiler was complaining that I didn't include this for generator, but another was fine ¯\_(ツ)_/¯
#include <iterator>
#include <numeric>

using namespace std;

// For this assignment splitting the program into multiple files didn't seem necessary.

// Class ---------------------------------------------------------------------------------------------------------------

class RandGen {
public:
    RandGen(int min_ = 1, int max_ = 10) : numbers(), min(min_), max(max_) { srand(time(nullptr)); }

    int operator()();

private:
    vector<int> numbers;
    int min;
    int max;
};

int RandGen::operator()() {
    int number;
    do {
        number = rand() % max + min;
    } while (find(numbers.begin(), numbers.end(), number) != numbers.end());
    numbers.push_back(number);
    return number;
}

// Main ----------------------------------------------------------------------------------------------------------------

void print_vect(const vector<int> &vect);

vector<int> find_match(vector<int> vector1, vector<int> vector2);

int yes_no();

int main() {
    int ch;
    int index;

    // Initialise necessary vectors and RangGen objects.
    vector<int> lotto(7), viking(6), eurojackpot(5), matches;
    RandGen lotto_gen(1, 40), viking_gen(1, 48), eurojackpot_gen(1, 50);

    // Lambda for printing.
    auto lambda = [&index](int i) {
        cout << "#" << index << ": " << i << endl;
        index++;
    };

    do {
        // Generate Lotto numbers.
        generate(lotto.begin(), lotto.end(), lotto_gen);
        cout << "Lotto: ";
        print_vect(lotto);

        // Generate Viking Lotto numbers.
        generate(viking.begin(), viking.end(), viking_gen);
        cout << "Viking Lotto: ";
        print_vect(viking);

        // Find matches and print them.
        matches = find_match(lotto, viking);
        cout << "Matching numbers: ";
        if (matches.empty()) {
            cout << "none" << endl;
        } else {
            cout << endl;
            index = 1;
            for_each(matches.begin(), matches.end(), lambda);
        }

        // Generate EuroJackpot numbers.
        generate(eurojackpot.begin(), eurojackpot.end(), eurojackpot_gen);
        cout << "EuroJackpot: ";
        print_vect(eurojackpot);

        // Find matches and print them.
        matches = find_match(matches, eurojackpot);
        cout << "Matching numbers: ";
        if (matches.empty()) {
            cout << "none" << endl;
        } else {
            cout << endl;
            index = 1;
            for_each(matches.begin(), matches.end(), lambda);
        }

        // Ask user to continue.
        ch = yes_no();
    } while (ch != 'N');

    return 0;
}

// Print the vector.
void print_vect(const vector<int> &vect) {
    ostream_iterator<int> it(cout, " ");
    copy(vect.begin(), vect.end(), it);
    cout << endl;
}

// Find the matches.
vector<int> find_match(vector<int> vector1, vector<int> vector2) {
    vector<int> matches;

    sort(vector1.begin(), vector1.end());
    sort(vector2.begin(), vector2.end());

    set_intersection(vector1.begin(), vector1.end(), vector2.begin(), vector2.end(), back_inserter(matches));

    return matches;
}

// Ask user input.
int yes_no() {
    char ch;
    while (true) {
        cout << "Do you want to continue (Y/N)? ";
        cin >> ch;
        if (!cin.good()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. ";
        } else if (toupper(ch) == 'N' || toupper(ch) == 'Y') {
            break;
        } else {
            cout << "Invalid input. ";
        }
    }
    return toupper(ch);
}