#pragma once
#include "Engine/Scene.hpp"

class GameOverScene : public Scene {
    bool victory;
    int score;

public:
    GameOverScene(
        SceneManager *manager,
        bool victory = false,
        int score = 0
    );

    void HandleEvent(const SDL_Event &event) override;
    void Render(SDL_Renderer *renderer) override;
};