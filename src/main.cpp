
#define SDL_MAIN_USE_CALLBACKS 1

#include <memory>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Engine/SceneManager.hpp"

// NUEVO: Incluimos la escena de demostracion de recursos.
#include "Game/ResourceDemoScene.hpp"


// AppState agrupa informacion necesaria
// para mantener funcionando el videojuego.
struct AppState
{
    SDL_Window* window{}; // Apunta a la ventana del juego.

    SDL_Renderer* renderer{}; // Permite dibujar con SDL3.

    Uint64 lastTicks{}; // Guarda el tiempo entre actualizaciones.

    SceneManager scenes; // Administra las escenas del videojuego.
};


static AppState app;


// Inicializa SDL3, crea la ventana y establece la escena inicial.
SDL_AppResult SDL_AppInit(void** state, int, char**)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
        return SDL_APP_FAILURE;


    if (!SDL_CreateWindowAndRenderer(

        // NUEVO: cambiamos el titulo de nuestra ventana.
        "Practica 06 - Gestion de Recursos",

        960, 540,
        SDL_WINDOW_RESIZABLE,
        &app.window,
        &app.renderer))

        return SDL_APP_FAILURE;


    // Guardamos el tiempo inicial.
    app.lastTicks = SDL_GetTicks();


    // NUEVO: Iniciamos directamente ResourceDemoScene.
    //
    // Ya no iniciamos con TitleScene.
    //
    // Enviamos el administrador de escenas y el renderer.
    // El renderer permitira crear las texturas del juego.
    app.scenes.ChangeScene(
        std::make_unique<ResourceDemoScene>(
            &app.scenes,
            app.renderer
        )
    );


    // Aplicamos el cambio de escena pendiente.
    // Esto tambien ejecuta Init() de ResourceDemoScene.
    app.scenes.ProcessPendingChanges();


    *state = &app;

    return SDL_APP_CONTINUE;
}


// Actualiza la logica y dibuja cada fotograma.
SDL_AppResult SDL_AppIterate(void* state)
{
    auto* app = static_cast<AppState*>(state);


    // Calculamos el tiempo transcurrido entre fotogramas.
    Uint64 now = SDL_GetTicks();

    float dt = (now - app->lastTicks) / 1000.0f;

    app->lastTicks = now;


    // Limitamos dt para evitar saltos muy grandes.
    if (dt > 0.05f)
        dt = 0.05f;


    // Procesamos cambios de escena.
    app->scenes.ProcessPendingChanges();


    // Si ya no existe ninguna escena, cerramos el programa.
    if (!app->scenes.HasScene())
        return SDL_APP_SUCCESS;


    // Actualizamos la escena activa.
    app->scenes.Update(dt);

    app->scenes.ProcessPendingChanges();


    // Dibujamos todos los objetos de la escena.
    app->scenes.Render(app->renderer);

    // Mostramos el fotograma terminado en pantalla.
    SDL_RenderPresent(app->renderer);


    return SDL_APP_CONTINUE;
}


// Recibe eventos del teclado y solicitudes de cerrar.
SDL_AppResult SDL_AppEvent(void* state, SDL_Event* event)
{
    auto* app = static_cast<AppState*>(state);


    // Si se solicita cerrar la ventana, terminamos.
    if (event->type == SDL_EVENT_QUIT)
        return SDL_APP_SUCCESS;


    // Enviamos los eventos a la escena activa.
    //
    // ResourceDemoScene procesara las teclas:
    // ESPACIO, C, L y ESCAPE.
    if (app->scenes.HasScene())
        app->scenes.HandleEvent(*event);


    return SDL_APP_CONTINUE;
}


// Libera las escenas, el renderer y la ventana.
void SDL_AppQuit(void* state, SDL_AppResult)
{
    auto* app = static_cast<AppState*>(state);


    // Destruimos las escenas y liberamos sus recursos.
    // ResourceDemoScene libera sus texturas en Exit().
    app->scenes.Clear();


    // Destruimos el renderer despues de liberar las texturas.
    SDL_DestroyRenderer(app->renderer);


    // Cerramos la ventana.
    SDL_DestroyWindow(app->window);


    // Finalizamos SDL3.
    SDL_Quit();
}
