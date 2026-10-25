#pragma once

// Incluimos nuestra clase base Scene.
// ResourceDemoScene heredara sus funciones y entidades.
#include "Engine/Scene.hpp"

// Incluimos el administrador de texturas que creamos.
// Lo utilizaremos para cargar y compartir las imagenes.
#include "Engine/ResourceManager.hpp"

class GameObject;

//Escena que demostrara el funcionamiento de FlyWeight
class ResourceDemoScene : public Scene {
    private:

    ResourceManager m_resources;

    GameObject* m_player{nullptr};

    int m_nextEnemyIndex{0};

    float m_playerSpeed{250.0f};

    void SpawnEnemies(int amount);

    void PrintMetrics() const;

    void ResetCache();

    void TriggerDeliberateLeak();

    public:

    ResourceDemoScene(SceneManager* manager,
    SDL_Renderer* renderer);

    void Init() override;

    void Exit() override;

    void HandleEvent(const SDL_Event& event) override;

    void Update(float dt) override;

    void Render(SDL_Renderer* renderer) override;

};