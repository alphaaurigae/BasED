#ifndef INPUT_GENERIC_H
#define INPUT_GENERIC_H

#include <string>
#include <vector>


std::vector<std::string> parse_input(const std::string& input) {
    std::vector<std::string> result;
    std::string current = "";
    bool in_quotes = false;
    bool escape = false;

    for (char c : input) {
        if (escape) {
            current += c;
            escape = false;
        } else if (c == '\\') {
            escape = true;
        } else if (c == '\"') {
            in_quotes = !in_quotes;
        } else if (c == ' ' && !in_quotes) {
            if (!current.empty()) {
                result.push_back(current);
                current.clear();
            }
        } else {
            current += c;
        }
    }
    if (!current.empty()) {
        result.push_back(current);
    }
    return result;
}

#endif