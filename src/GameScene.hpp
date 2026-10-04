#pragma once

#include "Scene.hpp"
#include "CollisionManager.hpp"

class GameScene : public Scene
{
public:
    explicit GameScene(SceneManager *manager);

    void Init() override;
    void Exit() override;

    void HandleEvent(const SDL_Event &event) override;
    void Update(float dt) override;
    void Render(SDL_Renderer *renderer) override;

private:
    // Gestor de colisiones de esta escena
    CollisionManager m_collisionManager;

    // Acumulador para física a paso fijo
    float m_physicsAccumulator{0.0f};

    // Mostrar u ocultar cajas de colisión
    bool m_debugDraw{false};
};