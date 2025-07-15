#ifndef TREX_LEXER
#define TREX_LEXER

#include <macros.hpp>
#include <token.hpp>

namespace trex {

class Lexer {
    public:
    explicit Lexer (const std::string& pattern) : pattern (pattern), pos (0) {}

    Token next ();
    bool has_next () const;

    static std::vector<Token> tokenize (const std::string& pattern);

    private:
    std::string pattern;
    uint32_t pos;
};

} // namespace trex

#endif // TREX_LEXER