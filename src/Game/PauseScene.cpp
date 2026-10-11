#include "Game/PauseScene.hpp"
#include "Engine/SceneManager.hpp"

PauseScene::PauseScene(SceneManager *manager)
    : Scene(manager, "PauseScene") {}

void PauseScene::HandleEvent(const SDL_Event &event) {
    if (event.type == SDL_EVENT_KEY_DOWN &&
        (event.key.scancode == SDL_SCANCODE_P ||
         event.key.scancode == SDL_SCANCODE_ESCAPE))
        m_manager->PopScene();
}

void PauseScene::Render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 175);

    SDL_FRect overlay{0, 0, 960, 540};
    SDL_RenderFillRect(renderer, &overlay);

    SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);

    SDL_FRect left{430, 225, 30, 90};
    SDL_FRect right{500, 225, 30, 90};

    SDL_RenderFillRect(renderer, &left);
    SDL_RenderFillRect(renderer, &right);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}