#ifndef TREX_AST
#define TREX_AST

#include <macros.hpp>

namespace trex {
namespace ast {
    struct Node {
        enum struct Type { CHAR, UNION, CONCAT, STAR, PLUS, OPT, DOT };

        Type type;
        std::optional<char> value;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;

        Node (Type type, std::shared_ptr<Node> left = nullptr, std::shared_ptr<Node> right = nullptr)
        : type (type), value (std::nullopt), left (std::move (left)), right (std::move (right)) {}

        Node (Type type, char value, std::shared_ptr<Node> left = nullptr, std::shared_ptr<Node> right = nullptr)
        : type (type), value (value), left (std::move (left)), right (std::move (right)) {}
    };

    std::ostream& operator<< (std::ostream& output, Node::Type type);
    std::ostream& operator<< (std::ostream& output, const std::shared_ptr<Node>& node);
} // namespace ast
} // namespace trex

#endif // TREX_AST
