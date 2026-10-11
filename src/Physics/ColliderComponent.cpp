#include "Physics/ColliderComponent.hpp"

#include "Engine/GameObject.hpp"
#include "Engine/TransformComponent.hpp"

ColliderComponent::ColliderComponent(
Vector2 size,
Vector2 offset,
bool trigger
) : offset(offset), size(size), is_trigger(trigger){}

SDL_FRect ColliderComponent::GetWorldBounds() const {
    auto *t = owner ? owner->GetComponent<TransformComponent>()
    : nullptr;

    if(!t)
    return { offset.x, offset.y, size.x, size.y};

    return{
        t->position.x + offset.x,
        t->position.y + offset.y,
        size.x * t->scale.x,
        size.y * t->scale.y
    };
}

void ColliderComponent::RenderDebug(SDL_Renderer *renderer){
    SDL_FRect rect = GetWorldBounds();

    SDL_SetRenderDrawColor(
        renderer,
        is_colliding ? 255 : 50,
        is_colliding ? 50:255,
        50,
        255
    
    );
    SDL_RenderRect(renderer, &rect);
}
