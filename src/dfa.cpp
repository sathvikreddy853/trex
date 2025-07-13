#include <dfa.hpp>

DFA DFA::construct (const NFA& alice) {
    std::map<std::set<u32>, u32> state_hash;
    std::set<u32> start_state = alice.epsilon_closure ({ alice.start });
    state_hash[start_state]   = get_id ();

    DFA david (state_hash[start_state]);
    std::queue<std::set<u32>> queue;
    queue.push (start_state);

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
            david.transitions.emplace(std::pair{curr_id, c}, target);
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
        if (not transitions.contains({current, c})) {
            return false;
        } else {
            current = transitions.at({current, c});
        }
    }

    return accept_states.contains (current);
}
