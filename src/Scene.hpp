#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <SDL3/SDL.h>
#include "GameObject.hpp"

// Declaracion adelantada para evitar dependencias circulares
class SceneManager;

class Scene
{
    public: 
    Scene(SceneManager *manager, std::string name)
    : m_manager(manager),
    m_name(std::move(name))
    {}


    virtual ~Scene() = default;

    //Evitamos copias pq las escenas tienen unique_ptr
    Scene(const Scene &) = delete;
    Scene &operator = (const Scene &) = delete;

    //Permitimos movimiento
    Scene(Scene &&) =default;
    Scene &operator=(Scene &&) = default;

    //Ciclo de vida de una escena
    virtual void Init(){
    }
    virtual void Exit(){}

    virtual void HandleEvent(const SDL_Event &event) = 0;

    virtual void Update(float dt){
for(auto &entity : m_entities){

    if(entity){
        entity->Update(dt);
    }
     }

    }
virtual void Render(SDL_Renderer *renderer)
{
    for (auto &entity : m_entities)
    {
        if (entity)
        {
            entity->Render(renderer);
        }
    }
}



  //Crea un GameObject perteneciente exclusivamente a esta escena
  GameObject *CreateGameObject(const std::string &tag){
    auto gameObject = std::make_unique<GameObject>(tag);

    GameObject *ptr = gameObject.get();

    m_entities.push_back(std::move(gameObject));

    return ptr;
  }  

  std::vector<std::unique_ptr<GameObject>> &GetEntities(){
    return m_entities;
  }
const std::string &GetName() const{
    return m_name;
}

protected:
SceneManager *m_manager{nullptr};

std::vector<std::unique_ptr<GameObject>> m_entities;

std::string m_name;

};