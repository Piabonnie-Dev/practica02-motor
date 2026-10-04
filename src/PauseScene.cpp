#include "PauseScene.hpp"

#include "SceneManager.hpp"

PauseScene::PauseScene(SceneManager *manager) : Scene(manager, "PauseScene"){

}
//Inicializacion
void PauseScene::Init(){

    SDL_Log("Entrando a PauseScene");

}

//Salida
void PauseScene::Exit(){
    SDL_Log("Saliendo de PauseScene");
}

void PauseScene::HandleEvent(const SDL_Event &event){

    if(event.type != SDL_EVENT_KEY_DOWN)
    {
        return;
    }

    //P o ESCAPE = salir de pausa
    if(event.key.scancode == SDL_SCANCODE_P ||event.key.scancode == SDL_SCANCODE_ESCAPE){
        m_manager->PopScene();
    }

}


//ACTUALIZACION
void PauseScene::Update(float dt){
//La pausa no actualiza ninguna entidad.
//GameScene queda congelada debajo/
(void)dt;
}

void PauseScene::Render(SDL_Renderer *renderer){

    //No usamos SDL_RenderClear pq queremos conservar GameScene dibujada debajo.
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    //velo oscuro semitransparente
    SDL_SetRenderDrawColor(renderer,
    0,
0,
0,
175
);

SDL_FRect overlay {
    0.0f,
    0.0f,
    960.0f,
    540.0f
};

SDL_RenderFillRect(renderer, &overlay);

//Recuadro central
SDL_FRect pauseBox{
    350.0f, 170.0f, 260.0f, 200.0f
};

SDL_SetRenderDrawColor(
    renderer,
    235,
        210,
        70,
        255

);
SDL_RenderFillRect(renderer, &pauseBox);

//Interior oscuro
SDL_FRect pauseInner {
    370.0f,
    190.0f,
    220.0f,
    160.0f
};
SDL_SetRenderDrawColor(renderer, 35, 35, 40, 245);
SDL_RenderFillRect(renderer, &pauseInner);

// Símbolo de pausa: ||
    SDL_FRect barLeft{
        430.0f,
        225.0f,
        30.0f,
        90.0f
    };

    SDL_FRect barRight{
        500.0f,
        225.0f,
        30.0f,
        90.0f
    };

    SDL_SetRenderDrawColor(
        renderer,
        245,
        245,
        245,
        255
    );

    SDL_RenderFillRect(renderer, &barLeft);
    SDL_RenderFillRect(renderer, &barRight);

    // Volvemos al modo normal
    SDL_SetRenderDrawBlendMode(
        renderer,
        SDL_BLENDMODE_NONE
    );

}