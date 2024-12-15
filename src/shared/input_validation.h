#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H

#include <string>
#include <iostream>


// use input to call endode / decode functionalities of main
inline void validate_input(const std::string& input, bool encode, bool decode) {
    if (input.empty()) {
        std::cout << "-i argument defined but no input given" << std::endl;
        std::exit(1);
    }
    if (encode && decode) {
        std::cout << "Invalid arguments. Cannot use both --encode and --decode options together." << std::endl;
        std::exit(1);
    }
}

#endif