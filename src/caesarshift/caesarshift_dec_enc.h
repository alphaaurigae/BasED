#ifndef CAESARSHIFT_DEC_ENC_H
#define CAESARSHIFT_DEC_ENC_H

#include <cctype>
#include <string>
#include <iostream>


template <typename T>
std::string caesar_shift(const std::string& input, int shift, const std::string& mode, T operation) {
    std::string result = "";
    for (char c : input) {
        if (mode == "alpha" && std::isalpha(c)) {
            if (std::isupper(c)) {
                result += static_cast<char>((c - 'A' + operation(shift)) % 26 + 'A');
            } else {
                result += static_cast<char>((c - 'a' + operation(shift)) % 26 + 'a');
            }
        } else if (mode == "digit" && std::isdigit(c)) {
            result += static_cast<char>((c - '0' + operation(shift)) % 10 + '0');
        } else if (mode == "alnum") {
            if (std::isalpha(c)) {
                if (std::isupper(c)) {
                    result += static_cast<char>((c - 'A' + operation(shift)) % 26 + 'A');
                } else {
                    result += static_cast<char>((c - 'a' + operation(shift)) % 26 + 'a');
                }
            } else if (std::isdigit(c)) {
                result += static_cast<char>((c - '0' + operation(shift)) % 10 + '0');
            } else {
                result += c;
            }
        } else {
            result += c;
        }
    }
    return result;
}


int encode_operation(int shift) {
    return shift;
}

int decode_operation(int shift) {
    return -shift;
}

std::string caesar_shift_encode(const std::string& input, int shift, const std::string& mode) {
    return caesar_shift(input, shift, mode, encode_operation);
}

std::string caesar_shift_decode(const std::string& input, int shift, const std::string& mode) {
    return caesar_shift(input, shift, mode, decode_operation);
}


#endif

