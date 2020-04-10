#ifndef PTE_ACTIVITIES_INTROACTIVITY_HPP
#   define PTE_ACTIVITIES_INTROACTIVITY_HPP

#   include <Tilemap.hpp>

#   include "pte/activities/BaseActivity.hpp"
#   include "sprites.h"


namespace pte::activities
{
    // Initial Activity.
    class IntroActivity:
        public BaseActivity<IntroActivity>
    {
    public: // Constructors.
        IntroActivity() noexcept;
    
    
    public: // Lifecycle.
        void update() noexcept;
        
    
    private:
        Tilemap _tilemap;
        
        struct
        {
            int x = 0;
            int y = 0;
            int recolor = 0;
            Sprite animator;
        } _player;
    };
}


#endif // PTE_ACTIVITIES_INTROACTIVITY_HPP