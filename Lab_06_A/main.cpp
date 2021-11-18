#include <iostream>
#include "Time.h"

int main() {
    while(1) {
        Time time2;
        std::cout << "Enter a time: ";
        std::cin >> time2;
        Time time(23, 40);
        std::cout << time << " <> " << time2 << std::endl << std::endl;
        if (time2 == time) {
            std::cout << "Same." << std::endl;
        } else if (time2 > time) {
            std::cout << "Greater." << std::endl;
        } else if (time2 < time) {
            std::cout << "Smaller." << std::endl;
        }
    }
    return 0;
}
