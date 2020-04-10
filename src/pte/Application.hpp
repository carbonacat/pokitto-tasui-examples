#ifndef PTE_APPLICATION_HPP
#   define PTE_APPLICATION_HPP

#   include <variant>

#   include "fmanga/StateMachine.h"
#   include "pte/activities/IntroActivity.hpp"


namespace pte
{
    // Common state for the whole app.
    // It is a static class, no actual instance of it are needed.
    class Application
    {
    public: // Types.
        using Activities = fmanga::StateMachine<activities::IntroActivity>;
        
    
    public: // Lifecycle.
        static void init() noexcept;
        static void update() noexcept
        {
            activities.update();
        }
    
    
    public: // Activities.
        static Activities activities;
    };
    
    
    template<typename ActivityP>
    ActivityP& activities::BaseActivity<ActivityP>::get() noexcept
    {
        return Application::activities.getState<ActivityP>();
    }
}


#endif // PTE_APPLICATION_HPP