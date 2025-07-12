#ifndef AST_HPP
#define AST_HPP

#include <macros.hpp>

enum struct NodeType { CHAR, UNION, CONCAT, STAR, PLUS, OPT, DOT };

struct ASTNode {
    NodeType type;
    std::optional<char> value;
    std::shared_ptr<ASTNode> left;
    std::shared_ptr<ASTNode> right;

    ASTNode (NodeType type, std::shared_ptr<ASTNode> left = nullptr, std::shared_ptr<ASTNode> right = nullptr)
    : type (type), value (std::nullopt), left (std::move (left)), right (std::move (right)) {
    }

    ASTNode (NodeType type, char value, std::shared_ptr<ASTNode> left = nullptr, std::shared_ptr<ASTNode> right = nullptr)
    : type (type), value (value), left (std::move (left)), right (std::move (right)) {
    }
};

std::ostream& operator<< (std::ostream& output, NodeType type);

#endif // AST_HPP