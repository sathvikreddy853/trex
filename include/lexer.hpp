#pragma once
#ifndef LEXER_HPP
#define LEXER_HPP

#include <macros.hpp>
#include <token.hpp>

class Lexer {
    public:
    explicit Lexer (const std::string& pattern) : pattern (pattern), pos (0) {
    }

    Token next () ;
    bool has_next() const;
    Token get_escape_token();

    private:
    std::string pattern;
    u32 pos;
};

std::vector<Token> tokenize(const std::string& pattern);

#endif // LEXER_HPP