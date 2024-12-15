#ifndef MAIN_MAN_H
#define MAIN_MAN_H

#include <iostream>


// manual for generic functionalities, repository wide --man arg
void main_man() {
    std::cout << "Usage: program [algo e.g -cs] [-e/-d] [optional for algo argument e.g 5] [-i 'input'/-p (pipe)]\n\n";
    std::cout << "Input:\n";
    std::cout << " [-p]\t\tInput pipe\n";
    std::cout << " [-i]\t\tInput arg (may use quotes ' or doublequotes \" to pass quotes or slashes as prefix escape as usual w bash\n\n";
    std::cout << "Task:\n";
    std::cout << " [-e], [--encode]\tEncode the input\n";
    std::cout << " [-d], [--decode]\tDecode the input\n\n";
    std::cout << "Samples General:\n\n";
    std::cout << "[algo e.g -cs] [-e/-d] [-i 'input'] (double quote container) \"bin\"\n";
    std::cout << "[algo e.g -cs] [-e/-d] [-i 'input'] (single quote container) 'bin'\n";
    std::cout << "[algo e.g -cs] [-e/-d] [-i 'input'] (w escaped quote) \\'bin\\'\n";
    std::cout << "[algo e.g -cs] [-e/-d] [-i 'input'] (w escaped backslash) \\\\bin\\\\\n\n";
}

#endif