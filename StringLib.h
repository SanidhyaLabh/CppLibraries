#ifndef STRINGLIB_H
#define STRINGLIB_H

#include <string>
#include <vector>

namespace StringLib {
    // 1. Reverse entire string
    std::string reverseString(const std::string &str);

    // 2. Reverse each word in a string
    std::string reverseWords(const std::string &str);

    // 3. Toggle case
    std::string toggleCase(const std::string &str);

    // 4. Convert array to string
    template <typename T>
    std::string arrayToString(const std::vector<T> &arr, const std::string &delimiter = " ");

    // 5. Arithmetic operations on numbers inside a string
    // Supported: +, -, *, /
    double evaluateExpressionInString(const std::string &str);

    // 6. Length of individual words
    std::vector<int> wordLengths(const std::string &str);

    // 7. Convert to ASCII values
    std::vector<int> toASCII(const std::string &str);
}

#include "StringLib.tpp" // for template implementation

#endif
