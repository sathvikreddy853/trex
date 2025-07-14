#include <lexer.hpp>
#include <macros.hpp>
#include <parser.hpp>
#include <nfa.hpp>
#include <dfa.hpp>

int main () {
    std::string text = "abbcda";
    auto tokens = Lexer::tokenize ("a.*a");

    std::println("Abstract Syntax Tree:");
    std::shared_ptr<ASTNode> node = Parser::parse(tokens);
    std::cout << node << std::endl;

    NFA nfa = NFA::build(node);
    DFA dfa = DFA::construct(nfa);
    std::println("Match: {}", dfa.match(text));

    return 0;
}