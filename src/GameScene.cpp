#include "GameScene.hpp"

#include <memory>

#include "SceneManager.hpp"
#include "PauseScene.hpp"
#include "GameOverScene.hpp"

#include "TransformComponent.hpp"
#include "RectRenderComponent.hpp"
#include "PlayerControllerComponent.hpp"
#include "ColliderComponent.hpp"
#include "BallComponent.hpp"
#include "Vector2.hpp"

GameScene::GameScene(SceneManager *manager): Scene(manager, "GameScene"), m_collisionManager(&m_entities){

}

void GameScene::Init(){
    SDL_Log("Entrando a GameScene");

    //Limpiamos por seguridad las entidades anteriores
    m_entities.clear();

    m_physicsAccumulator = 0.0f;
    m_debugDraw = false;

    //JUGADOR
    auto player = std::make_unique<GameObject>("Player");

    player->AddComponent<TransformComponent>(
        Vector2{440.0f, 240.0f},
        Vector2{1.0f, 1.0f}
    );

    player->AddComponent<RectRenderComponent>(
        Vector2{60.0f, 60.0f},
        SDL_Color{60, 180, 100, 255}
    );
player->AddComponent<ColliderComponent>(
    Vector2{60.0f, 60.0f}
);


player-> AddComponent<PlayerControllerComponent>(
300.0f,
false   

);

m_entities.push_back(std::move(player));

//OBSTACULO
auto obstacle = std::make_unique<GameObject>("Obstacle");

obstacle->AddComponent<TransformComponent>(
    Vector2{180.0f, 140.0f},
    Vector2 {1.0f, 1.0f}
);

obstacle->AddComponent<RectRenderComponent>(
    Vector2{80.0f, 80.0f},
    SDL_Color{220, 70, 70, 255}
);

obstacle->AddComponent<ColliderComponent>(
    Vector2{80.0f, 80.0f}
);

m_entities.push_back(std::move(obstacle));

//PELOTA
auto ball = std::make_unique<GameObject>("Ball");

ball->AddComponent<TransformComponent>(
    Vector2{468.0f, 80.0f},
    Vector2{1.0f, 1.0f}
);

ball->AddComponent<RectRenderComponent>(
    Vector2{24.0f, 24.0f},
    SDL_Color{240, 210, 60, 255}
);

ball->AddComponent<ColliderComponent>(
    Vector2{24.0f, 24.0f}
);

ball->AddComponent<BallComponent>(
    Vector2{220.0f, 180.0f}
);

m_entities.push_back(std::move(ball));
}


void GameScene::Exit(){

    SDL_Log("Saliendo de GameScene");
    m_entities.clear();

}

//EVENTOS
void GameScene::HandleEvent(const SDL_Event &event){

    if(event.type != SDL_EVENT_KEY_DOWN){
        return;
    }

    //F1 = Activar y desactivar contorno de colision

    if(event.key.scancode == SDL_SCANCODE_F1){
        m_debugDraw = !m_debugDraw;

        SDL_Log("Debug Draw: %s", m_debugDraw ? "ACTIVADO" : "DESACTIVADO" );
        return;
    }

    //P o Escape = Pausa

    if(event.key.scancode == SDL_SCANCODE_P || event.key.scancode == SDL_SCANCODE_ESCAPE)
    {
        m_manager->PushScene(
            std::make_unique<PauseScene>(m_manager)
    );
    return;
    }

    //G = GAME OVER para probar
    if(event.key.scancode == SDL_SCANCODE_G){
        m_manager->ChangeScene(std::make_unique<GameOverScene>(m_manager));
        return;
    }
}

//UPDATE

void GameScene::Update(float dt){

    constexpr float FIXED_TIMESTEP = 1.0f/60.0f;
   m_physicsAccumulator += dt;

    while(m_physicsAccumulator >= FIXED_TIMESTEP){

        //Actualizamos todas las entidades
        for(auto &entity : m_entities){
            if(entity && entity->IsActive()){
                entity->Update(FIXED_TIMESTEP);
            }
        }

        //Despues revisamos las colisiones
        m_collisionManager.CheckCollisions();

    m_physicsAccumulator -= FIXED_TIMESTEP;

    }
}

//RENDER
void GameScene::Render(SDL_Renderer *renderer){

    //Fondo de la escena de juego
    SDL_SetRenderDrawColor(
        renderer,
        25,
        25,
        30,
        255
     );
     SDL_RenderClear(renderer);


     //Dibujar entidades
     for(auto &entity : m_entities){
        if(entity && entity->IsActive()){
            entity->Render(renderer);
        }
     }

     //Dibujar cajas de colision si F1 esta activo
     if(m_debugDraw)
     {
        for(auto &entity : m_entities){
            if(!entity){
                continue;
            }
if(auto *collider = entity->GetComponent<ColliderComponent>()){
    collider->RenderDebug(renderer);
}

        }
     }
}