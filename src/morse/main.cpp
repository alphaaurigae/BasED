#include "input_generic.h"
#include "input_process.h"  // !important - main template for void handle_entered_input "validate_input"
#include "menu_generic.h"  // !important - struct for handling void process_arguments (cli11 menu) main shared parts
#include "input_validation.h"  // use input to call encode / decode functionalities of main
#include "argument_parser.h"
#include "argument_validation.h"
#include "input_pipe.h"
#include "man_main.h"
#include "man_cout.h"

#include <functional>
#include <iostream>
#include <string>

#include <CLI/CLI.hpp>

#include "morse_dec_enc.h"


void exec_man() {
    std::cout << "Samples Morse:\n\n";
    std::cout << "bin/morse -e -m -i 'good morning!'\n";
    std::cout << "bin/morse -d -m -i '-... ..- -.-- -- . .- -.-. --- ..-. ..-. . .'\n\n";
}


void handle_entered_input(const std::string& input, bool encode, bool decode, bool morse_standard) { // var

    validate_input(input, encode, decode);  // input_validation.h

    std::function<std::string(const std::string&)> encode_func;
    
    // var
    if (morse_standard) {
        encode_func = (encode) ? morse_standard_encode : morse_standard_decode;
    } else {
        std::cout << "Unsupported operation." << std::endl;
        return;
    }

    process_input(input, encode, encode_func); // input_process.h
}


void process_arguments(CLI::App& app, int argc, char* argv[]) {

    // menu_generic.h
    AppSettings settings;
    settings.setup_app(app);

    // var
    bool morse_standard = false;
    auto morse_standard_opt = app.add_flag("-m, --morse_standard", morse_standard, "Morse");
    morse_standard_opt->excludes(settings.man_opt);

    parse_arguments(app, argc, argv);  // argument_parser.h
    cout_man(settings.show_man);  // man_cout.h
    validate_arguments(settings);  // argument_validation.h

    // var
    if (!morse_standard) {
        std::cout << "Error: Morse encoding/decoding requires the --morse_standard flag.\n";
        return;
    }

    handle_pipe_input(settings);  // input_pipe.h

    if (!settings.input.empty()) {
        handle_entered_input(settings.input, settings.encode, settings.decode, morse_standard); // var
    }
}


int main(int argc, char* argv[]) {
    CLI::App app{"Morse Encoder/Decoder Program"};
    process_arguments(app, argc, argv);
    return 0;
}
