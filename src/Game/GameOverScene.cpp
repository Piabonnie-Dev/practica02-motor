#include "Game/GameOverScene.hpp"

#include <memory>
#include <string>

#include "Engine/SceneManager.hpp"
#include "Game/GameScene.hpp"
#include "Game/TitleScene.hpp"

//Constructor de la pantalla game over
//Manager: administra escenas
//Victory: true si gano, false si perdio.
//Score: Puntuacion final

GameOverScene::GameOverScene( SceneManager *manager, bool victory, int score) : Scene(manager, "GameOverScene"),
    victory(victory),
    score(score) {}

    //Recibe las pulsaciones del teclado.
void GameOverScene::HandleEvent(const SDL_Event &event) {
    if (event.type != SDL_EVENT_KEY_DOWN) return;

    if (event.key.scancode == SDL_SCANCODE_R)
        m_manager->ChangeScene(std::make_unique<GameScene>(m_manager));

    if (event.key.scancode == SDL_SCANCODE_M ||
        event.key.scancode == SDL_SCANCODE_ESCAPE)
        m_manager->ChangeScene(std::make_unique<TitleScene>(m_manager));
}
//Metodo encargado de dibujar el resultado.

void GameOverScene::Render(SDL_Renderer *renderer) {
    if (victory) //Si gana fondo verde
        SDL_SetRenderDrawColor(renderer, 20, 80, 40, 255);
    else  //Si pierde fondo rojo
        SDL_SetRenderDrawColor(renderer, 80, 20, 25, 255);

    SDL_RenderClear(renderer);
//Se construye el titulo de la ventana
    std::string title =
        std::string(victory ? "VICTORIA" : "DERROTA") +
        " - Puntos: " + std::to_string(score);

        //Modificamos el titulo de la ventana
    SDL_SetWindowTitle(
        SDL_GetRenderWindow(renderer),
        title.c_str()
    );
//Creamos un rectanculo central
    SDL_FRect box{280, 170, 400, 150};

    SDL_SetRenderDrawColor(
        renderer,
        victory ? 60 : 190,
        victory ? 200 : 45,
        victory ? 100 : 55,
        255
    );
//Dibujamos el rectangulo del resultado.
    SDL_RenderFillRect(renderer, &box);
}