#include "Game/TitleScene.hpp"

#include <memory>

#include "Engine/SceneManager.hpp"
#include "Game/GameScene.hpp"

TitleScene::TitleScene(SceneManager *manager)
    : Scene(manager, "TitleScene") {}

  void TitleScene::HandleEvent(const SDL_Event &event) {  
    if (event.type == SDL_EVENT_KEY_DOWN &&
         (event.key.scancode == SDL_SCANCODE_SPACE ||
    event.key.scancode == SDL_SCANCODE_RETURN))
        m_manager->ChangeScene(std::make_unique<GameScene>(m_manager));
}

void TitleScene::Render(SDL_Renderer *renderer) {
   SDL_SetWindowTitle(
    SDL_GetRenderWindow(renderer),
    "Space Invaders - SPACE/ENTER: iniciar - A/D: mover - SPACE: disparar"
);
    SDL_SetRenderDrawColor(renderer, 20, 25, 45, 255);
    SDL_RenderClear(renderer);

    SDL_FRect title{280, 175, 400, 110};
    SDL_SetRenderDrawColor(renderer, 80, 110, 220, 255);
    SDL_RenderFillRect(renderer, &title);

    SDL_FRect start{380, 360, 200, 55};
    SDL_SetRenderDrawColor(renderer, 50, 200, 120, 255);
    SDL_RenderFillRect(renderer, &start);
}