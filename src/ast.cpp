#include <ast.hpp>

std::ostream& operator<< (std::ostream& output, NodeType type) {
    using enum NodeType;
    switch (type) {
    case CHAR: output << "CHAR"; break;
    case UNION: output << "UNION"; break;
    case CONCAT: output << "CONCAT"; break;
    case STAR: output << "STAR"; break;
    case PLUS: output << "PLUS"; break;
    case OPT: output << "OPT"; break;
    case DOT: output << "DOT"; break;
    default: output << "NONE"; break;
    }

    return output;
}

std::ostream& operator<< (std::ostream& output, const std::shared_ptr<ASTNode>& node) {
    using enum NodeType;
    std::function<void(std::shared_ptr<ASTNode>, std::string, bool, bool)> print_tree;
    print_tree = [&](std::shared_ptr<ASTNode> root, std::string prefix, bool is_left, bool is_root) {
        if (!root) return;

        output << prefix;
        if (not is_root)
            output << (is_left ? "├── " : "└── ");

        switch (root->type) {
            case CHAR:   output << "CHAR('" << root->value.value_or('?') << "')\n"; break;
            case UNION:  output << "UNION\n"; break;
            case CONCAT: output << "CONCAT\n"; break;
            case STAR:   output << "STAR\n"; break;
            case PLUS:   output << "PLUS\n"; break;
            case OPT:    output << "OPT\n"; break;
            case DOT:    output << "DOT\n"; break;
            default:     output << "NONE\n"; break;
        }

        bool has_left  = static_cast<bool>(root->left);
        bool has_right = static_cast<bool>(root->right);

        if (has_left and not has_right) {
            print_tree(root->left,  prefix + (is_left ? "│   " : "    "), false, false);
        } else if (has_left) {
            print_tree(root->left,  prefix + (is_left ? "│   " : "    "), true, false);
        }

        if (has_right) {
            print_tree(root->right, prefix + (is_left ? "│   " : "    "), false, false);
        }
    };

    print_tree(node, "", false, true);
    return output;
}
