#include "Engine/SceneManager.hpp"

#include "Engine/Scene.hpp"

SceneManager::~SceneManager() {
    Clear();
}
//ChangeScene reemplaza la escena superior
void SceneManager::ChangeScene(std::unique_ptr<Scene> scene){
    pending = Action::Change;
    nextScene = std::move(scene);
}
// coloca una escena adicional encima de la actual
void SceneManager::PushScene(std::unique_ptr<Scene> scene){
    pending = Action::Push;
    nextScene = std::move(scene);
}
// Retira la pausa y permite regresar a la partida sin reiniciarla. 
void SceneManager::PopScene(){
    pending = Action::Pop;
}
//Aplica los cambios de escena en un momento seguro 
void SceneManager::ProcessPendingChanges(){
    if(pending == Action::None) return;

    if(pending == Action::Change){
        if(!scenes.empty()){
            scenes.back()->Exit();
            scenes.pop_back();

        }
        if(nextScene){
            scenes.push_back(std::move(nextScene));
            scenes.back()->Init();
        }
    }

    else if(pending == Action::Push){
        if(nextScene){
            scenes.push_back(std::move(nextScene));
            scenes.back()->Init();
        }

    }
    else if (pending == Action::Pop) {
        if (!scenes.empty()) {
            scenes.back()->Exit();
            scenes.pop_back();
        }
    }

    pending = Action::None;
    nextScene.reset();
}

void SceneManager::HandleEvent(const SDL_Event &event){
    if(!scenes.empty())
    scenes.back()->HandleEvent(event);
}

void SceneManager::Update(float dt)
{
    if(!scenes.empty())
    scenes.back()->Update(dt);


}
void SceneManager::Render(SDL_Renderer *renderer){
    for (auto &scene : scenes)
    scene->Render(renderer);
}

void SceneManager::Clear(){
    while(!scenes.empty()){
        scenes.back()->Exit();
        scenes.pop_back();
    }
}

bool SceneManager::HasScene() const
{
    return !scenes.empty();
}

