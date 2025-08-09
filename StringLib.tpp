#include <sstream>
#include <vector>
#include <string>

namespace StringLib {
    template <typename T>
    std::string arrayToString(const std::vector<T> &arr, const std::string &delimiter) {
        std::ostringstream oss;
        for (size_t i = 0; i < arr.size(); ++i) {
            oss << arr[i];
            if (i != arr.size() - 1) oss << delimiter;
        }
        return oss.str();
    }
}
