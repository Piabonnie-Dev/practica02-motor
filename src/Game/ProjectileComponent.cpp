#include "Game/ProjectileComponent.hpp"

#include "Engine/GameObject.hpp"
#include "Engine/TransformComponent.hpp"

ProjectileComponent::ProjectileComponent(Vector2 velocity)
    : velocity(velocity) {}

void ProjectileComponent::FixedUpdate(float dt) {
    auto *t = owner->GetComponent<TransformComponent>();
    if (!t) return;

    t->Translate(velocity * dt);

    if (t->position.y < -20 || t->position.y > 560)
        owner->SetActive(false);
}
void ProjectileComponent::OnCollision(GameObject *other) {
    if (!other) return;

    const auto &me = owner->GetTag();
    const auto &tag = other->GetTag();

    if (me == "PlayerBullet" &&
        (tag == "Enemy" || tag == "Bunker")) {
        owner->SetActive(false);
        other->SetActive(false);
    }

    if (me == "EnemyBullet" && tag == "Bunker") {
        owner->SetActive(false);
        other->SetActive(false);
    }
}
