#pragma once

#include <memory>
#include <vector>
#include <SDL3/SDL.h>

class Scene;

class SceneManager {
    enum class Action {
        None,
        Change,
        Push,
        Pop
    };

    std::vector<std::unique_ptr<Scene>> scenes;

    Action pending{Action::None};
    std::unique_ptr<Scene> nextScene;

public:
    ~SceneManager();

    void ChangeScene(std::unique_ptr<Scene> scene);
    void PushScene(std::unique_ptr<Scene> scene);
    void PopScene();

    void ProcessPendingChanges();

    void HandleEvent(const SDL_Event &event);
    void Update(float dt);
    void Render(SDL_Renderer *renderer);

    void Clear();
    bool HasScene() const;
};