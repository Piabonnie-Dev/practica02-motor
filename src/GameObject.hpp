#pragma once


#include <vector>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <SDL3/SDL.h>

#include "Component.hpp"

class GameObject
{
private: 
std::vector<std::unique_ptr<Component>> m_components; //
std::string m_tag{"GameObject"}; // 
bool m_active{true}; // estado activo del objeto, en este caso en true. Si fuera false, el objeto no se actualizaria ni se renderizaria.

public: 

GameObject() = default; //destructor virtual por defecto, que permite la destruccion correcta de los objetos derivados de GameObject.
explicit GameObject(std::string tag): m_tag(std::move(tag)){}
~GameObject() =default; // destructor virtual por defecto, que permite la destruccion correcta de los objetos derivados de GameObject.

//Desahbilitar copia para garantizar la propiedad unique_ptr
GameObject(const GameObject&) = delete; // deshabilita el constructor de copia, evitando la copia de objetos GameObject.
GameObject& operator=(const GameObject&) = delete;

//Habilitar movimiento en memoria 
GameObject(GameObject &&) noexcept = default;
 GameObject &operator=(GameObject &&) noexcept = default;

 //Identificacion y estado
 const std::string &GetTag() const { return m_tag; }
 void SetTag(std::string tag) {m_tag = std::move(tag); }

 bool IsActive() const { return m_active;}
 void SetActive(bool active ) {m_active = active;}
//Para armar componentes con reenvio perfecto
template <typename T, typename... Args>
T *AddComponent(Args &&... args)
{

static_assert(std::is_base_of_v<Component, T>, "T debe derivar de Component");

auto component = std::make_unique<T>(std::forward<Args>(args)...);
component->owner = this;
component->Init();
T*ptr = component.get();
m_components.push_back(std::move(component));
return ptr;
}
//consulta de componentes
template <typename T>
T * GetComponent() const {
   static_assert(  std::is_base_of_v<Component, T>, "T debe derivar de Component");

    for (const auto &component: m_components){
        if (auto casted = dynamic_cast<T *>(component.get()))
        {
            return casted;
        }
        
    }
    return nullptr;

}

template <typename T>
bool HasComponent() const{
    return GetComponent <T>() != nullptr;

}

//Propagacion del ciclo de vida a todos los componentes hijos

void Update(float dt)
{
    if(!m_active) return;
    for (auto &component : m_components)
    {
        component ->Update(dt);
    }
}

void Render(SDL_Renderer * renderer){
    if(!m_active) return;
    for(auto &component : m_components){
        component->Render(renderer);
    }
}

};