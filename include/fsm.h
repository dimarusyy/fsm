#pragma once

#include <array>
#include <unordered_map>
#include <functional>
#include <optional>
#include <cctype>

namespace fsm
{
    template <typename T>
    using states_t = std::array<T, 26>;

    using callback_t = std::function<void()>;

    struct state_t
    {
        char state;
        callback_t handler;
    };

    struct transition_t
    {
        bool enabled = false;
        callback_t fallback;

        std::unordered_map<std::string /*input*/, state_t> next;
    };

    struct fsm
    {
        static constexpr char unknown_state = ' ';

        void AddState(char state)
        {
            at(state).enabled = true;
        }

        void AddTransition(char from, char to, std::string input, callback_t handler)
        {
            at(from).next[input] = state_t{to, handler};
        }

        void AddFallback(char from, callback_t handler)
        {
            at(from).fallback = handler;
        }

        void ResetMachine(char state)
        {
            // don't change state if not enabled
            if(at(state).enabled)
                _current_state = std::tolower(state);
        }

        void Step(std::string input)
        {
            auto &state = at(_current_state.value());

            auto next_state_it = state.next.find(input);
            if(next_state_it != state.next.end())
            {
                _current_state = next_state_it->second.state;
                if(next_state_it->second.handler)
                    next_state_it->second.handler();
            }
            else
            {
                // fallback
                if(state.fallback)
                    state.fallback();
            }
        }

        char GetState() const
        {
            return _current_state.value();
        }

    protected:
        transition_t& at(char state)
        {
            return _states[std::tolower(state) - 'a'];
        }

    private:
        std::optional<char> _current_state{ unknown_state };
        states_t<transition_t> _states;
    };
}