#pragma once
#include <SDL3/SDL.h>

#include "Engine/Component.hpp"
#include "Math/Vector2.hpp"

class ColliderComponent : public Component
{
public:
    // Posicion local respecto al Transform
    Vector2 offset{};

    // Tamaño base de la caja
    Vector2 size{60, 60};

    // Si es trigger, detecta pero no debe bloquear
    bool is_trigger{false};

    // Estado de colision en el frame actual
    bool is_colliding{false};

    ColliderComponent() = default;

     ColliderComponent(
        Vector2 size,
        Vector2 offset = {},
        bool trigger = false
    );
SDL_FRect GetWorldBounds() const;
void RenderDebug(SDL_Renderer *renderer);

};