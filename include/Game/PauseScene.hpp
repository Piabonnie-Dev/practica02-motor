#pragma once
#include "Engine/Scene.hpp"

class PauseScene : public Scene {
public:
    explicit PauseScene(SceneManager *manager);

    void HandleEvent(const SDL_Event &event) override;
    void Render(SDL_Renderer *renderer) override;
};