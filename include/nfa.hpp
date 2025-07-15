#ifndef TREX_NFA
#define TREX_NFA

#include <ast.hpp>
#include <macros.hpp>

namespace trex {

struct NFA {
    struct Transition {
        enum struct Type { CHAR, EPSILON, DOT };

        uint32_t to;
        Type type;
        std::optional<char> value;

        Transition (uint32_t to, Type type, std::optional<char> value = std::nullopt)
        : to (to), type (type), value (value) {}
    };

    uint32_t start;
    uint32_t accept;
    std::unordered_map<uint32_t, std::vector<Transition>> transitions;

    static inline uint32_t get_id () {
        static uint32_t id = 0;
        id                 = id % (std::numeric_limits<uint32_t>::max () - 1);
        return id++;
    }

    NFA (uint32_t start, uint32_t accept) : start (start), accept (accept) {}

    NFA (uint32_t start, uint32_t accept, Transition::Type type, std::optional<char> value = std::nullopt)
    : start (start), accept (accept) {
        transitions[start].emplace_back (accept, type, value);
    }

    static NFA build (const std::shared_ptr<ast::Node>& node);

    static NFA build_union (const NFA&, const NFA&);
    static NFA build_concat (const NFA&, const NFA&);
    static NFA build_star (const NFA&);
    static NFA build_opt (const NFA&);
    static NFA build_plus (const NFA&);

    std::set<uint32_t> epsilon_closure (std::set<uint32_t> states) const;
    std::set<uint32_t> move (std::set<uint32_t> states, std::optional<char> symbol = std::nullopt) const;
};

std::ostream& operator<< (std::ostream& output, NFA::Transition::Type type);

} // namespace trex

#endif // TREX_NFA
