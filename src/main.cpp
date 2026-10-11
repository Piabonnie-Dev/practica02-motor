#define SDL_MAIN_USE_CALLBACKS 1

#include <memory>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Engine/SceneManager.hpp"
#include "Game/TitleScene.hpp"

struct AppState {
    SDL_Window *window{};
    SDL_Renderer *renderer{};
    Uint64 lastTicks{};
    SceneManager scenes;
};

static AppState app;

SDL_AppResult SDL_AppInit(void **state, int, char **) {
    if (!SDL_Init(SDL_INIT_VIDEO))
        return SDL_APP_FAILURE;

    if (!SDL_CreateWindowAndRenderer(
        "Space Invaders",
        960, 540,
        SDL_WINDOW_RESIZABLE,
        &app.window,
        &app.renderer))
        return SDL_APP_FAILURE;

    app.lastTicks = SDL_GetTicks();

    app.scenes.ChangeScene(
        std::make_unique<TitleScene>(&app.scenes));

    app.scenes.ProcessPendingChanges();

    *state = &app;
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *state) {
    auto *app = static_cast<AppState *>(state);

    Uint64 now = SDL_GetTicks();
    float dt = (now - app->lastTicks) / 1000.0f;
    app->lastTicks = now;

    if (dt > 0.05f) dt = 0.05f;

    app->scenes.ProcessPendingChanges();

    if (!app->scenes.HasScene())
        return SDL_APP_SUCCESS;

    app->scenes.Update(dt);
    app->scenes.ProcessPendingChanges();

    app->scenes.Render(app->renderer);
    SDL_RenderPresent(app->renderer);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *state, SDL_Event *event) {
    auto *app = static_cast<AppState *>(state);

    if (event->type == SDL_EVENT_QUIT)
        return SDL_APP_SUCCESS;

    if (app->scenes.HasScene())
        app->scenes.HandleEvent(*event);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *state, SDL_AppResult) {
    auto *app = static_cast<AppState *>(state);

    app->scenes.Clear();
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    SDL_Quit();
}