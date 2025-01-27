#ifndef BASE_DEFAULT_DECODE_ENCODE_H
#define BASE_DEFAULT_DECODE_ENCODE_H


#include <string>
#include <array>
#include <stdexcept>
#include <ranges>

#include <gmp.h>


inline std::string base_encode_impl(const std::string& data, const std::string_view& alphabet, const std::array<int, 256>& lookup_table) {
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

inline std::string base_decode_impl(const std::string& encoded, const std::string_view& alphabet, const std::array<int, 256>& lookup_table) {
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

#endif