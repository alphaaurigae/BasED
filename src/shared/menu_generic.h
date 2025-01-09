#ifndef MENU_GENERIC_H
#define MENU_GENERIC_H

#include "process_input.h"

#include <string>

#include <CLI/CLI.hpp>


// handle void process_arguments main.cpp
struct AppSettings {
    bool encode = false;
    bool decode = false;

    std::string input;
    bool pipe_input = false;

    bool show_man = false;


    // init pre
    CLI::Option* man_opt = nullptr;

    // general arguments e.g multi bin
    void setup_app(CLI::App& app) {
        auto encode_opt = app.add_flag("-e, --encode", encode, "Encode the input");
        auto decode_opt = app.add_flag("-d, --decode", decode, "Decode the input");
        encode_opt->excludes(decode_opt);
        decode_opt->excludes(encode_opt);

        auto input_opt = app.add_option("-i, --input", input, "Input argument");
        auto pipe_opt = app.add_flag("-p, --pipe", pipe_input, "Pipe input");
        input_opt->excludes(pipe_opt);
        pipe_opt->excludes(input_opt);

        man_opt = app.add_flag("--man", show_man, "Display detailed manual");

        man_opt->excludes(decode_opt);
        man_opt->excludes(encode_opt);
        man_opt->excludes(pipe_opt);
        man_opt->excludes(input_opt);
    }
};

#endif