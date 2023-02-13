
#include "xor_random.h"

static uint64_t state;
static const uint64_t STATE_MAGIC = 0x2545F4914F6CDD1D;

void seed(uint64_t num) {
    state = num;
}

uint32_t next_int(void) {
    uint64_t x;
    uint32_t answer;

    x = state;
    x = x ^ (x >> 12);
    x = x ^ (x << 25);
    x = x ^ (x >> 27);
    state = x;
    answer = ((x * STATE_MAGIC) >> 32);

    return answer;
}
