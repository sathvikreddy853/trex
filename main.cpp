#include <lexer.hpp>
#include <macros.hpp>
#include <parser.hpp>
#include <nfa.hpp>
#include <dfa.hpp>

int main () {
    std::string text = "abcbca";
    auto tokens = Lexer::tokenize ("a(bc)*a");
    std::shared_ptr<ASTNode> node = Parser::parse(tokens);
    std::cout << node << std::endl;

    NFA nfa = NFA::build(node);
    DFA dfa = DFA::construct(nfa);
    std::cout << std::boolalpha << dfa.match(text) << std::endl;
    return 0;
}