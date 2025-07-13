#ifndef TREX_NFA
#define TREX_NFA

#include <ast.hpp>
#include <macros.hpp>

enum struct TransitionType { CHAR, EPSILON, DOT, NONE };

struct Transition {
    u32 to;
    TransitionType type;
    std::optional<char> value;

    Transition (u32 to, TransitionType type, std::optional<char> val = std::nullopt)
    : to (to), type (type), value (val) {
    }
};

struct NFA {
    u32 start;
    u32 accept;
    std::unordered_map<u32, std::vector<Transition>> transitions;

    static inline u32 get_id () {
        static u32 id = 0;
        return id++;
    }

    NFA (u32 start, u32 accept)
    : start (start), accept (accept) {
    }

    NFA (u32 start, u32 accept, TransitionType type, std::optional<char> value = std::nullopt)
    : start (start), accept (accept) {
        transitions[start].emplace_back (accept, type, value);
    }

    static NFA build (const std::shared_ptr<ASTNode>& node);

    static NFA build_union (const NFA&, const NFA&);
    static NFA build_concat (const NFA&, const NFA&);
    static NFA build_star (const NFA&);
    static NFA build_opt (const NFA&);
    static NFA build_plus (const NFA&);
};

std::ostream& operator<< (std::ostream& output, TransitionType type);

#endif // TREX_NFA