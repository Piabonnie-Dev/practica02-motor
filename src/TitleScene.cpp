#include "TitleScene.hpp"

#include <memory>

#include "SceneManager.hpp"
#include "GameScene.hpp"

TitleScene::TitleScene(SceneManager *manager) : Scene(manager, "TitleScene"){

}

void TitleScene::Init(){
    SDL_Log("Entrando a TitleScene");
}

void TitleScene::Exit(){
    SDL_Log("Saliendo de TitleScene");
}
void TitleScene::HandleEvent(const SDL_Event &event){
    if(event.type != SDL_EVENT_KEY_DOWN){
        return;

    }

    if(event.key.scancode == SDL_SCANCODE_SPACE || event.key.scancode == SDL_SCANCODE_RETURN){
        m_manager->ChangeScene(std::make_unique<GameScene>(m_manager));

    }
}

void TitleScene::Update(float dt){
    //TitleScene no necesita actualizar entidades por ahora.
    (void)dt;
}

void TitleScene::Render(SDL_Renderer *renderer){
    //Fondo azul oscuro
    SDL_SetRenderDrawColor(renderer, 20, 25, 45, 255);
    SDL_RenderClear(renderer);

    //CARTEL CENTRAL / TITULO

    SDL_FRect titleRect{
        280.0f,
        175.0f,
        400.0f,
        110.0f
    };
    SDL_SetRenderDrawColor(renderer, 80, 110, 220, 255);
    SDL_RenderFillRect(renderer, &titleRect);

    //Decoracion interior del titulo
    SDL_FRect innerRect{
        300.0f,
        195.0f,
        360.0f,
70.0f
    };

    SDL_SetRenderDrawColor(renderer, 30, 40, 75, 255);
    SDL_RenderFillRect(renderer, &innerRect);

    // -------------------------------------------------
    // BOTÓN PARA COMENZAR
    // -------------------------------------------------

    SDL_FRect startButton{
        380.0f,
        360.0f,
        200.0f,
        55.0f
    };

    SDL_SetRenderDrawColor(renderer, 50, 200, 120, 255);
    SDL_RenderFillRect(renderer, &startButton);

    // Pequeño indicador dentro del botón
    SDL_FRect indicator{
        450.0f,
        375.0f,
        60.0f,
        25.0f
    };

    SDL_SetRenderDrawColor(renderer, 220, 255, 230, 255);
    SDL_RenderFillRect(renderer, &indicator);
}
