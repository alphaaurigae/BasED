#ifndef BINARY_DEC_ENC_H
#define BINARY_DEC_ENC_H

#include <bitset>
#include <string>


std::string binary_encode(const std::string& plaintext) {
    std::string ciphertext = "";
    for (char c : plaintext) {
        std::bitset<8> bits(c);
        ciphertext += bits.to_string();
    }
    return ciphertext;
}
std::string binary_decode(const std::string& ciphertext) {
    std::string plaintext = "";
    for (std::size_t i = 0; i < ciphertext.length(); i += 8) {
        std::bitset<8> bits(ciphertext.substr(i, 8));
        plaintext += char(bits.to_ulong());
    }
    return plaintext;
}

#endif