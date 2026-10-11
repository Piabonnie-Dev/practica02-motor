#pragma once


#include <vector>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>


#include "Engine/Component.hpp"

class GameObject
{
 
std::vector<std::unique_ptr<Component>> components; 
std::string tag;  
bool active{true}; // estado activo del objeto, en este caso en true. Si fuera false, el objeto no se actualizaria ni se renderizaria.

public: 

explicit GameObject(std::string tag = "GameObject");

const std::string &GetTag() const;
bool IsActive() const;
void SetActive(bool value);

void Update(float dt);
void FixedUpdate(float dt);
void Render(SDL_Renderer *renderer);
void OnCollision(GameObject *other);

template<typename T, typename... Args>
T * AddComponent(Args&&... args){
    static_assert(std::is_base_of_v<Component, T>);

    auto component = std::make_unique<T>(
        std::forward<Args>(args)...
    );

    component->owner = this;
    T*ptr = component.get();

    components.push_back(std::move(component));
    ptr->Init();

    return ptr;
}

template<typename T>
T *GetComponent() const {
    for(const auto &component : components)
    if(auto *ptr = dynamic_cast<T *>(component.get()))
return ptr;

return nullptr;
}


};