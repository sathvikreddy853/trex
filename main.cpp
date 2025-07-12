#include <lexer.hpp>
#include <macros.hpp>
#include <parser.hpp>

int main () {
    auto tokens = tokenize ("a(b|c)*d");
    for (auto token : tokens)
        std::cout << token << ' ';
    std::cout << std::endl << std::endl;

    std::shared_ptr<ASTNode> node = parse(tokens);
    std::cout << node << std::endl;
    return 0;
}