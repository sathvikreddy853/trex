#include <parser.hpp>

namespace trex {

Token Parser::peek () const { return tokens[pos]; }

void Parser::advance () { pos += 1; }

/* moves ahead only if it matches */
bool Parser::match (Token::Type type) {
    if (peek ().type != type) {
        return false;
    }

    advance ();
    return true;
}

std::shared_ptr<ast::Node> Parser::parse (const std::vector<Token>& tokens) {
    Parser parser (tokens);
    auto node = parser.parse_expression ();
    return node;
}

std::shared_ptr<ast::Node> Parser::parse_expression () {
    auto root = parse_term ();
    while (match (Token::Type::UNION)) {
        auto right = parse_term ();
        root       = std::make_shared<ast::Node> (ast::Node::Type::UNION, root, right);
    }

    return root;
}

std::shared_ptr<ast::Node> Parser::parse_term () {
    auto root = parse_factor ();
    while (match (Token::Type::CONCAT)) {
        auto right = parse_factor ();
        root       = std::make_shared<ast::Node> (ast::Node::Type::CONCAT, root, right);
    }

    return root;
}

std::shared_ptr<ast::Node> Parser::parse_factor () {
    auto root = parse_base ();
    switch (peek ().type) {
    case Token::Type::STAR:
        advance ();
        root = std::make_shared<ast::Node> (ast::Node::Type::STAR, root);
        break;
    case Token::Type::OPT:
        advance ();
        root = std::make_shared<ast::Node> (ast::Node::Type::OPT, root);
        break;
    case Token::Type::PLUS:
        advance ();
        root = std::make_shared<ast::Node> (ast::Node::Type::PLUS, root);
        break;
    default: break;
    }

    return root;
}

std::shared_ptr<ast::Node> Parser::parse_base () {
    if (match (Token::Type::CHAR)) {
        return std::make_shared<ast::Node> (ast::Node::Type::CHAR, tokens[pos - 1].value.value ());
    } else if (match (Token::Type::DOT)) {
        return std::make_shared<ast::Node> (ast::Node::Type::DOT);
    } else if (match (Token::Type::LPAREN)) {
        auto node = parse_expression ();
        match (Token::Type::RPAREN);
        return node;
    }

    return nullptr;
}

} // namespace trex
