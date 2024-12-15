#ifndef ARGUMENT_VALIDATION_H
#define ARGUMENT_VALIDATION_H

#include "menu_generic.h"

#include <iostream>


inline void validate_arguments(const AppSettings& settings) {
    if ((settings.input.empty() && !settings.pipe_input) || !(settings.encode || settings.decode)) {
        std::cout << "Missing required arguments:\n";
        if (settings.input.empty() && !settings.pipe_input) {
            std::cout << "  -i [input string] or -p [piped input] is required\n";
        }
        if (!(settings.encode || settings.decode)) {
            std::cout << "  -e (encode) or -d (decode) is required\n";
        }
        std::cout << "\nUse --help for more details.\n";
    }
}

#endif