#include <dfa.hpp>
#include <lexer.hpp>
#include <macros.hpp>
#include <nfa.hpp>
#include <parser.hpp>

int main () {
    auto text   = "abbcda";
    auto tokens = trex::Lexer::tokenize ("a.*a");

    std::println ("Abstract Syntax Tree:");
    std::shared_ptr<trex::ast::Node> node = trex::Parser::parse (tokens);
    std::cout << node << std::endl;

    trex::NFA nfa = trex::NFA::build (node);
    trex::DFA dfa = trex::DFA::construct (nfa);
    std::println ("Match: {}", dfa.match (text));

    return 0;
}