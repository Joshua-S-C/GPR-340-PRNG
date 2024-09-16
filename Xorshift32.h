#ifndef XORSHIFT32_H
#define XORSHIFT32_H

#include <stdint.h>
#include <ctime>
#include <chrono>

class Xorshift32 {
    uint32_t a = time(nullptr);
    int min = 0, max = 100;

public:

    void init() {
        a = min + (a % (max - min + 1));
    }

    void shift() {
        uint32_t x = a;
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;

        x = min + (x % (max - min + 1));

        a = x;
    }

    void print() {
        std::cout << a;
    }

};



#endif //XORSHIFT32_H
