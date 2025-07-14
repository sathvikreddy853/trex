#include <nfa.hpp>

std::ostream& operator<< (std::ostream& output, NFA::Transition::Type type) {
    using enum NFA::Transition::Type;
    switch (type) {
    case CHAR: output << "CHAR"; break;
    case DOT: output << "DOT"; break;
    case EPSILON: output << "EPSILON"; break;
    default: output << "NONE"; break;
    }
    return output;
}


NFA NFA::build (const std::shared_ptr<ASTNode>& node) {
    using enum ASTNode::Type;
    switch (node->type) {
    case CHAR: return NFA (get_id (), get_id (), Transition::Type::CHAR, node->value.value ());
    case DOT: return NFA (get_id (), get_id (), Transition::Type::DOT);
    case CONCAT: return build_concat (build (node->left), build (node->right));
    case UNION: return build_union (build (node->left), build (node->right));
    case STAR: return build_star (build (node->left));
    case PLUS: return build_plus (build (node->left));
    case OPT: return build_opt (build (node->left));
    default: std::println ("error: invalid node type in nfa"); break;
    }
}

NFA NFA::build_union (const NFA& alice, const NFA& bob) {
    u32 start  = get_id ();
    u32 accept = get_id ();

    NFA carol (start, accept);
    carol.transitions = alice.transitions;
    for (auto& [node, vec] : bob.transitions) {
        carol.transitions[node].insert (carol.transitions[node].end (), vec.begin (), vec.end ());
    }

    carol.transitions[start].emplace_back (alice.start, Transition::Type::EPSILON);
    carol.transitions[start].emplace_back (bob.start, Transition::Type::EPSILON);

    carol.transitions[alice.accept].emplace_back (accept, Transition::Type::EPSILON);
    carol.transitions[bob.accept].emplace_back (accept, Transition::Type::EPSILON);

    return carol;
}

NFA NFA::build_concat (const NFA& alice, const NFA& bob) {
    NFA carol (alice.start, bob.accept);

    carol.transitions = alice.transitions;
    for (auto& [node, vec] : bob.transitions) {
        carol.transitions[node].insert (carol.transitions[node].end (), vec.begin (), vec.end ());
    }

    carol.transitions[alice.accept].emplace_back (bob.start, Transition::Type::EPSILON);

    return carol;
}

NFA NFA::build_star (const NFA& alice) {
    u32 start  = get_id ();
    u32 accept = get_id ();

    NFA carol (start, accept);
    carol.transitions = alice.transitions;

    carol.transitions[start].emplace_back (alice.start, Transition::Type::EPSILON);
    carol.transitions[start].emplace_back (accept, Transition::Type::EPSILON);

    carol.transitions[alice.accept].emplace_back (alice.start, Transition::Type::EPSILON);
    carol.transitions[alice.accept].emplace_back (accept, Transition::Type::EPSILON);

    return carol;
}

NFA NFA::build_opt (const NFA& alice) {
    u32 start  = get_id ();
    u32 accept = get_id ();

    NFA carol (start, accept);
    carol.transitions = alice.transitions;

    carol.transitions[start].emplace_back (alice.start, Transition::Type::EPSILON);
    carol.transitions[alice.accept].emplace_back (accept, Transition::Type::EPSILON);
    carol.transitions[start].emplace_back (accept, Transition::Type::EPSILON);

    return carol;
}

NFA NFA::build_plus (const NFA& alice) {
    u32 accept = get_id ();

    NFA carol (alice.start, accept);
    carol.transitions = alice.transitions;

    carol.transitions[alice.accept].emplace_back (accept, Transition::Type::EPSILON);
    carol.transitions[alice.accept].emplace_back (alice.start, Transition::Type::EPSILON);

    return carol;
}

std::set<u32> NFA::epsilon_closure (std::set<u32> states) const {
    std::stack<u32> stack;
    std::set<u32> closure = states;

    for (u32 state : states)
        stack.push (state);

    while (not stack.empty ()) {
        u32 state = stack.top ();
        stack.pop ();

        if (not transitions.contains (state))
            continue;

        for (auto& [to, type, value] : transitions.at (state)) {
            if (type == Transition::Type::EPSILON and closure.insert (to).second)
                stack.push (to);
        }
    }

    return closure;
}

std::set<u32> NFA::move (std::set<u32> states, std::optional<char> symbol) const {
    std::set<u32> result;

    for (u32 state : states) {
        if (not transitions.contains (state))
            continue;

        for (auto& [to, type, value] : transitions.at (state)) {
            if (type == Transition::Type::CHAR and symbol.has_value () and value == symbol.value()) {
                result.insert (to);
            } else if (type == Transition::Type::DOT) {
                result.insert (to);
            }
        }
    }

    return result;
}
