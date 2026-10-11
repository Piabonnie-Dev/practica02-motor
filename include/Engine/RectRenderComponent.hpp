#pragma once
#include <SDL3/SDL.h>

#include "Engine/Component.hpp"
#include "Math/Vector2.hpp"

class RectRenderComponent : public Component{

    public : 
    Vector2 size;
    SDL_Color color;

    
    RectRenderComponent(Vector2 size, SDL_Color color);

    void Render(SDL_Renderer *renderer) override;

    };
