#include <dfa.hpp>
#include <lexer.hpp>
#include <macros.hpp>
#include <nfa.hpp>
#include <parser.hpp>

int main () {
    auto text   = "abbcda";
    auto tokens = TREX::Lexer::tokenize ("a.*a");

    std::println ("Abstract Syntax Tree:");
    std::shared_ptr<ASTNode> node = TREX::Parser::parse (tokens);
    std::cout << node << std::endl;

    TREX::NFA nfa = TREX::NFA::build (node);
    TREX::DFA dfa = TREX::DFA::construct (nfa);
    std::println ("Match: {}", dfa.match (text));

    return 0;
}