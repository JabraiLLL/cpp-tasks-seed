#include "base85ed.h"
#include <array>
#include <stdexcept>
#include <algorithm>

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
    
    result.reserve((bytes.size() + 3) / 4 * 5);
    
    size_t i = 0;
    while (i < bytes.size()) {
        uint32_t val = 0;
        size_t chunkSize = 0;
        
        for (int j = 0; j < 4; ++j) {
            val <<= 8;
            if (i < bytes.size()) {
                val |= bytes[i++];
                chunkSize++;
            }
        }
        
        if (chunkSize == 0) break;
        
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
    if (data.empty()) return {};
    
    std::vector<uint8_t> filtered;
    filtered.reserve(data.size());
    
    for (uint8_t c : data) {
        if (isWhitespace(c)) continue;
        if (DECODE_TABLE[c] == 255) {
            throw std::invalid_argument("Invalid Base85 character");
        }
        filtered.push_back(c);
    }
    
    if (filtered.empty()) return {};
    
    if (filtered.size() % 5 != 0) {
        throw std::invalid_argument("Invalid Base85 length");
    }
    
    std::vector<uint8_t> result;
    result.reserve((filtered.size() + 4) / 5 * 4);
    
    size_t i = 0;
    while (i < filtered.size()) {
        uint32_t val = 0;
        
        for (int j = 0; j < 5; ++j) {
            if (i < filtered.size()) {
                val = val * 85 + DECODE_TABLE[filtered[i++]];
            } else {
                val = val * 85 + 84;
            }
        }
        
        if (val > 0xFFFFFFFF) {
            throw std::invalid_argument("Value overflow");
        }
        
        uint8_t decoded[4];
        for (int j = 3; j >= 0; --j) {
            decoded[j] = val & 0xFF;
            val >>= 8;
        }
        
        result.push_back(decoded[0]);
        result.push_back(decoded[1]);
        result.push_back(decoded[2]);
        result.push_back(decoded[3]);
    }
    
    while (!result.empty() && result.back() == 0 && (result.size() % 4 != 0 || result.size() > 0)) {
        bool isPadding = true;
        for (size_t j = result.size() - 1; j >= result.size() - 4 && j < result.size(); --j) {
            if (result[j] != 0) {
                isPadding = false;
                break;
            }
        }
        if (isPadding && result.size() >= 4) {
            result.erase(result.end() - 4, result.end());
        } else {
            break;
        }
    }
    
    return result;
}

} // namespace base85