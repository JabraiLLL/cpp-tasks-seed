#include "base85ed.h"
#include <array>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstdint>

namespace base85 {

static constexpr char ALPHABET[] =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "!#$%&()*+-;<=>?@^_`{|}~";

static constexpr std::array<uint8_t, 256> buildDecodeTable() {
    std::array<uint8_t, 256> table{};
    for (auto& v : table) v = 255;
    for (uint8_t i = 0; i < 85; ++i) {
        table[static_cast<uint8_t>(ALPHABET[i])] = i;
    }
    return table;
}

static constexpr auto DECODE_TABLE = buildDecodeTable();

static inline bool isWhitespace(uint8_t c) {
    return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

std::vector<uint8_t> encode(const std::vector<uint8_t>& bytes) {
    std::vector<uint8_t> result;
    if (bytes.empty()) return result;
    
    size_t i = 0;
    while (i < bytes.size()) {
        uint32_t val = 0;
        int chunkSize = 0;
        
        for (int j = 0; j < 4; ++j) {
            val <<= 8;
            if (i < bytes.size()) {
                val |= bytes[i++];
                chunkSize++;
            }
        }
        
        uint8_t block[5];
        for (int j = 4; j >= 0; --j) {
            block[j] = ALPHABET[val % 85];
            val /= 85;
        }
        
        if (chunkSize < 4) {
            result.insert(result.end(), block, block + chunkSize + 1);
        } else {
            result.insert(result.end(), block, block + 5);
        }
    }
    
    return result;
}

std::vector<uint8_t> decode(const std::vector<uint8_t>& data) {
    if (data.empty()) return {};
    
    std::vector<uint8_t> filtered;
    for (uint8_t c : data) {
        if (isWhitespace(c)) continue;
        if (DECODE_TABLE[c] == 255) {
            throw std::invalid_argument("Invalid Base85 character");
        }
        filtered.push_back(c);
    }
    
    if (filtered.empty()) return {};
    
    std::vector<uint8_t> result;
    size_t i = 0;
    
    while (i < filtered.size()) {
        int remaining = filtered.size() - i;
        int blockLen = (remaining >= 5) ? 5 : remaining;
        
        uint32_t val = 0;
        for (int j = 0; j < blockLen; ++j) {
            val = val * 85 + DECODE_TABLE[filtered[i++]];
        }
        
        for (int j = blockLen; j < 5; ++j) {
            val = val * 85 + 84;
        }
        
        uint8_t decoded[4];
        decoded[0] = (val >> 24) & 0xFF;
        decoded[1] = (val >> 16) & 0xFF;
        decoded[2] = (val >> 8) & 0xFF;
        decoded[3] = val & 0xFF;
        
        if (blockLen < 5) {
            result.insert(result.end(), decoded, decoded + blockLen - 1);
        } else {
            result.insert(result.end(), decoded, decoded + 4);
        }
    }
    
    return result;
}

} // namespace base85
