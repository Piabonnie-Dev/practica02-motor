#include "Game/GameScene.hpp"

#include <memory>
#include <cstdlib>
#include <string>

#include "Engine/SceneManager.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/TransformComponent.hpp"
#include "Engine/RectRenderComponent.hpp"

#include "Physics/ColliderComponent.hpp"

#include "Game/PauseScene.hpp"
#include "Game/GameOverScene.hpp"

#include "Game/PlayerComponent.hpp"
#include "Game/ProjectileComponent.hpp"

GameScene::GameScene(SceneManager *manager)
    : Scene(manager, "GameScene"),
      collisions(&m_entities) {}

void GameScene::Init() {
m_entities.clear();
player = nullptr;


    accumulator = 0;
    shootCooldown = 0;
    enemyShootCooldown = 1;
    enemyDirection = 1;
    enemySpeed =100;
std::srand(static_cast<unsigned>(SDL_GetTicks()));

    debug = false;

    auto p = std::make_unique<GameObject>("Player");

    p->AddComponent<TransformComponent>(
        Vector2{450, 470}, Vector2{1, 1});

    p->AddComponent<RectRenderComponent>(
        Vector2{60, 30},
        SDL_Color{60, 220, 100, 255});

    p->AddComponent<ColliderComponent>(
        Vector2{60, 30});

    p->AddComponent<PlayerComponent>(300);

    player = p.get();

    m_entities.push_back(std::move(p));

for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 8; ++col) {
        auto enemy = std::make_unique<GameObject>("Enemy");

        enemy->AddComponent<TransformComponent>(
            Vector2{180.0f + col * 70.0f,
                    70.0f + row * 50.0f},
            Vector2{1, 1});

        enemy->AddComponent<RectRenderComponent>(
            Vector2{50, 30},
            SDL_Color{200, 80, 180, 255});

        enemy->AddComponent<ColliderComponent>(
            Vector2{50, 30});

        m_entities.push_back(std::move(enemy));
    }
}
for (int bunker = 0; bunker < 4; ++bunker) {
    for (int i = 0; i < 6; ++i) {
        auto block = std::make_unique<GameObject>("Bunker");

        block->AddComponent<TransformComponent>(
            Vector2{
                140.0f + bunker * 220.0f + (i % 3) * 18.0f,
                400.0f + (i / 3) * 18.0f
            },
            Vector2{1, 1}
        );

        block->AddComponent<RectRenderComponent>(
            Vector2{16, 16},
            SDL_Color{80, 180, 100, 255}
        );

        block->AddComponent<ColliderComponent>(
            Vector2{16, 16}
        );

        m_entities.push_back(std::move(block));
    }
}


}
//Tecla F1
void GameScene::HandleEvent(const SDL_Event &event) {
    if (event.type != SDL_EVENT_KEY_DOWN) return;

    if (event.key.scancode == SDL_SCANCODE_F1)
        debug = !debug;

    else if (event.key.scancode == SDL_SCANCODE_P ||
            event.key.scancode == SDL_SCANCODE_ESCAPE)
        m_manager->PushScene(
            std::make_unique<PauseScene>(m_manager));

    
}

void GameScene::Update(float dt) {
    constexpr float FIXED_DT = 1.0f / 60.0f;

    shootCooldown -= dt;
    enemyShootCooldown -= dt;

    const bool *keys = SDL_GetKeyboardState(nullptr);

    // Disparo del jugador
    if (player &&
        keys[SDL_SCANCODE_SPACE] &&
        shootCooldown <= 0) {

        auto *t = player->GetComponent<TransformComponent>();

        auto bullet = std::make_unique<GameObject>("PlayerBullet"); //Representación de la bala 

        bullet->AddComponent<TransformComponent>(
            Vector2{t->position.x + 26, t->position.y - 20},
            Vector2{1, 1});

        bullet->AddComponent<RectRenderComponent>(
            Vector2{8, 18},
            SDL_Color{240, 240, 120, 255});

        bullet->AddComponent<ColliderComponent>(
            Vector2{8, 18},
            Vector2{},
            true);

        bullet->AddComponent<ProjectileComponent>();

        m_entities.push_back(std::move(bullet));

        shootCooldown = 0.25f;
    }

    // Disparo enemigo 
    if (enemyShootCooldown <= 0) {
        std::vector<GameObject *> enemies;

        for (auto &e : m_entities)
            if (e->IsActive() && e->GetTag() == "Enemy")
                enemies.push_back(e.get());

        if (!enemies.empty()) {
            auto *enemy = enemies[std::rand() % enemies.size()];
            auto *t = enemy->GetComponent<TransformComponent>();

            auto bullet = std::make_unique<GameObject>("EnemyBullet");

            bullet->AddComponent<TransformComponent>(
                Vector2{t->position.x + 21, t->position.y + 35},
                Vector2{1, 1});

            bullet->AddComponent<RectRenderComponent>(
                Vector2{8, 18}, //tamaño de la bala 
                SDL_Color{240, 80, 80, 255});

            bullet->AddComponent<ColliderComponent>(
                Vector2{8, 18}, //tamaño de la bala
                Vector2{},
                true);

            bullet->AddComponent<ProjectileComponent>(
                Vector2{0, 300});

            m_entities.push_back(std::move(bullet));
        }

        enemyShootCooldown = 1.2f;
    }
// la puntuacion
    accumulator += dt;
int alive = 0;
    while (accumulator >= FIXED_DT) {
        
        bool edge = false;

        for (auto &e : m_entities) {
            if (!e->IsActive() || e->GetTag() != "Enemy")
                continue;

            ++alive;

            auto *t = e->GetComponent<TransformComponent>();

            t->Translate(
                Vector2{enemyDirection * enemySpeed * FIXED_DT, 0});

            if (t->position.x <= 0 ||
                t->position.x + 50 >= 960)
                edge = true;
        }

        if (edge) {
            enemyDirection *= -1;

            for (auto &e : m_entities)
                if (e->IsActive() && e->GetTag() == "Enemy")
                    e->GetComponent<TransformComponent>()
                        ->Translate(Vector2{0, 20});
        }
//el incremento de la velocidad del enemigo
        enemySpeed = 50 + (24 - alive) * 3;

        Scene::FixedUpdate(FIXED_DT);
        collisions.CheckCollisions();

        accumulator -= FIXED_DT;
    }

    Scene::Update(dt);

    std::erase_if(
        m_entities,
        [](const auto &e) {
            return !e->IsActive();
        });

    // Comprobar victoria o derrota
    int enemies = 0;
    bool reachedPlayer = false;

    for (auto &e : m_entities) {
        if (e->GetTag() != "Enemy")
            continue;

        ++enemies;

        auto *t = e->GetComponent<TransformComponent>();

        if (t->position.y + 30 >= 470)
            reachedPlayer = true;
    }

    int score = (24 - enemies) * 100;

    auto *pc = player->GetComponent<PlayerComponent>();
//Si eliminas a todos los enemigos, ganas la partida.
    if (enemies == 0) {
        m_manager->ChangeScene(
            std::make_unique<GameOverScene>(
                m_manager, true, score));
        return;
    }
//si el jugador le llegan los enemigos a su posicion pierde o cuando no tiene vidas
    if (pc->GetLives() <= 0 || reachedPlayer) {
        m_manager->ChangeScene(
            std::make_unique<GameOverScene>(
                m_manager, false, score));
        return;
    }
}

void GameScene::Render(SDL_Renderer *renderer) {
    int enemies = 0;

    for (auto &e : m_entities)
        if (e->IsActive() && e->GetTag() == "Enemy")
            ++enemies;

    int score = (24 - enemies) * 100;

    auto *pc = player->GetComponent<PlayerComponent>();

    std::string title =
        "Space Invaders - Vidas: " +
        std::to_string(pc->GetLives()) +
        " - Puntos: " +
        std::to_string(score);

    SDL_SetWindowTitle(
        SDL_GetRenderWindow(renderer),
        title.c_str()
    );

    SDL_SetRenderDrawColor(renderer, 25, 25, 30, 255);
    SDL_RenderClear(renderer);

    Scene::Render(renderer);
//Dibujado de las colisiones al activar F1
    if (debug)
        for (auto &e : m_entities)
            if (auto *c = e->GetComponent<ColliderComponent>())
                c->RenderDebug(renderer);
}