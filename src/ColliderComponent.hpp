#pragma once

#include <SDL3/SDL.h>

#include "Component.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"
#include "Vector2.hpp"

class ColliderComponent : public Component
{
public:
    // Posicion local respecto al Transform
    Vector2 offset{0.0f, 0.0f};

    // Tamaño base de la caja
    Vector2 size{60.0f, 60.0f};

    // Si es trigger, detecta pero no debe bloquear
    bool is_trigger{false};

    // Estado de colision en el frame actual
    bool is_colliding{false};

    ColliderComponent() = default;

    explicit ColliderComponent(
        Vector2 sz,
        Vector2 off = Vector2{0.0f, 0.0f},
        bool trigger = false)
        :  offset(off),
         size(sz),
          is_trigger(trigger)
    {
    }

    SDL_FRect GetWorldBounds() const
    {
        // Respaldo si por alguna razon no existe owner
          if (!owner)
        {
            return SDL_FRect{
                offset.x,
            offset.y,
                size.x,
                size.y};
        }

        TransformComponent *transform =
              owner->GetComponent<TransformComponent>();

        // Respaldo si no existe Transform
        if (!transform)
        {
         return SDL_FRect{
                offset.x,
                offset.y,
                size.x,
                size.y};
        }

        return SDL_FRect{
             transform->position.x + offset.x,
            transform->position.y + offset.y,
            size.x * transform->scale.x,
             size.y * transform->scale.y};
    }

    void RenderDebug( SDL_Renderer *renderer)
    {
        SDL_FRect bounds = GetWorldBounds();

        if (is_colliding)
        {
    // Rojo = colision
              SDL_SetRenderDrawColor(
                renderer,
                255,
                50,
                50,
                255);
        }
        else
        {
            // Verde = libre
            SDL_SetRenderDrawColor(
                renderer,
                50,
                255,
                50,
                255);
        }

        // Solo borde, sin rellenar
        SDL_RenderRect(renderer, &bounds);
    }
};