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