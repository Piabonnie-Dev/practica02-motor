#pragma once

#include <cmath>
#include<SDL3/SDL.h>

#include "Component.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"
#include "ColliderComponent.hpp"
#include "Vector2.hpp"

class BallComponent : public Component {
public:

Vector2 velocity {220.0f, 180.0f };

BallComponent() = default;
explicit BallComponent(Vector2 vel) : velocity(vel)
{}

void Update(float dt)override {
if(!owner)
return;

auto *transform = owner->GetComponent<TransformComponent>();

auto *collider = owner->GetComponent<ColliderComponent>();

if(!transform || !collider)
return;

transform->Translate(velocity * dt);
SDL_FRect bounds = collider->GetWorldBounds();

//Izquierda
if(bounds.x <= 0.0f){
    transform->position.x =- collider->offset.x;
    velocity.x = std::abs(velocity.x);
}

//Derecha
if(bounds.x + bounds.w >= 960.0f)
{
    transform->position.x = 960.0f - bounds.w - collider->offset.x;
    velocity.x =- std::abs(velocity.x);
}

//Arriba

if(bounds.y <= 0.0f)
{
transform->position.y =
-collider->offset.y;

velocity.y = std::abs(velocity.y);

}
//Abajo
if(bounds.y + bounds.h >= 540.0f)
{
transform->position.y = 
540.0f - bounds.h - collider->offset.y;

velocity.y = -std::abs(velocity.y);

}

}

void OnCollision(GameObject *other) override
{
    if(!owner || !other)
    return;

    auto *myCollider = owner->GetComponent<ColliderComponent>();
    auto *otherCollider = other->GetComponent<ColliderComponent>();

    if(!myCollider || !otherCollider)
    return;

    SDL_Log("Collision: %s con %s", 
    owner->GetTag().c_str(),
    owner->GetTag().c_str());

    //Un trigger detecta pero no provoca rebote
    if(otherCollider->is_trigger)
    return;

    SDL_FRect myBounds = myCollider->GetWorldBounds();

    SDL_FRect otherBounds = otherCollider->GetWorldBounds();

    //Centros geometricos
    float myCenterX =
    myBounds.x + myBounds.w * 0.5f;

    float myCenterY = 
    myBounds.y + myBounds.h * 0.5f;

    float otherCenterX = 
    otherBounds.x + otherBounds.w * 0.5f;

    float otherCenterY =
    otherBounds.y + otherBounds.h * 0.5f;

    float dx= myCenterX - otherCenterX;

    float dy = myCenterY - otherCenterY;

//Determinamos el eje principal del imapcto
if(std::abs(dx) > std::abs(dy))
{
//Impacto lateral
velocity.x=(dx>0.0f) ? std::abs(velocity.x) : -std::abs(velocity.x);

}
else {
// Impacto vertical
            velocity.y =
                (dy > 0.0f)
                    ? std::abs(velocity.y)
                    : -std::abs(velocity.y);

}

}


};