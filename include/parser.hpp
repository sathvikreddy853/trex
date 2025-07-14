#ifndef TREX_PARSER
#define TREX_PARSER

#include <ast.hpp>
#include <macros.hpp>
#include <token.hpp>

/*
 * Parser Grammar:

 * <EXPRESSION> -> <TERM> ( UNION <TERM>) STAR
 * <TERM> -> <FACTOR> ( CONCAT <FACTOR> ) STAR
 * <FACTOR> -> <BASE> ( STAR | PLUS | OPT ) OPT
 * <BASE> -> CHAR | LPAREN <EXPRESSION> RPAREN
 */

namespace TREX {

class Parser {
    public:
    explicit Parser (const std::vector<Token>& tokens) : tokens (tokens), pos (0) {
    }

    Token peek () const;
    void advance ();
    bool match (Token::Type type);

    std::shared_ptr<ASTNode> parse_expression ();
    std::shared_ptr<ASTNode> parse_term ();
    std::shared_ptr<ASTNode> parse_factor ();
    std::shared_ptr<ASTNode> parse_base ();

    static std::shared_ptr<ASTNode> parse (const std::vector<Token>& tokens);

    private:
    const std::vector<Token>& tokens;
    uint32_t pos;
};

} // namespace TREX

#endif // TREX_PARSER