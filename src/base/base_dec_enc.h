#ifndef BASE_DEC_ENC_H
#define BASE_DEC_ENC_H

#include <stdexcept>
#include <ranges>
#include <algorithm>
#include <array>
#include <ranges>
#include <stdexcept>
#include <vector>

#include <gmp.h>

constexpr std::string_view BASE16_ALPHABET = "0123456789ABCDEF";
constexpr std::string_view BASE32_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
constexpr std::string_view BASE58_ALPHABET = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

constexpr std::string_view BASE62_ALPHABET = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
constexpr std::string_view BASE64_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

constexpr std::string_view BASE85_ALPHABET = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstu";

constexpr std::string_view BASE91_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!#$%&()*+,./:;<=>?@[]^_`{|}~\"";


constexpr auto CREATE_LOOKUP_TABLE(const std::string_view alphabet) {
    std::array<int, 256> lookup_table{};
    lookup_table.fill(-1);

    for (size_t i = 0; i < alphabet.size(); ++i) {
        lookup_table[static_cast<unsigned char>(alphabet[i])] = i;
    }
    return lookup_table;
}

#define CREATE_BASE_LOOKUP_TABLE(base) \
    constexpr auto BASE ## base ## _LOOKUP_TABLE = CREATE_LOOKUP_TABLE(BASE ## base ## _ALPHABET);

CREATE_BASE_LOOKUP_TABLE(16)
CREATE_BASE_LOOKUP_TABLE(32)
CREATE_BASE_LOOKUP_TABLE(58)
CREATE_BASE_LOOKUP_TABLE(62)
CREATE_BASE_LOOKUP_TABLE(64)
CREATE_BASE_LOOKUP_TABLE(85)

std::string base_encode(const std::string& data, const std::string_view& alphabet, const std::array<int, 256>& lookup_table) {

    if (alphabet == BASE64_ALPHABET) {

        std::string result;
        int value = 0;
        int bits = 0;

        for (unsigned char byte : data) {
            value = (value << 8) + byte;
            bits += 8;

            while (bits >= 6) {
                result.push_back(alphabet[(value >> (bits - 6)) & 0x3F]);
                bits -= 6;
            }
        }

        if (bits > 0) {
            result.push_back(alphabet[(value << (6 - bits)) & 0x3F]);
        }

        while (result.size() % 4 != 0) {
            result.push_back('=');
        }

        return result;
    } else if (alphabet == BASE32_ALPHABET) {
    std::string result;
    int value = 0;
    int bits = 0;

    for (unsigned char byte : data) {
        value = (value << 8) + byte;
        bits += 8;

        while (bits >= 5) {
            result.push_back(BASE32_ALPHABET[(value >> (bits - 5)) & 0x1F]);
            bits -= 5;
        }
    }

    if (bits > 0) {
        result.push_back(BASE32_ALPHABET[(value << (5 - bits)) & 0x1F]);
    }

    while (result.size() % 8 != 0) {
        result.push_back('=');
    }

    return result;

} else if (alphabet == BASE85_ALPHABET) {
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
            base85_chars[j] = BASE85_ALPHABET[value % 85];
            value /= 85;
        }

        for (int j = 0; j < count + 1; ++j) {
            result.push_back(base85_chars[j]);
        }
    }

    return result;
}

    mpz_t value;
    mpz_init(value);
    mpz_set_ui(value, 0);

    for (unsigned char byte : data) {
        mpz_mul_ui(value, value, 256);
        mpz_add_ui(value, value, byte);
    }

    std::string result;
    while (mpz_cmp_ui(value, 0) > 0) {
        mpz_t remainder;
        mpz_init(remainder);
        mpz_fdiv_r_ui(remainder, value, alphabet.size());
        int remainder_int = mpz_get_ui(remainder);
        result.push_back(alphabet[remainder_int]);
        mpz_fdiv_q_ui(value, value, alphabet.size());
        mpz_clear(remainder);
    }

    for (unsigned char byte : data) {
        if (byte != 0) break;
        result.push_back(alphabet[0]);
    }

    std::ranges::reverse(result);
    mpz_clear(value);

    return result;
}

std::string base_decode(const std::string& encoded, const std::string_view& alphabet, const std::array<int, 256>& lookup_table) {
    if (alphabet == BASE64_ALPHABET) {

        std::string result;
        int value = 0;
        int bits = 0;

        for (char c : encoded) {
            if (c == '=') break;

            int index = lookup_table[static_cast<unsigned char>(c)];
            if (index == -1) {
                throw std::invalid_argument("Invalid character in Base64 string.");
            }

            value = (value << 6) + index;
            bits += 6;

            if (bits >= 8) {
                result.push_back((value >> (bits - 8)) & 0xFF);
                bits -= 8;
            }
        }

        return result;
    } else if (alphabet == BASE32_ALPHABET) {
    std::string result;
    int value = 0;
    int bits = 0;

    for (char c : encoded) {
        if (c == '=') break;

        int index = BASE32_LOOKUP_TABLE[static_cast<unsigned char>(c)];
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
} else if (alphabet == BASE85_ALPHABET) {
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
                int index = BASE85_LOOKUP_TABLE[static_cast<unsigned char>(c)];
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

    mpz_t value;
    mpz_init(value);
    mpz_set_ui(value, 0);

    for (char c : encoded) {
        int index = lookup_table[static_cast<unsigned char>(c)];
        if (index == -1) {
            throw std::invalid_argument("Invalid character in Base string.");
        }
        mpz_mul_ui(value, value, alphabet.size());
        mpz_add_ui(value, value, index);
    }

    int num_leading_zeros = std::ranges::count(
        encoded | std::views::take_while([&alphabet](char c) { return c == alphabet[0]; }),
        alphabet[0]
    );

    std::string result;
    while (mpz_cmp_ui(value, 0) > 0) {
        mpz_t remainder;
        mpz_init(remainder);
        mpz_fdiv_r_ui(remainder, value, 256);
        unsigned char byte = mpz_get_ui(remainder);
        result.insert(result.begin(), byte);
        mpz_fdiv_q_ui(value, value, 256);
        mpz_clear(remainder);
    }

    result.insert(result.begin(), num_leading_zeros, 0);

    mpz_clear(value);
    return result;
}



#define DEFINE_BASE_FUNCTIONS(name, alphabet, lookup_table) \
std::string name##_encode(const std::string& data) { \
    return base_encode(data, alphabet, lookup_table); \
} \
std::string name##_decode(const std::string& encoded) { \
    return base_decode(encoded, alphabet, lookup_table); \
}



DEFINE_BASE_FUNCTIONS(base16, BASE16_ALPHABET, BASE16_LOOKUP_TABLE)
DEFINE_BASE_FUNCTIONS(base32, BASE32_ALPHABET, BASE32_LOOKUP_TABLE)
DEFINE_BASE_FUNCTIONS(base58, BASE58_ALPHABET, BASE58_LOOKUP_TABLE)
DEFINE_BASE_FUNCTIONS(base62, BASE62_ALPHABET, BASE62_LOOKUP_TABLE)
DEFINE_BASE_FUNCTIONS(base64, BASE64_ALPHABET, BASE64_LOOKUP_TABLE)
DEFINE_BASE_FUNCTIONS(base85, BASE85_ALPHABET, BASE85_LOOKUP_TABLE)

#endif

