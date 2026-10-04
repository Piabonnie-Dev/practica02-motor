#pragma once

#include "Scene.hpp"

class PauseScene : public Scene{
    public:
    explicit PauseScene(SceneManager *manager);

    void Init() override;
    void Exit() override;

    void HandleEvent(const SDL_Event &event) override;
    void Update(float dt) override;
    void Render(SDL_Renderer *renderer) override;
};