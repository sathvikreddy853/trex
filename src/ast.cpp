#include <ast.hpp>

std::ostream& operator<< (std::ostream& output, NodeType type) {
    using enum NodeType;
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

std::ostream& operator<< (std::ostream& output, const std::shared_ptr<ASTNode>& node) {
    using enum NodeType;
    std::function<void (std::shared_ptr<ASTNode>, std::string, bool, bool)> print_tree;
    print_tree = [&] (std::shared_ptr<ASTNode> root, std::string prefix, bool is_left, bool is_root) {
        if (!root)
            return;

        output << prefix;
        if (not is_root)
            output << (is_left ? "├── " : "└── ");

        output << root->type;
        if (root->value.has_value ())
            output << '(' << root->value.value () << ')';
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
