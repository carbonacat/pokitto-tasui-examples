#include "pte/Application.hpp"

#include <Pokitto.h>

#include <miloslav.h>


namespace pte
{
    // Application - Lifecycle.
    
    void Application::init() noexcept
    {
        using PD = Pokitto::Display;
        
        PD::loadRGBPalette(miloslav);
    }
    
    Application::Activities Application::activities;
}