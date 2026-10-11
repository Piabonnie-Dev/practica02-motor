#include "Game/PlayerComponent.hpp"

#include <algorithm>
#include <SDL3/SDL.h>

#include "Engine/GameObject.hpp"
#include "Engine/TransformComponent.hpp"
#include "Math/Vector2.hpp"

PlayerComponent::PlayerComponent(float speed) : speed(speed){

}

void PlayerComponent::FixedUpdate(float dt){
    auto *t = owner->GetComponent<TransformComponent>();
    if(!t) return;

    const bool *keys = SDL_GetKeyboardState(nullptr);

    Vector2 dir{
        float(keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) -
        float(keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]),
        0

    };
if(dir.length_squared())
t->Translate(dir.normalized() * (speed * dt));

t->position.x=std::clamp(t->position.x, 0.0f, 900.0f);

}

void PlayerComponent::OnCollision(GameObject *other) {
    if (other && other->GetTag() == "EnemyBullet") {
        other->SetActive(false);
        --lives;
    }
}

int PlayerComponent::GetLives() const {
    return lives;
}
