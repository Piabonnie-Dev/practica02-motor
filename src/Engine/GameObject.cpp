#include "Engine/GameObject.hpp"

GameObject::GameObject(std::string tag) : tag(std::move(tag)) {}

const std::string &GameObject::GetTag() const {
    return tag;
}

bool GameObject::IsActive() const{
    return active;
}

void GameObject::SetActive(bool value){
    active = value;
}

void GameObject::Update(float dt){
    if(!active) return;
    for(auto &c : components)
    c->Update(dt);
}

void GameObject::FixedUpdate(float dt){
    if(!active) return;

    for(auto &c : components)
    c->FixedUpdate(dt);
}

void GameObject::Render (SDL_Renderer *renderer){
    if(!active) return;
    for(auto &c : components)
    c->Render(renderer);
}

void GameObject::OnCollision(GameObject *other){
    if(!active) return;

    for(auto &c : components)
    c->OnCollision(other);
}