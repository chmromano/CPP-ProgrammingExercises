#include <iostream>
#include "Time.h"

int main() {
    // Since no main() function was given I made a simple loop to test the implemented methods.
    while (true) {
        Time input_time;
        std::cout << "Enter a time (12:30 to quit): ";
        std::cin >> input_time;
        Time time(12, 30);
        std::cout << time << " <> " << input_time << std::endl;
        if (input_time == time) {
            std::cout << "Times are equal. Quitting program..." << std::endl;
            break;
        } else if (input_time > time) {
            std::cout << "Inputted time is greater." << std::endl << std::endl;
        } else if (input_time < time) {
            std::cout << "Inputted time is smaller." << std::endl << std::endl;
        }
    }
    return 0;
}
