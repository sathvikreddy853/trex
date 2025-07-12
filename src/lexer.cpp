#include <lexer.hpp>

bool Lexer::has_next() const {
    return pos < pattern.size();
}

Token Lexer::next () {
    if (not has_next())  {
        return Token(TokenType::END, '\0');
    }

    char value = pattern[pos++];
    switch(value) {
        case '|': return Token(TokenType::UNION, '|');
        case '+': return Token(TokenType::PLUS, '+');
        case '*': return Token(TokenType::STAR, '*');
        case '?': return Token(TokenType::OPTIONAL, '?');
        case '.': return Token(TokenType::DOT, '.');
        case '(': return Token(TokenType::LPAREN, '(');
        case ')': return Token(TokenType::RPAREN, ')');
        default: return Token(TokenType::CHAR, value);
    }
}

std::vector<Token> tokenize(const std::string& pattern)  {
    Lexer lexer(pattern);
    std::vector<Token> tokens;

    while (lexer.has_next()) {
        tokens.push_back(lexer.next());
    }
    
    tokens.emplace_back(TokenType::END);

    return tokens;
}