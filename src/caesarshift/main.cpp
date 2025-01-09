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

#include "caesarshift_dec_enc.h"


void exec_man() {
    std::cout <<"Samples Ceasarshift:\n\n";
    std::cout <<"echo 'cowsay' | bin/caesarshift -e --caesarshift 5  -p\n";
    std::cout <<"echo 'cowsay' | bin/caesarshift -e --caesarshift 5 --mode alnum -p\n";
    std::cout <<"bin/caesarshift -d --caesarshift 5 -i 'cowsay'\n";
    std::cout <<"bin/caesarshift -e --caesarshift 5 --mode alnum -i 'moo123'\n";
    std::cout <<"bin/caesarshift -e --caesarshift 5 --mode alpha -i 'mooo123'\n";
    std::cout <<"bin/caesarshift -e --caesarshift 5 --mode digit -i 'mooooo123'\n";
}


void handle_entered_input(const std::string& input, bool encode, bool decode, bool caesarshift, const std::string& mode) { // var

    validate_input(input, encode, decode);  // input_validation.h

    std::function<std::string(const std::string&)> encode_func;
    
    // var
    if (caesarshift != 0) {
        encode_func = (encode) ? std::bind(caesar_shift_encode, std::placeholders::_1, caesarshift, mode) : std::bind(caesar_shift_decode, std::placeholders::_1, caesarshift, mode);
    }

    else {
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
    int caesarshift = 0;
    std::string mode = "alnum"; // ‘[:alnum:]’ ‘[:alpha:]’ ‘[:digit:]’

    auto caesarshift_opt =     app.add_option("-c, --caesarshift", caesarshift, "& [shift value]");
    auto mode_opt =            app.add_option("--mode", mode, "Caesarshift mode: [alnum] [alpha] [digit]");
    caesarshift_opt->excludes(settings.man_opt);
    mode_opt->excludes(settings.man_opt);

    parse_arguments(app, argc, argv);  // argument_parser.h
    cout_man(settings.show_man);  // cout_man.h"
    validate_arguments(settings);  // argument_validation.h

    // var
    if (!caesarshift) {
        std::cout << "Error: caesarshift encoding/decoding requires the --caesarshift flag.\n";
        return;
    }

    handle_pipe_input(settings);  // pipe_input_handler.h

    if (!settings.input.empty()) {
        handle_entered_input(settings.input, settings.encode, settings.decode, caesarshift, mode); // var
    }
}


int main(int argc, char* argv[]) {
    CLI::App app{"Morse Encoder/Decoder Program"};
    process_arguments(app, argc, argv);
    return 0;
}

