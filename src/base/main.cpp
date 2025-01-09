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

#include <CLI/App.hpp>

#include "base_dec_enc.h"


void exec_man() {
    std::cout << "Base16:\n\n";
    std::cout << "bin/base --base16 -e -i '1\n";
    std::cout << "bin/base --base16 -d -i '616161'\n\n";

    std::cout << "Base32 RFC3548, RFC4648:\n\n";
    std::cout << "bin/base --base32 -e -i 'l4713116\n";
    std::cout << "bin/base --base32 -d -i 'MJVXK5ZTGAYHA4ZTGQ2TMNZS'\n\n";

    std::cout << "Base58:\n\n";
    std::cout << "bin/base --base58 -e -i 'robotfindskitten ᓚᘏᗢ'\n";
    std::cout << "bin/base --base58 -d -i 'CDpsYwLqYmttknVQ4JviU7VfMZXxLPQS5Drn8uCvQ1VxCRgt'\n\n";

    std::cout << "Base62:\n\n";
    std::cout << "bin/base --base62 -e -i '1YeShqwJ57qncOrK6U'\n";
    std::cout << "bin/base --base62 -d -i '4PCnHV'\n\n";

    std::cout << "Base64:\n\n";
    std::cout << "bin/base --base64 -e -i 'ulimit'\n";
    std::cout << "bin/base --base64 -d -i 'OigpeyA6fDomIH07Og=='\n\n";
}


void handle_entered_input(const std::string& input, bool encode, bool decode, bool base58, bool base16, bool base32, bool base62, bool base64) { // var

    validate_input(input, encode, decode);  // input_validation.h

    std::function<std::string(const std::string&)> encode_func;
    
    // var
    if (base58) {
        encode_func = (encode) ? base58_encode : base58_decode;
    } else if (base16) {
        encode_func = (encode) ? base16_encode : base16_decode;
    } else if (base32) {
        encode_func = (encode) ? base32_encode : base32_decode;

    } else if (base62) {
        encode_func = (encode) ? base62_encode : base62_decode;
    } else if (base64) {
        encode_func = (encode) ? base64_encode : base64_decode;
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
    bool base16 = false;
    auto base16_opt = app.add_flag("--base16", base16, "base16");
    bool base32 = false;
    auto base32_opt = app.add_flag("--base32", base32, "base32");
    bool base58 = false;
    auto base58_opt = app.add_flag("--base58", base58, "base58");
    bool base62 = false;
    auto base62_opt = app.add_flag("--base62", base62, "base62");
    bool base64 = false;
    auto base64_opt = app.add_flag("--base64", base64, "base64");
    base16_opt->excludes(settings.man_opt);
    base32_opt->excludes(settings.man_opt);
    base58_opt->excludes(settings.man_opt);
    base62_opt->excludes(settings.man_opt);
    base64_opt->excludes(settings.man_opt);


    parse_arguments(app, argc, argv);  // argument_parser.h
    cout_man(settings.show_man);  // man_cout.h"

    // input handling
    validate_arguments(settings);  // argument_validation.h

    // var
    if (!base58 && !base16 && !base32 && !base62 & !base64) {
        std::cout << "Error: You must specify either --base58 or --base62 for encoding/decoding.\n";
        return;
    }
    handle_pipe_input(settings);  // pipe_input_handler.h

    if (!settings.input.empty()) {
        handle_entered_input(settings.input, settings.encode, settings.decode, base58, base16, base32, base62, base64); // var
    }
}


int main(int argc, char* argv[]) {
    CLI::App app{"Morse Encoder/Decoder Program"};
    process_arguments(app, argc, argv);
    return 0;
}

