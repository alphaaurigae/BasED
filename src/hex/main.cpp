#include "input_generic.h"
#include "process_input.h"  // !important - main template for void handle_entered_input "validate_input"
#include "menu_generic.h"  // !important - struct for handling void process_arguments (cli11 menu) main shared parts
#include "input_validation.h"  // use input to call encode / decode functionalities of main
#include "argument_parser.h"
#include "argument_validation.h"
#include "pipe_input_handler.h"
#include "main_man.h"
#include "cout_man.h"

#include <functional>
#include <iostream>
#include <string>

#include <CLI/App.hpp>

#include "hex_dec_enc.h"


void exec_man() {
    std::cout << "Samples Base58:\n\n";
    std::cout << "bin/hex -e --hex -i 'cookie!'\n";
    std::cout << "bin/hex -d --hex -i '2420666f7274756e65'\n\n";
}


void handle_entered_input(const std::string& input, bool encode, bool decode, bool hex) { // var

    validate_input(input, encode, decode);  // input_validation.h

    std::function<std::string(const std::string&)> encode_func;
    
    // var
    if (hex) {
        encode_func = (encode) ? hex_encode : hex_decode;
    } else {
        std::cout << "Unsupported operation." << std::endl;
        return;
    }

    process_input(input, encode, encode_func); // process_input.h
}


void process_arguments(CLI::App& app, int argc, char* argv[]) {

    // menu_generic.h
    AppSettings settings;
    settings.setup_app(app);

    // var
    bool hex = false;
    auto hex_opt = app.add_flag("--hex", hex, "hex");
    hex_opt->excludes(settings.man_opt);

    parse_arguments(app, argc, argv);  // argument_parser.h
    cout_man(settings.show_man);  // cout_man.h"
    validate_arguments(settings);  // argument_validation.h

    // var
    if (!hex) {
        std::cout << "Error: hex encoding/decoding requires the --hex flag.\n";
        return;
    }

    handle_pipe_input(settings);  // pipe_input_handler.h

    if (!settings.input.empty()) {
        handle_entered_input(settings.input, settings.encode, settings.decode, hex); // var
    }
}


int main(int argc, char* argv[]) {
    CLI::App app{"Morse Encoder/Decoder Program"};
    process_arguments(app, argc, argv);
    return 0;
}

