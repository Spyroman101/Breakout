#ifndef __GAMEENTITY_H
#define __GAMEENTITY_H

#include "SDL.h"
#include "SDL_image.h"
namespace SDLFramework {

    class GameEntity {
        GameEntity(SDL_Renderer* renderer);
        virtual ~GameEntity();

        float x, y, width, height;

        virtual void Update(float delta);
        virtual void Render(float delta);

        bool Collides(GameEntity* other);
    protected:
        SDL_Renderer* renderer;


    };
   
}
#endif