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
        
        // Для последнего неполного блока: добавляем только нужные символы
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
        
        // Дополняем до 5 символов кодом '~' (84) если блок неполный
        for (int j = blockLen; j < 5; ++j) {
            val = val * 85 + 84;
        }
        
        if (val > 0xFFFFFFFF) {
            throw std::invalid_argument("Value overflow");
        }
        
        // Извлекаем 4 байта
        uint8_t decoded[4];
        decoded[0] = (val >> 24) & 0xFF;
        decoded[1] = (val >> 16) & 0xFF;
        decoded[2] = (val >> 8) & 0xFF;
        decoded[3] = val & 0xFF;
        
        // Добавляем только нужное количество байт для последнего блока
        if (blockLen < 5) {
            result.insert(result.end(), decoded, decoded + blockLen - 1);
        } else {
            result.insert(result.end(), decoded, decoded + 4);
        }
    }
    
    return result;
}
