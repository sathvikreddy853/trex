#include <lexer.hpp>

namespace trex {

bool Lexer::has_next () const { return pos < pattern.size (); }

Token Lexer::next () {
    using enum Token::Type;

    if (not has_next ()) return Token (END);

    char value = pattern[pos++];
    switch (value) {
    case '|': return Token (UNION);
    case '+': return Token (PLUS);
    case '*': return Token (STAR);
    case '?': return Token (OPT);
    case '.': return Token (DOT);
    case '(': return Token (LPAREN);
    case ')': return Token (RPAREN);
    default: return Token (CHAR, value);
    }
}

std::vector<Token> Lexer::tokenize (const std::string& pattern) {
    using enum Token::Type;

    Lexer lexer (pattern);
    std::vector<Token> tokens;

    Token::Type prev = NONE;
    Token::Type curr = NONE;

    while (lexer.has_next ()) {
        Token token = lexer.next ();
        curr        = token.type;

        bool curr_can_be = (curr == CHAR or curr == LPAREN or curr == DOT);
        bool prev_can_be =
        (prev == CHAR or prev == RPAREN or prev == PLUS or prev == OPT or prev == STAR or prev == DOT);

        if (curr_can_be and prev_can_be) tokens.emplace_back (CONCAT);

        tokens.push_back (token);
        prev = token.type;
    }

    tokens.emplace_back (END);

    return tokens;
}

} // namespace trex