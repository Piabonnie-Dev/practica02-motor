#pragma once
#include "Engine/Component.hpp"

class PlayerComponent : public Component {
    float speed;
    int lives{3};

public:
    explicit PlayerComponent(float speed = 300);

    void FixedUpdate(float dt) override;
    void OnCollision(GameObject *other) override;

    int GetLives() const;
};