#include "GameOverScene.hpp"

#include <memory>

#include "SceneManager.hpp"
#include "GameScene.hpp"
#include "TitleScene.hpp"

GameOverScene::GameOverScene(SceneManager *manager) : Scene(manager, "GameOverScene"){

}

void GameOverScene::Init(){
    SDL_Log("Entrando a GameOverScene");

}

void GameOverScene::Exit(){
    SDL_Log("Saliendo de GameOverScene");
}
void GameOverScene::HandleEvent(const SDL_Event &event){
    if(event.type != SDL_EVENT_KEY_DOWN){
        return;
    }

    //R = reiniciar juego desde cero
    if(event.key.scancode == SDL_SCANCODE_R)
    {
        m_manager->ChangeScene(std::make_unique<GameScene>(m_manager));
        return;
    }

    //M o ESCAPE = regresar al menu principal
    if(event.key.scancode == SDL_SCANCODE_M || event.key.scancode == SDL_SCANCODE_ESCAPE){
        m_manager->ChangeScene(std::make_unique<TitleScene>(m_manager));
        return;
    } 
}

void GameOverScene::Update(float dt){

    (void)dt;
}

void GameOverScene::Render(SDL_Renderer *renderer){

    //Fondo rojizo
    SDL_SetRenderDrawColor(
        renderer,
        45,
        15,
        20,
        255
    );

    SDL_RenderClear(renderer);

    //Cartel central de Game Over >:)
    SDL_FRect gameOverBox{
280.0f,
145.0f,
400.0f,
150.0f

    };

SDL_SetRenderDrawColor(
        renderer,
        190,
        45,
        55,
        255
    );

    SDL_RenderFillRect(renderer, &gameOverBox);

    SDL_FRect innerBox{
        305.0f,
        170.0f,
        350.0f,
        100.0f
    };

    SDL_SetRenderDrawColor(
        renderer,
        70,
        20,
        25,
        255
    );

    SDL_RenderFillRect(renderer, &innerBox);

    
    // Indicador visual de R = reiniciar
   
    SDL_FRect restartButton{
        300.0f,
        350.0f,
        150.0f,
        60.0f
    };

    SDL_SetRenderDrawColor(
        renderer,
        235,
        195,
        60,
        255
    );

    SDL_RenderFillRect(renderer, &restartButton);

    
    // Indicador visual de M = menú
    

    SDL_FRect menuButton{
        510.0f,
        350.0f,
        150.0f,
        60.0f
    };

    SDL_SetRenderDrawColor(
        renderer,
        60,
        120,
        220,
        255
    );

    SDL_RenderFillRect(renderer, &menuButton);

}