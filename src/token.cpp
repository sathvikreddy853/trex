#include <token.hpp>

std::ostream& operator<< (std::ostream& output, TokenType type) {
    using enum TokenType;
    switch (type) {
    case CHAR: output << "CHAR"; break;
    case DOT: output << "DOT"; break;
    case UNION: output << "UNION"; break;
    case CONCAT: output << "CONCAT"; break;
    case STAR: output << "STAR"; break;
    case OPT: output << "OPT"; break;
    case PLUS: output << "PLUS"; break;
    case LPAREN: output << "LPAREN"; break;
    case RPAREN: output << "RPAREN"; break;
    case END: output << "END"; break;
    default: output << "NONE"; break;
    }

    return output;
}

std::ostream& operator<< (std::ostream& output, Token token) {
    output << CYAN << token.type << RESET;
    if (token.value.has_value ())
        output << '(' << GREEN << token.value.value () << RESET << ')';

    return output;
}