#include "base85ed.h"
#include <stdexcept>
#include <cstring>

namespace base85 {

static const char b85_alphabet[] =
    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";

static int b85_value[256];
static bool b85_table_initialized = false;

static void init_b85_table() {
    if (b85_table_initialized) return;
    for (int i = 0; i < 256; i++) {
        b85_value[i] = -1;
    }
    for (int i = 0; i < 85; i++) {
        b85_value[(unsigned char)b85_alphabet[i]] = i;
    }
    b85_table_initialized = true;
}

std::vector<uint8_t> encode(const std::vector<uint8_t>& bytes) {
    std::vector<uint8_t> result;
    size_t i = 0;
    size_t n = bytes.size();
    
    while (i < n) {
        uint32_t value = 0;
        for (int j = 0; j < 4; j++) {
            value <<= 8;
            if (i + j < n) {
                value |= bytes[i + j];
            }
        }
        
        char encoded[5];
        for (int j = 4; j >= 0; j--) {
            encoded[j] = b85_alphabet[value % 85];
            value /= 85;
        }
        
        size_t block_size = n - i;
        if (block_size >= 4) {
            result.insert(result.end(), encoded, encoded + 5);
        } else {
            result.insert(result.end(), encoded, encoded + block_size + 1);
        }
        i += 4;
    }
    return result;
}

std::vector<uint8_t> decode(const std::vector<uint8_t>& b85str) {
    init_b85_table();
    std::vector<uint8_t> result;
    size_t i = 0;
    size_t n = b85str.size();
    
    if (n == 0) return result;
    
    while (i < n) {
        size_t remaining = n - i;
        size_t block_size = (remaining >= 5) ? 5 : remaining;
        
        uint32_t value = 0;
        for (size_t j = 0; j < 5; j++) {
            if (j < block_size) {
                int v = b85_value[b85str[i + j]];
                if (v == -1) {
                    throw std::runtime_error("Invalid Base85 character");
                }
                value = value * 85 + v;
            } else {
                value = value * 85 + 84;
            }
        }
        
        int bytes_to_output = block_size - 1;
        for (int j = 0; j < bytes_to_output; j++) {
            int shift = 24 - j * 8;
            result.push_back((value >> shift) & 0xFF);
        }
        i += block_size;
    }
    return result;
}

} // namespace base85
