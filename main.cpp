#include <macros.hpp>
#include <lexer.hpp>

int main () {
    auto tokens = tokenize("a(b|c)*d");
    for (auto token : tokens)
        std::cout << token << ' ';
    std::cout << std::endl;

    return 0;
}