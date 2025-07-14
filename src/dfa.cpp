#include <dfa.hpp>

DFA DFA::construct (const NFA& alice) {
    std::map<std::set<u32>, u32> state_hash;
    std::set<u32> start_state = alice.epsilon_closure ({ alice.start });
    state_hash[start_state]   = get_id ();

    DFA david (state_hash[start_state]);
    std::queue<std::set<u32>> queue;
    queue.push (start_state);

    std::set<char> alphabet;
    for (const auto& [from, trans_list] : alice.transitions) {
        for (const auto& [to, type, value] : trans_list) {
            if (type == NFA::Transition::Type::CHAR && value.has_value ()) {
                alphabet.insert (value.value ());
            }
        }
    }

    while (not queue.empty ()) {
        std::set<u32> current = queue.front ();
        queue.pop ();
        u32 curr_id = state_hash[current];

        for (char c : alphabet) {
            std::set<u32> next =
            alice.epsilon_closure (alice.move (current, c));
            if (next.empty ())
                continue;

            if (not state_hash.count (next)) {
                state_hash[next] = get_id ();
                queue.push (next);
            }

            u32 target = state_hash[next];
            david.char_transitions.emplace (std::pair{ curr_id, c }, target);
        }

        std::set<u32> next = alice.epsilon_closure (alice.move (current));
        if (not next.empty ()) {
            if (not state_hash.contains (next)) {
                state_hash[next] = get_id ();
                queue.push (next);
            }

            u32 target                     = state_hash[next];
            david.dot_transitions[curr_id] = target;
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
        if (char_transitions.contains ({ current, c })) {
            current = char_transitions.at ({ current, c });
        } else if (dot_transitions.contains (current)) {
            current = dot_transitions.at (current);
        } else {
            return false;
        }
    }

    return accept_states.contains (current);
}
