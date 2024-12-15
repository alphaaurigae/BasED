#ifndef HEX_DEC_ENC_H
#define HEX_DEC_ENC_H

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>

std::string hex_encode(const std::string& plaintext) {
    std::ostringstream ss;
    for (unsigned char c : plaintext) {
        ss << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(c);
    }
    return ss.str();
}

std::string hex_decode(const std::string& ciphertext) {
    if (ciphertext.length() % 2 != 0) {
        throw std::invalid_argument("Hex string has an odd number of characters");
    }

    std::string plaintext;
    for (std::size_t i = 0; i < ciphertext.length(); i += 2) {
        unsigned int byte;
        std::stringstream ss;
        ss << std::hex << ciphertext.substr(i, 2);
        ss >> byte;
        plaintext += static_cast<char>(byte);
    }
    return plaintext;
}

#endif