#include <iostream>
#include "Xorshift32.h"

// Do this one next https://en.wikipedia.org/wiki/Lagged_Fibonacci_generator


int main() {
    Xorshift32 state1;
    state1.init();
    state1.print();

    for (int i = 0; i < 100; i++) {
        state1.shift();
        state1.print();
        std::cout << ", \t";
    }

    return 0;
}
