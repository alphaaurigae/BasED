#ifndef MORSE_DEC_ENC_H
#define MORSE_DEC_ENC_H

#include <map>
#include <cctype>
#include <sstream>
#include <string>

std::map<char, std::string> get_morse_standard_map() {
    return {
        {'A', ".-"}, 
        {'B', "-..."}, 
        {'C', "-.-."}, 
        {'D', "-.."},
        {'E', "."},
        {'F', "..-."}, 
        {'G', "--."}, 
        {'H', "...."}, 
        {'I', ".."}, 
        {'J', ".---"},
        {'K', "-.-"}, 
        {'L', ".-.."}, 
        {'M', "--"}, 
        {'N', "-."}, 
        {'O', "---"},
        {'P', ".--."}, 
        {'Q', "--.-"}, 
        {'R', ".-."}, 
        {'S', "..."}, 
        {'T', "-"},
        {'U', "..-"}, 
        {'V', "...-"}, 
        {'W', ".--"}, 
        {'X', "-..-"}, 
        {'Y', "-.--"},
        {'Z', "--.."}, 
        {'0', "-----"}, 
        {'1', ".----"}, 
        {'2', "..---"}, 
        {'3', "...--"},
        {'4', "....-"}, 
        {'5', "....."}, 
        {'6', "-...."}, 
        {'7', "--..."}, 
        {'8', "---.."},
        {'9', "----."}, 
        {' ', " "}
    };
}

std::map<std::string, char> get_reverse_morse_standard_map() {
    std::map<char, std::string> morse_standard_map = get_morse_standard_map();
    std::map<std::string, char> reverse_morse_standard_map;

    for (const auto& pair : morse_standard_map) {
        reverse_morse_standard_map[pair.second] = pair.first;
    }

    return reverse_morse_standard_map;
}
std::string morse_standard_encode(std::string plaintext) {
    auto morse_standard_map = get_morse_standard_map();
    std::stringstream ss;
    for (char c : plaintext) {
        auto it = morse_standard_map.find(toupper(c));
        if (it != morse_standard_map.end()) {
            ss << it->second << ' ';
        }
    }
    return ss.str();
}
std::string morse_standard_decode(std::string ciphertext) {
    auto reverse_morse_standard_map = get_reverse_morse_standard_map();
    std::stringstream ss(ciphertext);
    std::string word;
    std::string plaintext;

    while (ss >> word) {
        auto it = reverse_morse_standard_map.find(word);
        if (it != reverse_morse_standard_map.end()) {
            plaintext += it->second;
        }
    }

    return plaintext;
}

#endif


// NOTES:

// 1. Double-Tap for Dash Mapping


//    Use "." for dots (single taps).
//    Use ".." for dashes (double taps).
//    Add spaces to separate elements (dots, dashes) within a letter.



/*
std::map<std::string, char> double_tap_morse_map{
    {". ..", 'A'}, // ".-" -> dot, space, double-tap (dash)
    {".. . . .", 'B'}, // "-..." -> double-tap, dot, dot, dot
    {".. . .. .", 'C'}, // "-.-." -> double-tap, dot, double-tap, dot
    {".. . .", 'D'}, // "-.." -> double-tap, dot, dot
    {".", 'E'}, // "." -> dot
    {". . .. .", 'F'}, // "..-." -> dot, dot, double-tap, dot
    {".. .. .", 'G'}, // "--." -> double-tap, double-tap, dot
    {". . . .", 'H'}, // "...." -> dot, dot, dot, dot
    {". .", 'I'}, // ".." -> dot, dot
    {". .. .. ..", 'J'}, // ".---" -> dot, double-tap, double-tap, double-tap
    {".. . ..", 'K'}, // "-.-" -> double-tap, dot, double-tap
    {". .. . .", 'L'}, // ".-.." -> dot, double-tap, dot, dot
    {".. ..", 'M'}, // "--" -> double-tap, double-tap
    {".. .", 'N'}, // "-." -> double-tap, dot
    {".. .. ..", 'O'}, // "---" -> double-tap, double-tap, double-tap
    {". .. .. .", 'P'}, // ".--." -> dot, double-tap, double-tap, dot
    {".. .. . ..", 'Q'}, // "--.-" -> double-tap, double-tap, dot, double-tap
    {". .. .", 'R'}, // ".-." -> dot, double-tap, dot
    {". . .", 'S'}, // "..." -> dot, dot, dot
    {"..", 'T'}, // "-" -> double-tap
    {". . ..", 'U'}, // "..-" -> dot, dot, double-tap
    {". . . ..", 'V'}, // "...-" -> dot, dot, dot, double-tap
    {". .. ..", 'W'}, // ".--" -> dot, double-tap, double-tap
    {".. . . ..", 'X'}, // "-..-" -> double-tap, dot, dot, double-tap
    {".. . .. ..", 'Y'}, // "-.--" -> double-tap, dot, double-tap, double-tap
    {".. .. . .", 'Z'}, // "--.." -> double-tap, double-tap, dot, dot
    {".. .. .. .. ..", '0'}, // "-----" -> five double-taps
    {". .. .. .. ..", '1'}, // ".----" -> dot, four double-taps
    {". . .. .. ..", '2'}, // "..---" -> two dots, three double-taps
    {". . . .. ..", '3'}, // "...--" -> three dots, two double-taps
    {". . . . ..", '4'}, // "....-" -> four dots, one double-tap
    {". . . . .", '5'}, // "....." -> five dots
    {".. . . . .", '6'}, // "-...." -> one double-tap, four dots
    {".. .. . . .", '7'}, // "--..." -> two double-taps, three dots
    {".. .. .. . .", '8'}, // "---.." -> three double-taps, two dots
    {".. .. .. .. .", '9'}, // "----." -> four double-taps, one dot
    {" ", ' '} // Space for word gap
};

*/