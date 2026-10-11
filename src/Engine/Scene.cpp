#include "Engine/Scene.hpp"
#include <utility>

#include "Engine/GameObject.hpp"

Scene::Scene(SceneManager *manager, std::string name): m_manager(manager), m_name(std::move(name)){}

Scene::~Scene() = default;
void Scene::Init() {}
void Scene::Exit() {}
void Scene::Update(float dt){
    for (auto &e : m_entities)
        if (e) e->Update(dt);
}

void Scene::FixedUpdate(float dt){
    for(auto &e : m_entities)
    if(e) e->FixedUpdate(dt);
}

void Scene::Render(SDL_Renderer *renderer){
    for (auto &e : m_entities)
    if(e) e->Render(renderer);
}