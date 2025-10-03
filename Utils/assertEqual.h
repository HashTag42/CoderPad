#include <iostream>
#include <string>

#define ASSERT_STR_EQ(a, b) assertEqual(std::string(a), std::string(b))

template <typename T>
bool assertEqual(const T& actual, const T& expected) {
    std::string msg = "[assertEqual] ";
    bool result;

    if (actual == expected) {
        msg += "PASS";
        result = true;
    }
    else {
        msg += "FAIL: \"" + actual + "\" != \"" + expected + "\"";
        result = false;
    }

    std::cerr << msg << std::endl;
    return result;
}