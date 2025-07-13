#ifndef TREX_LEXER
#define TREX_LEXER

#include <macros.hpp>
#include <token.hpp>

class Lexer {
    public:
    explicit Lexer (const std::string& pattern) : pattern (pattern), pos (0) {
    }

    Token next () ;
    bool has_next() const;

    private:
    std::string pattern;
    u32 pos;
};

std::vector<Token> tokenize(const std::string& pattern);

#endif // TREX_LEXER