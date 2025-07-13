#ifndef TREX_TOKEN
#define TREX_TOKEN

#include <macros.hpp>

enum struct TokenType { CHAR, UNION, CONCAT, STAR, PLUS, OPT, DOT, RPAREN, LPAREN, END, NONE };

struct Token {
    TokenType type;
    std::optional<char> value;

    Token (TokenType type = TokenType::NONE) : type (type), value(std::nullopt) {
    }

    Token (TokenType type, char value) : type (type), value (value) {
    }

    friend std::ostream& operator<< (std::ostream&, Token);
};

std::ostream& operator<< (std::ostream& output, TokenType type);
std::ostream& operator<< (std::ostream& output, Token token);

#endif // TREX_TOKEN