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

// ---------------------------------
// Main function
// ---------------------------------
// int main() {
//     // Fixed key (16-bit round keys)
//     std::vector<uint16_t> key = {0x1234, 0xBEEF, 0xCAFE, 0x0BAD, 0xFACE, 0xDEAD};

//     // Sampling parameters
//     const uint32_t SAMPLES = 200000; // Increase if your machine allows
//     const uint32_t STEP = (1ULL << 32) / SAMPLES;

//     std::vector<uint32_t> xs;
//     std::vector<uint32_t> ys;

//     uint32_t x = 0;
//     for (uint32_t i = 0; i < SAMPLES; ++i) {
//         uint32_t y = feistel32(x, key);
//         xs.push_back(x);
//         ys.push_back(y);
//         x = (x + STEP) & 0xFFFFFFFF;
//     }

//     // Output data to a file for plotting
//     std::ofstream outFile("feistel_output.csv");
//     if (outFile.is_open()) {
//         outFile << "x,y\n";
//         for (size_t i = 0; i < xs.size(); ++i) {
//             outFile << xs[i] << "," << ys[i] << "\n";
//         }
//         outFile.close();
//         std::cout << "Data written to feistel_output.csv. Use a plotting tool to visualize it.\n";
//     } else {
//         std::cerr << "Failed to open output file.\n";
//     }

//     return 0;
// }