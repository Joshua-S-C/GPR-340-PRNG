//
// Created by joshua.sinclairchong on 9/16/2024.
//

#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdint.h>
#include <ctime>
#include <chrono>

//todo Make this an abstract class
class Generator {
protected:
    int min = 0, max = 100;
public:
    void setRange(int min, int max) {
        this->min = min;
        this->max = max;
    }

    //void loop(int iterations) {
    //    for (int i = 0; i < iterations; i++) {
    //        shift();
    //        print();
    //    }
    //}

    virtual void init() = 0;
    virtual void shift() = 0;
    virtual void print() = 0;
};


/// <summary>
/// Marsaglia
/// </summary>
class Xorshift32 : Generator {
    uint32_t a = time(nullptr);
public:
    void init() override {
        a = min + (a % (max - min + 1));
    }

    void shift() override {
        uint32_t x = a;
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;

        x = min + (x % (max - min + 1));

        a = x;
    }

    void print() override {
        std::cout << a << ", \t";
    }
};

// https://en.wikipedia.org/wiki/Lagged_Fibonacci_generator
// todo: change operator
class LFG : Generator {
    uint32_t a = time(nullptr);

public:
    enum usedOperator {
        ADD = 0,
        SUBTRACT,
        MULTIPLY,
        DIVIDE,
        MOD,
        XOR
    };

    usedOperator op = ADD;

    uint32_t j, k; // Previous 2 numbers

    /// <param name="j">Previous number</param>
    /// <param name="k">Second previous number</param>
    LFG(uint32_t j, uint32_t k) {
        this->j = j;
        this->k = k;
    }

    void init() override {
        a = min + (a % (max - min + 1));
    }

    void shift() override {
        switch (op) {
            case ADD:
                a = j + k;
                break;
            case SUBTRACT:
                a = j - k;
                break;
            case MULTIPLY:
                a = j * k;
                break;
            //todo divide by 0
            case DIVIDE:
                a = j / k;
                break;
            //todo MOD 0
            case MOD:
                a = j % k;
                break;
            case XOR:
                a = j ^ k;
                break;
            default:
                std::cout << "Achievement Unlocked: How did we get here?";
        }

        k = j;
        j = a;
    }

    void print() override {
        std::cout << a << ", \t";
    }
};

#endif //GENERATOR_H
