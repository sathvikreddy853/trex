#ifndef TREX_DFA
#define TREX_DFA

#include <macros.hpp>
#include <nfa.hpp>

struct DFA {
    static inline u32 get_id () {
        static u32 id = 0;
        id            = id % (std::numeric_limits<u32>::max () - 1);
        return id++;
    }

    struct PairHash {
        std::size_t operator() (const std::pair<u32, char>& p) const {
            return std::hash<u32> () (p.first) ^ (std::hash<char> () (p.second) << 1);
        }
    };

    u32 start;
    std::unordered_set<u32> accept_states;

    std::unordered_map<std::pair<u32, char>, u32, PairHash> char_transitions;
    std::unordered_map<u32, u32> dot_transitions;


    DFA () = default;

    DFA (u32 start) : start (start) {
    }

    static DFA construct (const NFA& alice);
    bool match (const std::string& input) const;
};

#endif // TREX_DFA