#ifndef TREX_NFA
#define TREX_NFA

#include <ast.hpp>
#include <macros.hpp>

struct NFA {
    struct Transition {
        enum struct Type { CHAR, EPSILON, DOT };

        u32 to;
        Type type;
        std::optional<char> value;

        Transition (u32 to, Type type, std::optional<char> value = std::nullopt)
        : to (to), type (type), value (value) {
        }
    };

    u32 start;
    u32 accept;
    std::unordered_map<u32, std::vector<Transition>> transitions;

    static inline u32 get_id () {
        static u32 id = 0;
        id            = id % (std::numeric_limits<u32>::max () - 1);
        return id++;
    }

    NFA (u32 start, u32 accept) : start (start), accept (accept) {
    }

    NFA (u32 start, u32 accept, Transition::Type type, std::optional<char> value = std::nullopt)
    : start (start), accept (accept) {
        transitions[start].emplace_back (accept, type, value);
    }

    static NFA build (const std::shared_ptr<ASTNode>& node);

    static NFA build_union (const NFA&, const NFA&);
    static NFA build_concat (const NFA&, const NFA&);
    static NFA build_star (const NFA&);
    static NFA build_opt (const NFA&);
    static NFA build_plus (const NFA&);

    std::set<u32> epsilon_closure (std::set<u32> states) const;
    std::set<u32> move (std::set<u32> states, std::optional<char> symbol = std::nullopt) const;
};

std::ostream& operator<< (std::ostream& output, NFA::Transition::Type type);

#endif // TREX_NFA