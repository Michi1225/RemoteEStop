#include "codec.h"

inline uint16_t F(uint16_t r, uint16_t k)
{
    r += k;                         // mix key
    r ^= (r << 5) | (r >> 11);      // rotate-left 5
    r ^= (r >> 3);                  // extra diffusion
    return r;
}

namespace codec {
    uint32_t encode32(uint32_t x) {


        uint16_t L = (x >> 16) & 0xFFFF;
        uint16_t R = x & 0xFFFF;

        for (size_t r = 0; r < ROUNDS; ++r) {
            
            uint16_t f = F(R, KEYS[r]);
            uint16_t temp = L;
            L = R;
            R = temp ^ f;
        }

        return ((static_cast<uint32_t>(L) << 16) | R) & 0xFFFFFFFF;
    }
    uint32_t decode32(uint32_t x)
    {
        uint16_t L = (x >> 16) & 0xFFFF;
        uint16_t R = x & 0xFFFF;

        for (int r = ROUNDS - 1; r >= 0; --r) {
        uint16_t f = F(L, KEYS[r]);
        uint16_t tmp = R;
        R = L;
        L = tmp ^ f;
        }

        return (uint32_t(L) << 16) | R;
    }

} // namespace codec