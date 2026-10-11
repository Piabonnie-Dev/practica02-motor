#pragma once

#include "Engine/Scene.hpp"
#include "Physics/CollisionManager.hpp"

class GameObject;

class GameScene : public Scene {
    CollisionManager collisions;

    GameObject *player{nullptr};

    float accumulator{0};
    float shootCooldown{0};
    float enemyShootCooldown{1};

    float enemyDirection{1};
    float enemySpeed{50};
    

    bool debug{false};

public:
    explicit GameScene(SceneManager *manager);

    void Init() override;
    void HandleEvent(const SDL_Event &event) override;
    void Update(float dt) override;
    void Render(SDL_Renderer *renderer) override;
};