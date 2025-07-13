#include <nfa.hpp>

int State::next_id = 0;

NFA NFA::build_nfa (const std::shared_ptr<ASTNode>& node) {
    using enum NodeType;
    switch (node->type) {
    case CHAR: return build_char (node->value.value ()); break;
    case CONCAT: return build_concat(node->left, node->right);
    case UNION:  return build_union(node->left, node->right);
    case STAR:   return build_star(node->left);
    case PLUS:   return build_plus(node->left);
    case OPT:    return build_opt(node->left);
    case DOT:    return build_dot();
    default: throw std::runtime_error("Invalid AST NodeType in build_nfa()"); break;
    }
}

NFA NFA::build_char (char value) {
    auto start  = new State (TransitionType::CHAR, value);
    auto accept = new State (TransitionType::NONE);
    start->out1 = accept;
    return NFA (start, accept);
}

NFA NFA::build_dot () {
    auto start  = new State (TransitionType::DOT);
    auto accept = new State (TransitionType::NONE);
    start->out1 = accept;
    return NFA (start, accept);
}

NFA NFA::build_union (const std::shared_ptr<ASTNode>& left, const std::shared_ptr<ASTNode>& right) {
    NFA nfa1 = build_nfa (left);
    NFA nfa2 = build_nfa (right);

    auto start  = new State (TransitionType::EPSILON);
    auto accept = new State (TransitionType::NONE);

    start->out1 = nfa1.start;
    start->out2 = nfa2.start;

    nfa1.accept->out1 = accept;
    nfa1.accept->type = TransitionType::EPSILON;

    nfa2.accept->out1 = accept;
    nfa2.accept->type = TransitionType::EPSILON;

    return NFA (start, accept);
}

NFA NFA::build_concat (const std::shared_ptr<ASTNode>& left, const std::shared_ptr<ASTNode>& right) {
    NFA nfa1 = build_nfa (left);
    NFA nfa2 = build_nfa (right);

    auto start  = new State (TransitionType::EPSILON);
    auto accept = new State (TransitionType::NONE);

    start->out1 = nfa1.start;

    nfa1.accept->out1 = nfa2.start;
    nfa1.accept->type = TransitionType::EPSILON;

    nfa2.accept->out1 = accept;
    nfa2.accept->type = TransitionType::EPSILON;

    return NFA (start, accept);
}

NFA NFA::build_star (const std::shared_ptr<ASTNode>& child) {
    NFA nfa = build_nfa (child);

    auto start  = new State (TransitionType::EPSILON);
    auto accept = new State (TransitionType::NONE);

    start->out1 = nfa.start;
    start->out2 = accept;

    nfa.accept->out1 = nfa.start;
    nfa.accept->out2 = accept;
    nfa.accept->type = TransitionType::EPSILON;

    return NFA (start, accept);
}

NFA NFA::build_opt (const std::shared_ptr<ASTNode>& child) {
    NFA nfa = build_nfa (child);

    auto start  = new State (TransitionType::EPSILON);
    auto accept = new State (TransitionType::NONE);

    start->out1 = nfa.start;
    start->out2 = accept;

    nfa.accept->out1 = accept;
    nfa.accept->type = TransitionType::EPSILON;

    return NFA (start, accept);
}

NFA NFA::build_plus (const std::shared_ptr<ASTNode>& child) {
    NFA nfa     = build_nfa (child);
    auto accept = new State (TransitionType::NONE);

    nfa.accept->out1 = nfa.start;
    nfa.accept->out2 = accept;
    nfa.accept->type = TransitionType::EPSILON;

    return NFA (nfa.start, accept);
}