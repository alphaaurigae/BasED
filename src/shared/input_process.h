#ifndef PROCESS_INPUT_H
#define PROCESS_INPUT_H

#include <iostream>
#include <string>

// main template for void handle_entered_input "validate_input" in input_validation.h for --> encode && decode to --> call encode and decode functinoalities of main
template <typename Func>
void process_input(const std::string& input, bool is_encode, Func func) {
    std::string result = func(input);
    std::cout << (is_encode ? "Encoded: " : "Decoded: ") << result << std::endl;
}

#endif