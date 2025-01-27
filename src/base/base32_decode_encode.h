#ifndef BASE32_DECODE_ENCODE_H
#define BASE32_DECODE_ENCODE_H


#include <string>
#include <string_view>
#include <stdexcept>
#include <array>

#include "base_dec_enc.h"


inline std::string encode_base32(const std::string& data, const std::string_view& alphabet) {

    std::string result;
    int value = 0;
    int bits = 0;

    for (unsigned char byte : data) {
        value = (value << 8) + byte;
        bits += 8;

        while (bits >= 5) {
            result.push_back(alphabet[(value >> (bits - 5)) & 0x1F]);
            bits -= 5;
        }
    }

    if (bits > 0) {
        result.push_back(alphabet[(value << (5 - bits)) & 0x1F]);
    }

    while (result.size() % 8 != 0) {
        result.push_back('=');
    }

    return result;
}

inline std::string decode_base32(const std::string& encoded, const std::string_view& alphabet, const std::array<int, 256>& lookup_table) {

    std::string result;
    int value = 0;
    int bits = 0;

    for (char c : encoded) {
        if (c == '=') break;

        int index = lookup_table[static_cast<unsigned char>(c)];
        if (index == -1) {
            throw std::invalid_argument("Invalid character in Base32 string.");
        }

        value = (value << 5) + index;
        bits += 5;

        if (bits >= 8) {
            result.push_back((value >> (bits - 8)) & 0xFF);
            bits -= 8;
        }
    }

    return result;
}

#endif