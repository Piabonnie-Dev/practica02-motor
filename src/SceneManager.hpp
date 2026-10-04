#pragma once

#include <memory>
#include <utility>
#include <vector>

#include <SDL3/SDL.h>

#include "Scene.hpp"

//Operaciones que pueden quedar pendientes hasta un punto seguro
enum class SceneAction{
    None, 
    Change,
    Push,
    Pop,
    Clear
};

class SceneManager {

    public:
    SceneManager() = default;
    ~SceneManager(){
        Clear();
    }

    SceneManager (const SceneManager &) = delete;
SceneManager &operator= (const SceneManager &) = delete;

//SOLICITUDES DE TRANSICION

void ChangeScene(std::unique_ptr<Scene> newScene){
     m_pendingAction = SceneAction::Change;
        m_pendingScene = std::move(newScene);
}

void PopScene(){
    m_pendingAction = SceneAction::Pop;
}
void PushScene(std::unique_ptr<Scene> newScene)
{
    m_pendingAction = SceneAction::Push;
    m_pendingScene = std::move(newScene);
}


//Procesar cambios en un punto seguro
void ProcessPendingChanges(){
    if(m_pendingAction == SceneAction::None){
        return;
    }

    switch (m_pendingAction)
    {
        case SceneAction::Change:{
            //Destruir la escena actual
            if(!m_scenes.empty()){

                m_scenes.back()->Exit();
                m_scenes.pop_back();
            }
//Agregar la nueva escena
            if(m_pendingScene){
                m_scenes.push_back(std::move(m_pendingScene));
                m_scenes.back()->Init();
            }
            break;
        }

        case SceneAction::Push:{

            // Conservamos la escena anterior
            // y colocamos una nueva encima
            if (m_pendingScene)
            {
                m_scenes.push_back(std::move(m_pendingScene));
                m_scenes.back()->Init();
            }

            break;
        }

        case SceneAction::Pop:{
            if(!m_scenes.empty()){
                m_scenes.back()->Exit();
                m_scenes.pop_back();
            }

            break;
        }

        case SceneAction::Clear:
        {
            Clear();
            break;

        }

        case SceneAction::None:
        default:
        break;
    }
    //Reestablecemos la transicion pendiente
    m_pendingAction=SceneAction::None;
    m_pendingScene.reset();
}
//CICLO PRINCIPAL
void HandleEvent(const SDL_Event &event){
    if(!m_scenes.empty()){
        //Unicamente la escena superior recibe input
        m_scenes.back()->HandleEvent(event);
    }
}
void Update(float dt){
    if(!m_scenes.empty()){
        //Unicamente actualiza la escena superior
        m_scenes.back()->Update(dt);
    }
}

void Render(SDL_Renderer *renderer){
    //Renderizamos todas las escenas
     // desde el fondo hasta la parte superior.
        //
        // Esto permitirá ver GameScene debajo de PauseScene.
        for (auto &scene : m_scenes)
        {
            if (scene)
            {
                scene->Render(renderer);
            }
        }
}

//LIMPIEZA
void Clear(){
    while(!m_scenes.empty()){
        m_scenes.back()->Exit();
        m_scenes.pop_back();
    }
}

bool HasScene() const{
    return !m_scenes.empty();

}

std::size_t GetSceneCount() const{
    return m_scenes.size();
}

private:
//Pila de escenas
std::vector<std::unique_ptr<Scene>> m_scenes;

//Cambio solicitado pero todavia no ejecutado
SceneAction m_pendingAction{SceneAction::None};

//Nueva ESCENAS que espera entrar a la pila
std::unique_ptr<Scene> m_pendingScene{nullptr};

};