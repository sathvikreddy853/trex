#include <parser.hpp>

Token Parser::peek () const {
    return tokens[pos];
}

void Parser::advance () {
    pos += 1;
}

/* moves ahead only if it matches */
bool Parser::match (TokenType type) {
    if (peek ().type != type) {
        return false;
    }

    advance ();
    return true;
}

std::shared_ptr<ASTNode> parse (const std::vector<Token>& tokens) {
    Parser parser (tokens);
    auto node = parser.parse_expression ();
    return node;
}

std::shared_ptr<ASTNode> Parser::parse_expression () {
    auto root = parse_term ();
    while (match (TokenType::UNION)) {
        auto right = parse_term ();
        root       = std::make_shared<ASTNode> (NodeType::UNION, root, right);
    }

    return root;
}

std::shared_ptr<ASTNode> Parser::parse_term () {
    auto root = parse_factor ();
    while (match (TokenType::CONCAT)) {
        auto right = parse_factor ();
        root       = std::make_shared<ASTNode> (NodeType::CONCAT, root, right);
    }

    return root;
}

std::shared_ptr<ASTNode> Parser::parse_factor () {
    auto root = parse_base ();
    switch (peek ().type) {
    case TokenType::STAR:
        advance ();
        root = std::make_shared<ASTNode> (NodeType::STAR, root);
        break;
    case TokenType::OPT:
        advance ();
        root = std::make_shared<ASTNode> (NodeType::OPT, root);
        break;
    case TokenType::PLUS:
        advance ();
        root = std::make_shared<ASTNode> (NodeType::PLUS, root);
        break;
    default: break;
    }

    return root;
}

std::shared_ptr<ASTNode> Parser::parse_base () {
    if (match (TokenType::CHAR)) {
        return std::make_shared<ASTNode> (NodeType::CHAR, tokens[pos - 1].value.value ());
    } else if (match (TokenType::DOT)) {
        return std::make_shared<ASTNode> (NodeType::DOT);
    } else if (match (TokenType::LPAREN)) {
        auto node = parse_expression ();
        match (TokenType::RPAREN);
        return node;
    }

    return nullptr;
}