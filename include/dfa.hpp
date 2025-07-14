#ifndef TREX_DFA
#define TREX_DFA

#include <macros.hpp>
#include <nfa.hpp>

namespace TREX {

struct DFA {
    static inline uint32_t get_id () {
        static uint32_t id = 0;
        id                 = id % (std::numeric_limits<uint32_t>::max () - 1);
        return id++;
    }

    struct PairHash {
        std::size_t operator() (const std::pair<uint32_t, char>& p) const {
            return std::hash<uint32_t> () (p.first) ^ (std::hash<char> () (p.second) << 1);
        }
    };

    uint32_t start;
    std::unordered_set<uint32_t> accept_states;

    std::unordered_map<std::pair<uint32_t, char>, uint32_t, PairHash> char_transitions;
    std::unordered_map<uint32_t, uint32_t> dot_transitions;


    DFA () = default;

    DFA (uint32_t start) : start (start) {
    }

    static DFA construct (const NFA& alice);
    bool match (const std::string& input) const;
};

} // namespace TREX

#endif // TREX_DFA
