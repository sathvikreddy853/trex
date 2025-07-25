#include <ast.hpp>

namespace trex {

std::ostream& ast::operator<< (std::ostream& output, ast::Node::Type type) {
    using enum ast::Node::Type;
    switch (type) {
    case CHAR: output << "CHAR"; break;
    case DOT: output << "DOT"; break;
    case UNION: output << "UNION"; break;
    case CONCAT: output << "CONCAT"; break;
    case STAR: output << "STAR"; break;
    case OPT: output << "OPT"; break;
    case PLUS: output << "PLUS"; break;
    default: output << "NONE"; break;
    }

    return output;
}

std::ostream& ast::operator<< (std::ostream& output, const std::shared_ptr<ast::Node>& node) {
    using enum ast::Node::Type;
    std::function<void (std::shared_ptr<ast::Node>, std::string, bool, bool)> print_tree;
    print_tree = [&] (std::shared_ptr<ast::Node> root, std::string prefix, bool is_left, bool is_root) {
        if (not root) return;

        output << prefix;
        if (not is_root) output << (is_left ? "├── " : "└── ");

        output << root->type;
        if (root->value.has_value ()) output << '(' << root->value.value () << ')';
        output << std::endl;

        bool has_left  = static_cast<bool> (root->left);
        bool has_right = static_cast<bool> (root->right);

        if (has_left and not has_right) {
            print_tree (root->left, prefix + (not is_root ? (is_left ? "│   " : "    ") : ""), false, false);
        } else if (has_left) {
            print_tree (root->left, prefix + (not is_root ? (is_left ? "│   " : "    ") : ""), true, false);
            print_tree (root->right, prefix + (not is_root ? (is_left ? "│   " : "    ") : ""), false, false);
        } else if (has_right) {
            print_tree (root->right, prefix + (not is_root ? (is_left ? "│   " : "    ") : ""), false, false);
        }
    };

    print_tree (node, "", false, true);
    return output;
}

} // namespace trex