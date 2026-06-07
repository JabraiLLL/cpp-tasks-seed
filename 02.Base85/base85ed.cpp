#include "base85ed.h"
#include <array>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstdint>

namespace base85 {

static constexpr char ALPHABET[] = 
    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";

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
    size_t i = 0;
    while (i < bytes.size()) {
        uint32_t val = 0;
        int cnt = 0;
        for (int j = 0; j < 4 && i < bytes.size(); ++j, ++i) {
            val = (val << 8) | bytes[i];
            ++cnt;
        }
        if (cnt == 0) break;
        
        for (int j = cnt; j < 4; ++j) val <<= 8;
        
        uint8_t block[5];
        for (int j = 4; j >= 0; --j) {
            block[j] = ALPHABET[val % 85];
            val /= 85;
        }
        
        result.insert(result.end(), block, block + 5);
    }
    return result;
}

std::vector<uint8_t> decode(const std::vector<uint8_t>& data) {
    std::vector<uint8_t> filtered;
    for (uint8_t c : data) {
        if (isWhitespace(c)) continue;
        if (DECODE_TABLE[c] == 255) {
            throw std::invalid_argument("Invalid Base85 character");
        }
        filtered.push_back(c);
    }
    
    if (filtered.empty()) return {};
    
    if (filtered.size() % 5 != 0) {
    }
    
    std::vector<uint8_t> result;
    size_t i = 0;
    while (i < filtered.size()) {
        uint32_t val = 0;
        int cnt = 0;
        for (int j = 0; j < 5 && i < filtered.size(); ++j, ++i) {
            val = val * 85 + DECODE_TABLE[filtered[i]];
            ++cnt;
        }
        
        for (int j = cnt; j < 5; ++j) val = val * 85 + 84;
        
        uint8_t decoded[4];
        decoded[0] = (val >> 24) & 0xFF;
        decoded[1] = (val >> 16) & 0xFF;
        decoded[2] = (val >> 8) & 0xFF;
        decoded[3] = val & 0xFF;
        
        int bytesToAdd = 4;
        if (cnt < 5 && cnt > 0) {
            bytesToAdd = cnt - 1;
        }
        result.insert(result.end(), decoded, decoded + bytesToAdd);
    }
    return result;
}

} // namespace base85
