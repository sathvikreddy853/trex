#include <dfa.hpp>

DFA DFA::construct (const NFA& alice) {
    std::map<std::set<u32>, u32> state_hash;
    std::set<u32> start_state = alice.epsilon_closure ({ alice.start });
    state_hash[start_state]   = get_id ();

    DFA david (state_hash[start_state]);
    std::queue<std::set<u32>> queue;
    queue.push (start_state);

    std::set<char> alphabet;
    for (const auto& [from, transitions] : alice.transitions) {
        for (const auto& [to, type, value] : transitions) {
            if (type == NFA::Transition::Type::CHAR and value.has_value()) {
                alphabet.insert(value.value());
            }
        }
    }

    while (not queue.empty ()) {
        std::set<u32> current = queue.front ();
        queue.pop ();
        u32 curr_id = state_hash[current];

        for (char c = 32; c < 127; c++) {
            std::set<u32> next = alice.epsilon_closure (alice.move (current, c));

            if (next.empty ())
                continue;

            if (not state_hash.count (next)) {
                state_hash[next] = get_id ();
                queue.push (next);
            }

            u32 target = state_hash[next];
            david.transitions[curr_id].emplace_back(target, DFA::Transition::Type::CHAR, c);
        }
    }

    for (const auto& [states, id] : state_hash) {
        if (states.contains (alice.accept)) {
            david.accept_states.insert (id);
        }
    }

    return david;
}

bool DFA::match (const std::string& input) const {
    u32 current = start;

    for (char c : input) {
        bool transitioned = false;
        if (not transitions.contains (current))
            return false;

        for (const auto& [to, type, value] : transitions.at (current)) {
            if (type == Transition::Type::CHAR && value == c) {
                current      = to;
                transitioned = true;
                break;
            } else if (type == Transition::Type::DOT) {
                current      = to;
                transitioned = true;
                break;
            }
        }

        if (not transitioned) {
            return false;
        }
    }

    return accept_states.count (current) > 0;
}
