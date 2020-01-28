#include "GameEntity.h"

namespace SDLFramework {

    GameEntity::GameEntity(SDL_Renderer* renderer) {
        this->renderer = renderer;

        x = 0;
        y = 0;
        width = 1;
        height = 1;
    }

    GameEntity::~GameEntity() {
    }

    void GameEntity::Update(float delta) {
    }

    void GameEntity::Render(float delta) {
    }

    bool GameEntity::Collides(GameEntity* other) {
        if (x + width > other->x&& x < other->x + other->width &&
            y + height > other->y&& y < other->y + other->height) {
            return true;
        }
        return false;

}