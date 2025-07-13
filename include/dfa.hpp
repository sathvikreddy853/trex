#ifndef TREX_DFA
#define TREX_DFA

#include <macros.hpp>
#include <nfa.hpp>

struct DFA {
    struct Transition {
        enum struct Type { CHAR, DOT };

        u32 to;
        Type type;
        std::optional<char> value;

        Transition (u32 to, Type type, std::optional<char> val = std::nullopt)
        : to (to), type (type), value (val) {
        }
    };

    static inline u32 get_id () {
        static u32 id = 0;
        id = id % (std::numeric_limits<u32>::max() - 1);
        return id++;
    }
    

    u32 start;
    std::unordered_set<u32> accept_states;
    std::unordered_map<u32, std::vector<Transition>> transitions;

    DFA () = default;

    DFA (u32 start) : start (start) {
    }

    static DFA construct(const NFA& alice);
    bool match(const std::string& input) const;
};

#endif // TREX_DFA