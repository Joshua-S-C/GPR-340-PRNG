//
// Created by joshua.sinclairchong on 9/16/2024.
//

#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdint.h>
#include <ctime>
#include <chrono>

class Generator {
protected:
    int min = 0, max = 1000;
public:
    void setRange(int min, int max) {
        this->min = min; 
        this->max = max;
    }

    virtual void init() = 0;
    virtual void shift() = 0;
    virtual void print() = 0;
};


/// <summary>
/// https://en.wikipedia.org/wiki/Xorshift
/// </summary>
class Xorshift32 : Generator {
public:
    uint32_t a;

    void init() override {
        a = time(nullptr);
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


/// <summary>
/// https://en.wikipedia.org/wiki/Lagged_Fibonacci_generator
/// </summary>
class LFG : Generator {
public:
    enum usedOperator {
        ADD = 0,
        SUBTRACT = 1,
        MULTIPLY = 2,
        DIVIDE = 3,
        MOD = 4,
        XOR = 5
    };

    usedOperator op;
    std::string opName;

    uint32_t a;
    uint32_t j; // Previous number
    uint32_t k; // Second previous number

    /// <summary>
    /// Initializes the previous two numbers (since they wouldn't exist)
    /// TODO Use the range
    /// </summary>
    void init() override {
        j = 24;
        k = 55;
        op = ADD;

        switch (op)
        {
        case LFG::ADD:
            opName = "Add";
            break;
        case LFG::SUBTRACT:
            opName = "Subtract";
            break;
        case LFG::MULTIPLY:
            opName = "Multiply";
            break;
        case LFG::DIVIDE:
            opName = "Divide";
            break;
        case LFG::MOD:
            opName = "Mod";
            break;
        case LFG::XOR:
            opName = "Xor";
            break;
        }

        a = time(nullptr);
        //a = min + (a % (max - min + 1));
    }

    void shift() override {
        switch (op) {
            case ADD:
                a = j + k;
                break;
            case SUBTRACT:
                a = j - k;
                break;
            //todo will multiply by 0 really fast
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

        //a = min + (a % (max - min + 1));

        k = j;
        j = a;
    }

    void print() override {
        std::cout << a << ", \t";
    }
};

#endif //GENERATOR_H
