#include <iostream>
#include <vector>
#include <ctime>

using namespace std;


// Class UniqueRng -----------------------------------------------------------------------------------------------------

class UniqueRng {
private:
    vector<int> numbers;
    int min;
    int max;
public:
    UniqueRng(int min_ = 1, int max_ = 10) : numbers(), min(min_), max(max_) { srand(time(nullptr)); }

    int operator()() {
        int number;
        do {
            if (numbers.size() == (max - min + 1)) throw runtime_error("Unable to produce unique random number");
            number = rand() % (max - min + 1) + min;
        } while (find(numbers.begin(), numbers.end(), number) != numbers.end());
        numbers.push_back(number);
        return number;
    };
};


// Main ----------------------------------------------------------------------------------------------------------------

void test_generator(UniqueRng ur, int count);

int main() {
    UniqueRng randGen(5, 13);
    test_generator(randGen, 6);
    test_generator(randGen, 9);
    test_generator(randGen, 13);

    UniqueRng randGen2(1, 35);
    test_generator(randGen2, 7);
    test_generator(randGen2, 7);
    test_generator(randGen2, 7);
    test_generator(randGen2, 70);

    return 0;
}

void test_generator(UniqueRng ur, int count) {
    vector<int> vect;
    cout << "Generating numbers:" << endl;
    for (int i = 0; i < count; i++) {
        try {
            vect.push_back(ur());
        } catch (const runtime_error &e) {
            cout << "Exception: " << e.what() << endl;
            cout << "Tried to generate " << count << " numbers. Got only " << i << endl;
            break;
        }
    }
    for (auto item: vect) cout << item << endl;
    cout << "End of generator" << endl;
}