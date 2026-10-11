#pragma once
#include <SDL3/SDL.h>

class GameObject;

class Component {
public:
    GameObject *owner{nullptr};

    virtual ~Component() = default;

    virtual void Init();
    virtual void Update(float dt);
    virtual void FixedUpdate(float dt);
    virtual void Render(SDL_Renderer *renderer);
    virtual void OnCollision(GameObject *other);
};