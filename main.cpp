#include <iostream>
#include <unordered_map>
#include "Generator.h"

int main() {
    int iterations = 1000;

#pragma region XOR Shift
    // Marsaglia
    std::cout << "[Xorshift]\n";
    std::unordered_map<int, size_t> xorStates;

    Xorshift32 xorShift;
    xorShift.init();
    xorShift.print();

    for (int i = 0; i < iterations; i++) {
        if (xorStates.contains(xorShift.a)) {
            // Warmup Ends
            std::cout << "\nDuped Number: " << xorShift.a;
            std::cout << "\tOriginal Index: " << xorStates[xorShift.a];
            std::cout << "\tDuped Index: " << i;
            std::cout << "\tCycle Length: " << i - xorStates[xorShift.a];

            break;
        }

        xorStates.insert({ xorShift.a, i });

        xorShift.shift();
        xorShift.print();
    }
#pragma endregion

#pragma region Lagged Fibonacci Generator
    std::cout << "\n\n[Lagged Fibonacci]\n";
    std::unordered_map<int, size_t> lfgStates;

    LFG lfg(24, 55);
    lfg.op = lfg.ADD;
    lfg.init();
    lfg.print();

    for (int i = 0; i < iterations; i++) {
        if (lfgStates.contains(lfg.a)) {
            // Warmup Ends
            std::cout << "\nDuped Number: " << lfg.a;
            std::cout << "\tOriginal Index: " << lfgStates[lfg.a];
            std::cout << "\tDuped Index: " << i;
            std::cout << "\tCycle: " << i - lfgStates[lfg.a];

            break;
        }

        lfgStates.insert({ lfg.a, i });

        lfg.shift();
        lfg.print();
    }
#pragma endregion

    return 0;
}
