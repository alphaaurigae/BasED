#ifndef BASE_DEC_ENC_H
#define BASE_DEC_ENC_H


#include <stdexcept>
#include <ranges>
#include <algorithm>
#include <array>
#include <string_view>
#include <string>
#include <ranges>
#include <stdexcept>
#include <vector>

#include <gmp.h>

#include "base_alphabet.h"
#include "base_default_decode_encode.h"
#include "base32_decode_encode.h"
#include "base64_decode_encode.h"
#include "base85_decode_encode.h"
#include "base91_decode_encode.h"

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
CREATE_BASE_LOOKUP_TABLE(91)


inline std::string base_encode(const std::string& data, const std::string_view& alphabet, const std::array<int, 256>& lookup_table) {

    if (alphabet == BASE64_ALPHABET) {
        return encode_base64(data, alphabet);

    } else if (alphabet == BASE32_ALPHABET) {
        return encode_base32(data, alphabet);

    } else if (alphabet == BASE85_ALPHABET) {
        return encode_base85(data, alphabet);

    } else if (alphabet == BASE91_ALPHABET) {
        return encode_base91(data, alphabet);
    }
    return base_encode_impl(data, alphabet, lookup_table);
}

inline std::string base_decode(const std::string& encoded, const std::string_view& alphabet, const std::array<int, 256>& lookup_table) {

    if (alphabet == BASE64_ALPHABET) {
        return decode_base64(encoded, alphabet, lookup_table);

    } else if (alphabet == BASE32_ALPHABET) {
        return decode_base32(encoded, alphabet, lookup_table);

    } else if (alphabet == BASE85_ALPHABET) {
        return decode_base85(encoded, alphabet, lookup_table);

    } else if (alphabet == BASE91_ALPHABET) {
        return decode_base91(encoded, alphabet, lookup_table);
    }
    return base_decode_impl(encoded, alphabet, lookup_table);
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
DEFINE_BASE_FUNCTIONS(base91, BASE91_ALPHABET, BASE91_LOOKUP_TABLE)


#endif

