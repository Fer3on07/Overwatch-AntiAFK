#include <iostream>

namespace ConsoleColor {
    constexpr const char* RESET = "\033[0m";
    constexpr const char* BLACK = "\033[30m";
    constexpr const char* RED = "\033[31m";
    constexpr const char* GREEN = "\033[32m";
    constexpr const char* YELLOW = "\033[33m";
    constexpr const char* BLUE = "\033[34m";
    constexpr const char* MAGENTA = "\033[35m";
    constexpr const char* CYAN = "\033[36m";
    constexpr const char* LIGHTGRAY = "\033[37m";
    constexpr const char* DARKGRAY = "\033[90m";
    constexpr const char* LIGHTRED = "\033[91m";
    constexpr const char* LIGHTGREEN = "\033[92m";
    constexpr const char* LIGHTYELLOW = "\033[93m";
    constexpr const char* LIGHTBLUE = "\033[94m";
    constexpr const char* LIGHTMAGENTA = "\033[95m";
    constexpr const char* LIGHTCYAN = "\033[96m";
    constexpr const char* WHITE = "\033[97m";

    struct ColorText {
        const char* color;
        std::string text;

        ColorText(const char* c, std::string t) : color(c), text(std::move(t)) {}

        friend std::ostream& operator<<(std::ostream& os, const ColorText& ct) {
            return os << ct.color << ct.text << RESET;
        }
    };
}

// Usage
/*
using namespace ConsoleColor;
#define ColorText(color, text) (ConsoleColor::ColorText((color), (text)))


std::cout << ColorText(GREEN, "[+] ") << ColorText(WHITE, "This is white text.") << std::endl;
std::cout << ColorText(RED, "[-] Error occurred!") << std::endl;
std::cout << ColorText(LIGHTBLUE, "[*] ") << "Normal text follows..." << std::endl;
*/