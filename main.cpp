#include <lexer.hpp>
#include <macros.hpp>
#include <parser.hpp>
#include <nfa.hpp>

int main () {
    auto tokens = Lexer::tokenize ("((ab)*|(ac)*d)?");
    for (auto token : tokens)
        std::cout << token << ' ';
    std::cout << std::endl << std::endl;

    std::shared_ptr<ASTNode> node = Parser::parse(tokens);
    std::cout << node << std::endl;

    NFA nfa = NFA::build(node);
    return 0;
}