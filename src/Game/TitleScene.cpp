#include "Game/TitleScene.hpp"

#include <memory>

#include "Engine/SceneManager.hpp"
#include "Game/GameScene.hpp"

//Constructor de TitleScene.
//Recibe un puntero al administrador de escenas.
TitleScene::TitleScene(SceneManager *manager)
    : Scene(manager, "TitleScene") {}
//Metodo que recibe eventos del teclado.
  void TitleScene::HandleEvent(const SDL_Event &event) {  
    if (event.type == SDL_EVENT_KEY_DOWN &&
         (event.key.scancode == SDL_SCANCODE_SPACE ||
    event.key.scancode == SDL_SCANCODE_RETURN))
    //Solicitamos reemplazar el menu por GameScene
        m_manager->ChangeScene(std::make_unique<GameScene>(m_manager));
}
//Metodo encargado de dibujar el menu principal
void TitleScene::Render(SDL_Renderer *renderer) {
   //Obtiene la ventana asociada al render y cambia el texto de su barra de titulo.
    SDL_SetWindowTitle(
    SDL_GetRenderWindow(renderer),
    "Space Invaders - SPACE/ENTER: iniciar - A/D: mover - SPACE: disparar"
);
//Establece el color de dibujo con valores RGBA.
    SDL_SetRenderDrawColor(renderer, 20, 25, 45, 255);
    SDL_RenderClear(renderer); //Limpia la pantalla utilizando ese color.
//Define un rectangulo: (x, y, ancho , alto)
    SDL_FRect title{280, 175, 400, 110};
    SDL_SetRenderDrawColor(renderer, 80, 110, 220, 255); //Color azul del cartel
    SDL_RenderFillRect(renderer, &title);
//Creamos un segundo rectangulo debajo del primero.
    SDL_FRect start{380, 360, 200, 55};
    SDL_SetRenderDrawColor(renderer, 50, 200, 120, 255); //Color verde
    SDL_RenderFillRect(renderer, &start);
}