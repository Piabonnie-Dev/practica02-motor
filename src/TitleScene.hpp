#pragma once
#include "Scene.hpp"

class TitleScene : public Scene{


    public:
    explicit TitleScene(SceneManager *manager);

    void Init() override;
    void Exit() override;

    void HandleEvent(const SDL_Event &event) override;
    void Update(float dt) override;
    void Render(SDL_Renderer *renderer) override;
};