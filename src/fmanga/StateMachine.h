#ifndef FMANGA_STATEMACHINE_H
#   define FMANGA_STATEMACHINE_H

#   include <variant>


// Stolen from https://github.com/felipemanga/FemtoIDE/blob/master/projects/P-Type/StateMachine.h.
namespace fmanga
{
    template<class... States>
    class StateMachine {
        std::variant<States...> state;
        void (*_update)(StateMachine *) = [](StateMachine *sm){
            std::get<0>(sm->state).update();
        };
    
    public:
        void update(){ _update(this); }
    
        template<class StateType>
        void setState(){
            _update = [](StateMachine *sm){
                sm->state.template emplace<StateType>();
                sm->_update = [](StateMachine *sm){
                    std::get<StateType>(sm->state).update();
                };
                sm->_update(sm);
            };
        }
    
        template<class StateType>
        StateType &getState() {
            return std::get<StateType>(state);
        }
    };
    
    template <typename Type>
    class State {
    public:
        static Type& get();
    };
}


#endif // FMANGA_STATEMACHINE_H