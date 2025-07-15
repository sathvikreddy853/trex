#ifndef TREX_TOKEN
#define TREX_TOKEN

#include <macros.hpp>

namespace trex {

struct Token {
    enum struct Type { CHAR, DOT, UNION, CONCAT, STAR, OPT, PLUS, RPAREN, LPAREN, END, NONE };

    Type type;
    std::optional<char> value;

    Token (Type type = Type::NONE) : type (type), value (std::nullopt) {}
    Token (Type type, char value) : type (type), value (value) {}
};

std::ostream& operator<< (std::ostream& output, Token::Type type);
std::ostream& operator<< (std::ostream& output, Token token);

} // namespace trex

#endif // TREX_TOKEN
