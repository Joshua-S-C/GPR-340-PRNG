// Joshua Sinclair Chong

#include <iostream>
#include <unordered_map>
#include "Generator.h"

typedef std::unordered_map<uint16_t, size_t> StatesMap;

void warmupEndMessage(Generator* gen, StatesMap* states, int i) {
    uint16_t foundIndex = (*states)[gen->a];
    
    std::cout << "\nDuped Number: " << gen->a;
    std::cout << "\tDuped Index: " << i;
    std::cout << "\tWarmup: " << foundIndex;
    std::cout << "\tCycle Length: " << i - foundIndex;
}

int main() {
#pragma region Init
    // Edit Generator.h to mess with params
    
    int iterations = 1000000;

    StatesMap xorStates;
    xorStates.clear();
    Xorshift xorShift;
    xorShift.init();

    StatesMap lfgStates;
    lfgStates.clear();
    LFG lfg;
    lfg.init();

#pragma endregion

#pragma region XOR Shift
    std::cout << "[Xorshift]\n";
    xorShift.print();

    for (int i = 0; i < iterations; i++) {
        if (xorStates.contains(xorShift.a)) {
            warmupEndMessage(&xorShift, &xorStates, i);
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
            warmupEndMessage(&lfg, &lfgStates, i);
            break;
        }

        lfgStates.insert({ lfg.a, i });

        lfg.shift();
        lfg.print();  
    }
#pragma endregion

    return 0;
}
