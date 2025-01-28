#ifndef BASE91_DECODE_ENCODE_H
#define BASE91_DECODE_ENCODE_H

#include <string>
#include <string_view>
#include <stdexcept>
#include <array>

inline std::string encode_base91(const std::string& data, const std::string_view& alphabet) {
    std::string result;
    uint32_t b = 0;
    int n = 0;

    constexpr uint32_t MASK_13BIT = 8191;
    constexpr uint32_t MASK_14BIT = 16383;

    for (unsigned char byte : data) {
        b |= byte << n;
        n += 8;
        if (n > 13) {
            uint32_t v = b & MASK_13BIT;

            if (v > 88) {
                b >>= 13;
                n -= 13;
            } else {
                v = b & MASK_14BIT;
                b >>= 14;
                n -= 14;
            }
            result.push_back(alphabet[v % 91]);
            result.push_back(alphabet[v / 91]);
        }
    }
    if (n) {
        result.push_back(alphabet[b % 91]);
        if (n > 7 || b > 90) {
            result.push_back(alphabet[b / 91]);
        }
    }
    return result;
}

inline std::string decode_base91(const std::string& encoded, const std::string_view& alphabet, const std::array<int, 256>& lookup_table) {
    std::string result;
    uint32_t b = 0;
    int n = 0;
    int v = -1;

    for (char c : encoded) {
        if (lookup_table[static_cast<unsigned char>(c)] == -1) {
            throw std::invalid_argument("Invalid character in Base91 string.");
        }
        if (v < 0) {
            v = lookup_table[static_cast<unsigned char>(c)];
        } else {
            v += lookup_table[static_cast<unsigned char>(c)] * 91;
            b |= v << n;
            n += (v & 8191) > 88 ? 13 : 14;
            do {
                result.push_back(static_cast<char>(b));
                b >>= 8;
                n -= 8;
            } while (n > 7);
            v = -1;
        }
    }

    if (v >= 0) {
        result.push_back(static_cast<char>((b | v << n)));
    }

    return result;
}

#endif