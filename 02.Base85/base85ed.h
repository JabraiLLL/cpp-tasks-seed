#ifndef BASE85ED_H
#define BASE85ED_H

#include <vector>
#include <cstdint>
#include <string>

namespace base85 {

std::vector<uint8_t> encode(const std::vector<uint8_t>& bytes);
std::vector<uint8_t> decode(const std::vector<uint8_t>& data);

inline std::string encodeToString(const std::string& str) {
    std::vector<uint8_t> bytes(str.begin(), str.end());
    auto encoded = encode(bytes);
    return std::string(encoded.begin(), encoded.end());
}

inline std::string decodeToString(const std::vector<uint8_t>& data) {
    auto decoded = decode(data);
    return std::string(decoded.begin(), decoded.end());
}

inline std::string decodeToString(const std::string& str) {
    std::vector<uint8_t> bytes(str.begin(), str.end());
    return decodeToString(bytes);
}

}

#endif // BASE85ED_H