#ifndef BASE85_DECODE_ENCODE_H
#define BASE85_DECODE_ENCODE_H


#include <string>
#include <string_view>
#include <stdexcept>
#include <array>

#include "base_dec_enc.h"


inline std::string encode_base85(const std::string& data, const std::string_view& alphabet) {

    std::string result;
    size_t i = 0;
    size_t len = data.size();

    while (i < len) {
        uint32_t value = 0;
        int count = 0;

        for (int j = 0; j < 4; ++j) {
            if (i < len) {
                value = (value << 8) | static_cast<unsigned char>(data[i++]);
                count++;
            } else {
                value <<= 8;
            }
        }

        if (value == 0 && count == 4) {
            result.push_back('z');
            continue;
        }

        char base85_chars[5];
        for (int j = 4; j >= 0; --j) {
            base85_chars[j] = alphabet[value % 85];
            value /= 85;
        }

        for (int j = 0; j < count + 1; ++j) {
            result.push_back(base85_chars[j]);
        }
    }

    return result;
}

inline std::string decode_base85(const std::string& encoded, const std::string_view& alphabet, const std::array<int, 256>& lookup_table) {

    std::string result;
    size_t i = 0;
    size_t len = encoded.size();

    while (i < len) {
        if (encoded[i] == 'z') {
            result.append(4, 0);
            ++i;
            continue;
        }

        if (encoded[i] == 'y') {
            result.append(4, ' ');
            ++i;
            continue;
        }

        uint32_t value = 0;
        int count = 0;

        for (int j = 0; j < 5; ++j) {
            if (i >= len) {
                value = value * 85 + 84;
            } else {
                char c = encoded[i++];
                if (c == ' ' || c == '\n' || c == '\r') {
                    --j;
                    continue;
                }
                int index = lookup_table[static_cast<unsigned char>(c)];
                if (index == -1) {
                    throw std::invalid_argument("Invalid character in Base85 string.");
                }
                value = value * 85 + index;
                ++count;
            }
        }

        int bytes_to_write = (count == 0) ? 0 : count - 1;
        for (int j = 0; j < bytes_to_write; ++j) {
            result.push_back(static_cast<char>((value >> (24 - j * 8)) & 0xFF));
        }
    }

    return result;
}

#endif