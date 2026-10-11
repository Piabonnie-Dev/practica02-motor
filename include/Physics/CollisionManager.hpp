#pragma once

#include <memory>
#include <vector>
#include <SDL3/SDL.h>

class GameObject;

class CollisionManager {
std::vector<std::unique_ptr<GameObject>> *entities;

static bool CheckAABB(
    const SDL_FRect &a,
    const SDL_FRect &b
);

public:
explicit CollisionManager(
    std::vector<std::unique_ptr<GameObject>> *entities
);

void CheckCollisions();
};