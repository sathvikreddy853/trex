#include <token.hpp>

std::ostream& operator<< (std::ostream& output, TokenType type) {
    switch (type) {
    case TokenType::CHAR: output << "CHAR"; break;
    case TokenType::UNION: output << "UNION"; break;
    case TokenType::CONCAT: output << "CONCAT"; break;
    case TokenType::STAR: output << "STAR"; break;
    case TokenType::PLUS: output << "PLUS"; break;
    case TokenType::OPTIONAL: output << "OPTIONAL"; break;
    case TokenType::DOT: output << "DOT"; break;
    case TokenType::LPAREN: output << "LPAREN"; break;
    case TokenType::RPAREN: output << "RPAREN"; break;
    case TokenType::END: output << "END"; break;
    default: output << "NONE"; break;
    }

    return output;
}

std::ostream& operator<< (std::ostream& output, Token token) {
    output << '<' << token.type << ':' << token.value << '>';
    return output;
}