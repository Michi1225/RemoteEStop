#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>
#include <fstream>




namespace codec{
    constexpr size_t ROUNDS = 4;
    constexpr uint16_t KEYS[ROUNDS] = {0x1234, 0xBEEF, 0xCAFE, 0x0BAD};

    uint32_t encode32(uint32_t x);
    uint32_t decode32(uint32_t y);
};
