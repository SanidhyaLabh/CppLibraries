#include "StringLib.h"
#include <sstream>
#include <cctype>
#include <stack>
#include <stdexcept>
#include <algorithm>
namespace StringLib {

    std::string reverseString(const std::string &str) {
        return std::string(str.rbegin(), str.rend());
    }

    std::string reverseWords(const std::string &str) {
        std::stringstream ss(str);
        std::string word, result;
        while (ss >> word) {
            std::reverse(word.begin(), word.end());
            result += word + " ";
        }
        if (!result.empty()) result.pop_back();
        return result;
    }

    std::string toggleCase(const std::string &str) {
        std::string result = str;
        for (char &c : result) {
            if (std::isupper(static_cast<unsigned char>(c)))
                c = std::tolower(c);
            else if (std::islower(static_cast<unsigned char>(c)))
                c = std::toupper(c);
        }
        return result;
    }

    double evaluateExpressionInString(const std::string &str) {
        std::stringstream ss;
        for (char c : str) {
            if (std::isdigit(c) || c == '+' || c == '-' || c == '*' || c == '/' || c == '.') {
                ss << c;
            }
        }

        // Simple evaluation: only handles expressions like "12+34*2"
        std::string expression = ss.str();
        std::stringstream es(expression);
        std::stack<double> numbers;
        std::stack<char> ops;

        auto applyOp = [](double a, double b, char op) {
            switch (op) {
                case '+': return a + b;
                case '-': return a - b;
                case '*': return a * b;
                case '/': 
                    if (b == 0) throw std::runtime_error("Division by zero");
                    return a / b;
            }
            return 0.0;
        };

        double num;
        char op;
        es >> num;
        numbers.push(num);

        while (es >> op >> num) {
            if (op == '*' || op == '/') {
                double a = numbers.top(); numbers.pop();
                numbers.push(applyOp(a, num, op));
            } else {
                numbers.push(num);
                ops.push(op);
            }
        }

        // Now handle + and -
        std::stack<double> revNumbers;
        while (!numbers.empty()) {
            revNumbers.push(numbers.top());
            numbers.pop();
        }

        double result = revNumbers.top(); revNumbers.pop();
        while (!ops.empty()) {
            char currOp = ops.top(); ops.pop();
            double b = revNumbers.top(); revNumbers.pop();
            if (currOp == '+') result += b;
            else result -= b;
        }

        return result;
    }

    std::vector<int> wordLengths(const std::string &str) {
        std::stringstream ss(str);
        std::string word;
        std::vector<int> lengths;
        while (ss >> word) {
            lengths.push_back(word.size());
        }
        return lengths;
    }

    std::vector<int> toASCII(const std::string &str) {
        std::vector<int> asciiValues;
        for (char c : str) {
            asciiValues.push_back(static_cast<unsigned char>(c));
        }
        return asciiValues;
    }

} // namespace StringLib
