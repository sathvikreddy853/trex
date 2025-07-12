#ifndef PARSER_HPP
#define PARSER_HPP

#include <ast.hpp>
#include <macros.hpp>
#include <token.hpp>

/*
 * Parser Grammar:

 * <EXPRESSION> -> <TERM> ( UNION <TERM>) STAR
 * <TERM> -> <FACTOR> ( CONCAT <FACTOR> ) *
 * <FACTOR> -> <BASE> ( STAR | PLUS | OPT ) OPT
 * <BASE> -> CHAR | LPAREN <EXPRESSION> RPAREN
 */

class Parser {
    public:
    explicit Parser (const std::vector<Token>& tokens)
    : tokens (tokens), pos (0) {
    }

    std::shared_ptr<ASTNode> parse ();

    private:
    const std::vector<Token>& tokens;
    u32 pos;

    Token peek () const;
    void advance ();
    bool match (TokenType type);

    std::shared_ptr<ASTNode> parse_expression ();
    std::shared_ptr<ASTNode> parse_term ();
    std::shared_ptr<ASTNode> parse_factor ();
    std::shared_ptr<ASTNode> parse_base ();
};

#endif // PARSER_HPP