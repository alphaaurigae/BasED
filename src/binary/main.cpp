#include "input_generic.h"
#include "process_input.h"  // !important - main template for void handle_entered_input "validate_input"
#include "menu_generic.h"  // !important - struct for handling void process_arguments (cli11 menu) main shared parts
#include "input_validation.h"  // use input to call encode / decode functionalities of main
#include "argument_parser.h"
#include "argument_validation.h"
#include "pipe_input_handler.h"
#include "man_main.h"
#include "man_cout.h"

#include <functional>
#include <iostream>
#include <string>

#include <CLI/CLI.hpp>

#include "binary_dec_enc.h"


void exec_man() {
    std::cout << "Samples Binary:\n\n";
    std::cout << "bin/binary -e -b -i 'bin'\n";
    std::cout << "bin/binary -d -b -i '11110000100111111001000110111101'\n\n";
}


void handle_entered_input(const std::string& input, bool encode, bool decode, bool binary) { // var

    validate_input(input, encode, decode);  // input_validation.h

    std::function<std::string(const std::string&)> encode_func;

    // var
    if (binary) {
        encode_func = (encode) ? binary_encode : binary_decode;
    } else {
        std::cout <<  "Unsupported operation." << std::endl;
        return;
    }

    process_input(input, encode, encode_func);  // process_input.h
}


void process_arguments(CLI::App& app, int argc, char* argv[]) {

    // menu_generic.h
    AppSettings settings;
    settings.setup_app(app);

    // var
    bool binary = false;
    auto binary_opt = app.add_flag("-b, --binary", binary, "Use binary encoding/decoding");
    binary_opt->excludes(settings.man_opt);
    
    parse_arguments(app, argc, argv);  // argument_parser.h
    cout_man(settings.show_man);  // cout_man.h"
    validate_arguments(settings);  // argument_validation.h

    // var
    if (!binary) {
        std::cout <<  "Error: Binary encoding/decoding requires the --binary flag.\n";
        return;
    }

    handle_pipe_input(settings);  // pipe_input_handler.h

    if (!settings.input.empty()) {
        handle_entered_input(settings.input, settings.encode, settings.decode, binary); // var
    }

}


int main(int argc, char* argv[]) {
    CLI::App app{"Binary Encoder/Decoder Program"};
    process_arguments(app, argc, argv);
    return 0;
}
