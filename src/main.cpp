#define SDL_MAIN_USE_CALLBACKS 1

#include <memory>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "SceneManager.hpp"
#include "TitleScene.hpp"







struct AppState
{
    SDL_Renderer *renderer{nullptr};
    SDL_Window *window{nullptr};

    // Temporizador para Delta Time
    Uint64 last_ticks{0};

    

   SceneManager sceneManager;
} appstate;


SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error al inicializar SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Sugerir a la plataforma una tasa objetivo de 60 FPS
    SDL_SetHint(SDL_HINT_MAIN_CALLBACK_RATE, "60");

    

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
//Todo este tiempo se me olvido cambiar la linea 66 XD. Pero ya esta cambiada jaja
    if (!SDL_CreateWindowAndRenderer("Práctica 05 - Manejo de escenas", 960, 540, SDL_WINDOW_RESIZABLE, &window, &renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error al crear ventana o renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_Log("Renderer Driver activo: %s", SDL_GetRendererName(renderer));

    ::appstate.window = window;
    ::appstate.renderer = renderer;
    ::appstate.last_ticks = SDL_GetTicks();


::appstate.sceneManager.ChangeScene(
    std::make_unique<TitleScene>(&::appstate.sceneManager)
);

::appstate.sceneManager.ProcessPendingChanges();



    *appstate = &::appstate;
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    AppState *app = static_cast<AppState *>(appstate);

    // 1. Medición de Delta Time en segundos
    Uint64 current_ticks = SDL_GetTicks();
    float delta_time = static_cast<float>(current_ticks - app->last_ticks) / 1000.0f;
    app->last_ticks = current_ticks;

    // Evitar saltos de tiempo excesivos si el sistema operativo pausa el proceso
    if (delta_time > 0.05f)
    {
        delta_time = 0.05f;
    }

app->sceneManager.ProcessPendingChanges();

if(!app->sceneManager.HasScene()){
    return SDL_APP_SUCCESS;
}
app->sceneManager.Update(delta_time);

    app->sceneManager.Render(app->renderer);

    SDL_RenderPresent(app->renderer);



    return SDL_APP_CONTINUE;
}
//Sustituimos gran parte de SDL_AppEvent para cumplir el interruptor de depuracion con F1
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
   
   AppState *app = static_cast<AppState *>(appstate);

    if (event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;
    }

   if(app && app->sceneManager.HasScene()){
    app->sceneManager.HandleEvent(*event);
   }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    AppState *app = static_cast<AppState *>(appstate);
    if (app)
    {
        app->sceneManager.Clear();

        SDL_DestroyRenderer(app->renderer);
        SDL_DestroyWindow(app->window);
    }
    SDL_Quit();
}


