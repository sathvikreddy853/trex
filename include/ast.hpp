#ifndef TREX_AST
#define TREX_AST

#include <macros.hpp>


struct ASTNode {
    enum struct Type { CHAR, UNION, CONCAT, STAR, PLUS, OPT, DOT };

    Type type;
    std::optional<char> value;
    std::shared_ptr<ASTNode> left;
    std::shared_ptr<ASTNode> right;

    ASTNode (Type type, std::shared_ptr<ASTNode> left = nullptr, std::shared_ptr<ASTNode> right = nullptr)
    : type (type), value (std::nullopt), left (std::move (left)), right (std::move (right)) {
    }

    ASTNode (Type type, char value, std::shared_ptr<ASTNode> left = nullptr, std::shared_ptr<ASTNode> right = nullptr)
    : type (type), value (value), left (std::move (left)), right (std::move (right)) {
    }
};

std::ostream& operator<< (std::ostream& output, ASTNode::Type type);
std::ostream& operator<< (std::ostream& output, const std::shared_ptr<ASTNode>& node);

#endif // TREX_AST