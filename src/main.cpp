#include <Pokitto.h>

#include "pte/Application.hpp"


int main()
{
    using Application = pte::Application;
    using PC=Pokitto::Core;
    
    PC::begin();
    Application::init();
    while (PC::isRunning())
    {
        if (!PC::update()) 
            continue;
        Application::update();
    }
    
    return 0;
}
