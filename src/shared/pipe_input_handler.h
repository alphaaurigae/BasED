#ifndef INPUT_PIPE_HANDLER_H
#define INPUT_PIPE_HANDLER_H

#include "menu_generic.h"  // AppSettings struct

#include <iostream>
#include <string>

inline void handle_pipe_input(AppSettings& settings) {
    if (settings.pipe_input) {
        std::getline(std::cin, settings.input);
        if (settings.input.empty()) {
            std::cerr << "Error: No input received from pipe.\n";
            return;
        }
    }
}

#endif