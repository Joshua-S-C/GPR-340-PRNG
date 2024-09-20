// Joshua Sinclair Chong

#include <iostream>
#include <unordered_map>
#include "Generator.h"

int main() {
#pragma region Init
    // Edit Generator.h to mess with params
    
    int iterations = 1000000;

    std::unordered_map<uint32_t, size_t> xorStates;
    xorStates.clear();
    Xorshift32 xorShift;
    xorShift.init();

    std::unordered_map<uint32_t, size_t> lfgStates;
    lfgStates.clear();
    LFG lfg;
    lfg.init();

#pragma endregion

#pragma region XOR Shift
    std::cout << "[Xorshift]\n";
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
    std::cout << "\n\n[" + lfg.opName + " Lagged Fibonacci]\n";
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
        //lfg.print();  // I am getting cycles of 168K when not using a Range
    }
#pragma endregion

    return 0;
}
