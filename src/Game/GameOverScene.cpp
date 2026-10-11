#include "Game/GameOverScene.hpp"

#include <memory>
#include <string>

#include "Engine/SceneManager.hpp"
#include "Game/GameScene.hpp"
#include "Game/TitleScene.hpp"

GameOverScene::GameOverScene( SceneManager *manager, bool victory, int score) : Scene(manager, "GameOverScene"),
    victory(victory),
    score(score) {}

void GameOverScene::HandleEvent(const SDL_Event &event) {
    if (event.type != SDL_EVENT_KEY_DOWN) return;

    if (event.key.scancode == SDL_SCANCODE_R)
        m_manager->ChangeScene(std::make_unique<GameScene>(m_manager));

    if (event.key.scancode == SDL_SCANCODE_M ||
        event.key.scancode == SDL_SCANCODE_ESCAPE)
        m_manager->ChangeScene(std::make_unique<TitleScene>(m_manager));
}

void GameOverScene::Render(SDL_Renderer *renderer) {
    if (victory)
        SDL_SetRenderDrawColor(renderer, 20, 80, 40, 255);
    else
        SDL_SetRenderDrawColor(renderer, 80, 20, 25, 255);

    SDL_RenderClear(renderer);

    std::string title =
        std::string(victory ? "VICTORIA" : "DERROTA") +
        " - Puntos: " + std::to_string(score);

    SDL_SetWindowTitle(
        SDL_GetRenderWindow(renderer),
        title.c_str()
    );

    SDL_FRect box{280, 170, 400, 150};

    SDL_SetRenderDrawColor(
        renderer,
        victory ? 60 : 190,
        victory ? 200 : 45,
        victory ? 100 : 55,
        255
    );

    SDL_RenderFillRect(renderer, &box);
}