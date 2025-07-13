#ifndef TREX_NFA
#define TREX_NFA

#include <macros.hpp>
#include <ast.hpp>

enum struct TransitionType { CHAR, EPSILON, DOT, NONE };

struct State {
    int id;
    TransitionType type;
    std::optional<char> value;

    State* out1 = nullptr;
    State* out2 = nullptr;

    State(TransitionType type) : id(next_id++), type(type), value(std::nullopt) {}
    State(TransitionType type, char value) : id(next_id++), type(type), value(value) {}
    
    static int next_id;
};

struct NFA {
    State* start;
    State* accept;

    static NFA build_nfa(const std::shared_ptr<ASTNode>& node);
    static NFA build_char(char value);
    static NFA build_dot();
    static NFA build_union(const std::shared_ptr<ASTNode>& left, const std::shared_ptr<ASTNode>& right);
    static NFA build_concat(const std::shared_ptr<ASTNode>& left, const std::shared_ptr<ASTNode>& right);
    static NFA build_star(const std::shared_ptr<ASTNode>& child);
    static NFA build_opt(const std::shared_ptr<ASTNode>& child);
    static NFA build_plus(const std::shared_ptr<ASTNode>& child);

    NFA(State* start, State* accept) : start(start), accept(accept) {}
};

#endif // TREX_NFA