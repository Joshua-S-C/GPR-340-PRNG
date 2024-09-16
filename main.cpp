#include <iostream>
#include "Generator.h"

int main() {
    int iterations = 10;

    // Marsaglia
    std::cout << "[Xorshift]\n";

    Xorshift32 state1;
    state1.init();
    state1.print();

    for (int i = 0; i < iterations; i++) {
        state1.shift();
        state1.print();
    }

    // Lagged Fibbonacci
    std::cout << "\n[Lagged Fibonacci]\n";

    LFG lfg(7, 10);
    lfg.op = lfg.XOR;
    lfg.init();
    lfg.print();

    for (int i = 0; i < iterations; i++) {
        lfg.shift();
        lfg.print();
    }

    return 0;
}
