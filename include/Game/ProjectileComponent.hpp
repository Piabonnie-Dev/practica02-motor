#pragma once

#include "Engine/Component.hpp"
#include "Math/Vector2.hpp"

class ProjectileComponent : public Component {
    Vector2 velocity;

public:
    explicit ProjectileComponent(Vector2 velocity = {0, -500});

    void FixedUpdate(float dt) override;
    void OnCollision(GameObject *other) override;
};