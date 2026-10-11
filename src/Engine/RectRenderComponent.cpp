#include "Engine/RectRenderComponent.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/TransformComponent.hpp"

RectRenderComponent::RectRenderComponent(Vector2 size, SDL_Color color): size(size), color(color){}

void RectRenderComponent::Render(SDL_Renderer *renderer){
    auto *t = owner->GetComponent<TransformComponent>();
    if(!t) return;

    SDL_FRect rect{
        t->position.x,
        t->position.y,
        size.x * t->scale.x,
        size.y * t->scale.y
    };

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}