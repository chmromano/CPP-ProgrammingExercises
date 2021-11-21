#include <iostream>
#include "Time.h"

int main() {
    // Since no main() function was given I made a simple loop to test the implemented methods.
    // Enter an equal time to quit.
    while (true) {
        Time input;
        std::cout << "Enter a time: ";
        std::cin >> input;
        Time time(12, 30);
        std::cout << time << " <> " << input << std::endl << std::endl;
        if (input == time) {
            std::cout << "Times are equal. Quitting..." << std::endl;
            break;
        } else if (input > time) {
            std::cout << "Inputted time is greater." << std::endl;
        } else if (input < time) {
            std::cout << "Inputted time is smaller." << std::endl;
        }
    }
    return 0;
}
