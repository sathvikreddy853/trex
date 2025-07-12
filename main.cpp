#include <lexer.hpp>
#include <macros.hpp>
#include <parser.hpp>

int main () {
    auto tokens = tokenize ("a(b|c)*d");
    for (auto token : tokens)
        std::cout << token << ' ';
    std::cout << std::endl;

    Parser parser (tokens);
    std::shared_ptr<ASTNode> node = parser.parse ();

    std::queue<std::shared_ptr<ASTNode>> nodes;
    nodes.push (node);
    while (not nodes.empty ()) {
        auto u = nodes.front ();
        nodes.pop ();

        std::cout << u->type;
        if (u->value.has_value())
            std::cout << '(' << u->value.value() <<  ')';
        std::cout << std::endl;

        if (u->left)
            nodes.push (u->left);
        if (u->right)
            nodes.push (u->right);
    }


    return 0;
}