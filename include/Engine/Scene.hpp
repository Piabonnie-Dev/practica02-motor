#pragma once

#include <memory>
#include <string>
#include <vector>
#include <SDL3/SDL.h>

class GameObject;
class SceneManager;

class Scene {
protected:
    SceneManager *m_manager;
    std::vector<std::unique_ptr<GameObject>> m_entities;
    std::string m_name;

public:
    Scene(SceneManager *manager, std::string name);
    virtual ~Scene();

    virtual void Init();
    virtual void Exit();

    virtual void HandleEvent(const SDL_Event &event) = 0;

    virtual void Update(float dt);
    virtual void FixedUpdate(float dt);
    virtual void Render(SDL_Renderer *renderer);
};