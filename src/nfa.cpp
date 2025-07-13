#include <nfa.hpp>

std::ostream& operator<<(std::ostream& output, TransitionType type) {
    using enum TransitionType;
    switch (type) {
        case CHAR: output << "CHAR"; break;
        case DOT: output << "DOT"; break;
        case EPSILON: output << "EPSILON"; break;
        default: output << "NONE"; break;
    }
    return output;
}


NFA NFA::build (const std::shared_ptr<ASTNode>& node) {
    using enum NodeType;
    switch (node->type) {
    case CHAR: return NFA (get_id(), get_id(), TransitionType::CHAR, node->value.value());
    case DOT: return NFA (get_id(), get_id(), TransitionType::DOT);
    case CONCAT: return build_concat(build(node->left), build(node->right));
    case UNION: return build_union(build(node->left), build(node->right));
    case STAR: return build_star(build(node->left));
    case PLUS: return build_plus(build(node->left));
    case OPT: return build_opt(build(node->left));
    default: std::println("error: invalid node type in nfa"); break;
    }
}

NFA NFA::build_union (const NFA& alice, const NFA& bob) {
    u32 start = get_id();
    u32 accept = get_id();

    NFA carol(start, accept);
    carol.transitions = alice.transitions;
    for (auto& [node, vec] : bob.transitions) {
        carol.transitions[node].insert(carol.transitions[node].end(), vec.begin(), vec.end());
    }

    carol.transitions[start].emplace_back(alice.start, TransitionType::EPSILON);
    carol.transitions[start].emplace_back(bob.start, TransitionType::EPSILON);

    carol.transitions[alice.accept].emplace_back(accept, TransitionType::EPSILON);
    carol.transitions[bob.accept].emplace_back(accept, TransitionType::EPSILON);

    return carol;
}

NFA NFA::build_concat (const NFA& alice, const NFA& bob) {
    NFA carol(alice.start, bob.accept);
    
    carol.transitions = alice.transitions;
    for (auto& [node, vec] : bob.transitions) {
        carol.transitions[node].insert(carol.transitions[node].end(), vec.begin(), vec.end());
    }

    carol.transitions[alice.accept].emplace_back(bob.start, TransitionType::EPSILON);

    return carol;
}

NFA NFA::build_star (const NFA& alice) {
    u32 start = get_id();
    u32 accept = get_id();

    NFA carol(start, accept);
    carol.transitions = alice.transitions;

    carol.transitions[start].emplace_back(alice.start, TransitionType::EPSILON);
    carol.transitions[start].emplace_back(accept, TransitionType::EPSILON);

    carol.transitions[alice.accept].emplace_back(alice.start, TransitionType::EPSILON);
    carol.transitions[alice.accept].emplace_back(accept, TransitionType::EPSILON);

    return carol;
}

NFA NFA::build_opt (const NFA& alice) {
    u32 start = get_id();
    u32 accept = get_id();

    NFA carol(start, accept);
    carol.transitions = alice.transitions;

    carol.transitions[start].emplace_back(alice.start, TransitionType::EPSILON);
    carol.transitions[alice.accept].emplace_back(accept, TransitionType::EPSILON);
    carol.transitions[start].emplace_back(accept, TransitionType::EPSILON);

    return carol;
}

NFA NFA::build_plus (const NFA& alice) {
    u32 accept = get_id();

    NFA carol(alice.start, accept);
    carol.transitions = alice.transitions;

    carol.transitions[alice.accept].emplace_back(accept, TransitionType::EPSILON);
    carol.transitions[alice.accept].emplace_back(alice.start, TransitionType::EPSILON);

    return carol;
}
