#include "pte/activities/IntroActivity.hpp"

#include <puits_UltimateUtopia.h>
#include <tasui>

#include "maps.h"


namespace pte::activities
{
    // IntroActivity - Constructors.
    
    IntroActivity::IntroActivity() noexcept
    {
        using PUI=Pokitto::UI;
    
        // Loads the tilemap.
        _tilemap.set(gardenPath[0], gardenPath[1], gardenPath+2);
        for(int i=0; i<sizeof(tiles)/(POK_TILE_W*POK_TILE_H); i++)
            _tilemap.setTile(i, POK_TILE_W, POK_TILE_H, tiles+i*POK_TILE_W*POK_TILE_H);
        
        // Setup the player.
        _player.animator.play(tasuiCharacter, TasuiCharacter::idle);
        _player.x = LCDWIDTH / 2 - _player.animator.getFrameWidth() / 2;
        _player.y = LCDHEIGHT / 2 - _player.animator.getFrameHeight() / 2;
        _player.recolor = 0;
        
        // Setup the TASUI
        PUI::setTilesetImage(puits::UltimateUtopia::tileSet);
        PUI::showTileMapSpritesUI();
        PUI::printString("Hi stranger");
    }
    
    
    // IntroActivity - Lifecycle.
    
    void IntroActivity::update() noexcept
    {
        using PB = Pokitto::Buttons;
        
        // Updates the player's state.
        {
            constexpr int speed = 3;
            
            // X movement.
            {
                int oldPlayerX = _player.x;
                
                if (PB::rightBtn())
                    _player.x += speed;
                if (PB::leftBtn())
                    _player.x -= speed;
                
                auto playerTile = gardenPathEnum(_player.x / PROJ_TILE_W, _player.y / PROJ_TILE_H);
                
                if (playerTile == Collide)
                    _player.x = oldPlayerX;
            }
            // Y movement.
            {
                int oldPlayerY = _player.y;
                
                if (PB::upBtn())
                {
                    _player.y -= speed;
                }
                if (PB::downBtn())
                {
                    _player.y += speed;
                }
                
                auto playerTile = gardenPathEnum(_player.x / PROJ_TILE_W, _player.y / PROJ_TILE_H);
                
                if (playerTile == Collide)
                    _player.y = oldPlayerY;
            }
            if (PB::aBtn())
            {
                switch (_player.animator.animation)
                {
                case TasuiCharacter::idle:
                    _player.animator.play(tasuiCharacter, TasuiCharacter::blink);
                    break ;
                case TasuiCharacter::blink:
                    _player.animator.play(tasuiCharacter, TasuiCharacter::wave);
                    break ;
                case TasuiCharacter::wave:
                    _player.animator.play(tasuiCharacter, TasuiCharacter::bow);
                    break ;
                case TasuiCharacter::bow:
                    _player.animator.play(tasuiCharacter, TasuiCharacter::idle);
                    break ;
                }
            }
            
            // Standard tile behavior.
            
            auto tile = gardenPathEnum(_player.x / PROJ_TILE_W, _player.y / PROJ_TILE_H);
        
            if (tile == WalkOnGrass)
                _player.recolor++;
            else
                _player.recolor = 0;
        }
        
        // Renders stuff.
        {
            struct
            {
                int x;
                int y;
            } camera
            {
                _player.x - PROJ_LCDWIDTH / 2,
                _player.y - PROJ_LCDHEIGHT / 2
            };
            constexpr int tasuiCharacterOriginX = 6;
            constexpr int tasuiCharacterOriginY = 6;
            
            _tilemap.draw(-camera.x, -camera.y);
            _player.animator.draw(_player.x - camera.x - tasuiCharacterOriginX,
                                  _player.y - camera.y - tasuiCharacterOriginY,
                                  false, false, _player.recolor);
        }
    }
}