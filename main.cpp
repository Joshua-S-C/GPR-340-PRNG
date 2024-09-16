#include <iostream>
#include <stdint.h>

// Just taken from Wikipedia
struct xorshift32_state {
    uint32_t a;
};

/* The state must be initialized to non-zero */
uint32_t xorshift32(struct xorshift32_state *state)
{
    /* Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs" */
    uint32_t x = state->a;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return state->a = x;
}

int main() {
    xorshift32_state state1;
    state1.a = 0x12345678;

    std::cout << state1.a << std::endl << xorshift32(&state1);

    return 0;
}
