#include "Game/PauseScene.hpp"
#include "Engine/SceneManager.hpp"


//Constructor: Recibe el administrador y llama al constructor Scene.
PauseScene::PauseScene(SceneManager *manager)
    : Scene(manager, "PauseScene") {}
//Controla las teclas mientras el juego esta pausado.
void PauseScene::HandleEvent(const SDL_Event &event) {
    if (event.type == SDL_EVENT_KEY_DOWN &&
        (event.key.scancode == SDL_SCANCODE_P ||
         event.key.scancode == SDL_SCANCODE_ESCAPE))
        //Retira la escena superior de la pila.
         m_manager->PopScene();
}

//Dibuja la pantalla de pausa.
void PauseScene::Render(SDL_Renderer *renderer) {
   //Permite dibujar elementos semitransparentes encima de lo que se encuentra en pantalla.
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 175);

    SDL_FRect overlay{0, 0, 960, 540}; //Rectangulo que cubre los pixeles 960x540
    SDL_RenderFillRect(renderer, &overlay);

    SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);
//Aqui se definen las dos barras del simbolo pausa.
    SDL_FRect left{430, 225, 30, 90};
    SDL_FRect right{500, 225, 30, 90};

    SDL_RenderFillRect(renderer, &left); //Dibujamos barra izquierda y derecha
    SDL_RenderFillRect(renderer, &right);
//Reestablecemos el modo de dibujo
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}