
#include "Game/ResourceDemoScene.hpp"

// Necesitamos esta biblioteca para crear objetos con unique_ptr.
#include <memory>

// Incluimos las clases que ya existen en nuestro motor.
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/TransformComponent.hpp"
#include "Engine/SpriteComponent.hpp"

// Nos permite cargar imagenes y crear superficies.
#include <SDL3_image/SDL_image.h>


// Constructor de nuestra escena.
// Recibimos el administrador de escenas y el renderer.
//
// Scene recibe el manager y el nombre de la escena.
// ResourceManager recibe el renderer para crear texturas.
ResourceDemoScene::ResourceDemoScene(
    SceneManager* manager,
    SDL_Renderer* renderer
)
    : Scene(manager, "ResourceDemoScene"),
      m_resources(renderer)
{
}


// Inicializamos la escena y creamos sus entidades.
void ResourceDemoScene::Init()
{
    // Limpiamos los objetos anteriores, si existen.
    m_entities.clear();

    // Reiniciamos el puntero del jugador.
    m_player = nullptr;

    // Comenzamos a contar enemigos desde cero.
    m_nextEnemyIndex = 0;


    // Solicitamos las tres texturas al ResourceManager.
    SDL_Texture* backgroundTexture =
        m_resources.GetTexture("assets/background.png");

    SDL_Texture* playerTexture =
        m_resources.GetTexture("assets/player.png");

    SDL_Texture* enemyTexture =
        m_resources.GetTexture("assets/enemy.png");


    // Si alguna imagen no pudo cargarse,
    // no podemos construir correctamente la escena.
    if (!backgroundTexture || !playerTexture || !enemyTexture)
    {
        SDL_Log("[ResourceDemoScene] Error al cargar imagenes.");
        return;
    }


    // Obtenemos las dimensiones originales del fondo.
    float backgroundWidth = 0.0f;
    float backgroundHeight = 0.0f;

    // Comprobamos que sus dimensiones sean validas.
    if (!SDL_GetTextureSize(
            backgroundTexture,
            &backgroundWidth,
            &backgroundHeight) ||
        backgroundWidth <= 0.0f ||
        backgroundHeight <= 0.0f)
    {
        SDL_Log("[ResourceDemoScene] Error en tamaño del fondo.");
        return;
    }


    // Creamos el objeto que representa nuestro fondo.
    auto background = std::make_unique<GameObject>("Background");

    // Ajustamos la imagen al tamaño de la ventana:
    // 960 pixeles de ancho y 540 de alto.
    background->AddComponent<TransformComponent>(
        Vector2{0.0f, 0.0f},
        Vector2{
            960.0f / backgroundWidth,
            540.0f / backgroundHeight
        }
    );

    // Agregamos el componente que dibuja la imagen.
    background->AddComponent<SpriteComponent>(backgroundTexture);

    // Guardamos el objeto dentro de la escena.
    m_entities.push_back(std::move(background));


    // Obtenemos las dimensiones originales del jugador.
    float playerWidth = 0.0f;
    float playerHeight = 0.0f;

    if (!SDL_GetTextureSize(
            playerTexture,
            &playerWidth,
            &playerHeight) ||
        playerWidth <= 0.0f ||
        playerHeight <= 0.0f)
    {
        SDL_Log("[ResourceDemoScene] Error en tamaño del jugador.");
        m_entities.clear();
        return;
    }


    // Creamos el GameObject de nuestro jugador.
    auto player = std::make_unique<GameObject>("Player");

    // Colocamos al jugador cerca de la parte inferior.
    // Ajustamos su imagen a un tamaño de 52x52 pixeles.
    player->AddComponent<TransformComponent>(
        Vector2{454.0f, 460.0f},
        Vector2{
            52.0f / playerWidth,
            52.0f / playerHeight
        }
    );

    // Asociamos la textura del jugador.
    player->AddComponent<SpriteComponent>(playerTexture);

    // Guardamos un puntero para moverlo despues.
    m_player = player.get();

    // El vector sera propietario del objeto.
    m_entities.push_back(std::move(player));


    // Creamos los 50 enemigos iniciales.
    SpawnEnemies(50);


    // Mostramos el resultado en la consola.
    SDL_Log("[ResourceDemoScene] Escena inicializada.");

    PrintMetrics();
}


// Crea nuevos enemigos utilizando una textura compartida.
void ResourceDemoScene::SpawnEnemies(int amount)
{
    // Solicitamos la textura del enemigo.
    //
    // Como ya fue cargada por ResourceManager,
    // GetTexture devolvera la textura de la cache.
    SDL_Texture* enemyTexture =
        m_resources.GetTexture("assets/enemy.png");

    if (!enemyTexture)
    {
        SDL_Log("[ResourceDemoScene] No existe textura de enemigo.");
        return;
    }


    // Obtenemos el tamaño original de la imagen.
    float enemyWidth = 0.0f;
    float enemyHeight = 0.0f;

    if (!SDL_GetTextureSize(
            enemyTexture,
            &enemyWidth,
            &enemyHeight) ||
        enemyWidth <= 0.0f ||
        enemyHeight <= 0.0f)
    {
        SDL_Log("[ResourceDemoScene] Error en tamaño enemigo.");
        return;
    }


    // Repetimos el proceso segun la cantidad solicitada.
    for (int i = 0; i < amount; ++i)
    {
        // Obtenemos el indice del siguiente enemigo.
        int index = m_nextEnemyIndex;

        // Calculamos su columna.
        // Tendremos 10 enemigos por fila.
        int col = index % 10;

        // Calculamos su fila utilizando division entera.
        int row = index / 10;


        // Calculamos la posicion individual del enemigo.
        float x = 140.0f + col * 65.0f;
        float y = 70.0f + row * 55.0f;


        // Creamos un nuevo objeto.
        auto enemy = std::make_unique<GameObject>("Enemy");


        // Cada enemigo tendra su propia posicion,
        // aunque todos compartan la misma textura.
        enemy->AddComponent<TransformComponent>(
            Vector2{x, y},
            Vector2{
                40.0f / enemyWidth,
                40.0f / enemyHeight
            }
        );


        // Agregamos el sprite utilizando la textura compartida.
        auto* sprite =
            enemy->AddComponent<SpriteComponent>(enemyTexture);


        // Algunos enemigos tendran una modulacion diferente.
        // Esto demuestra que podemos modificar su apariencia
        // sin crear otra copia de la textura.
        if (index % 5 == 0)
        {
            sprite->SetColorMod(
                SDL_FColor{1.0f, 0.7f, 0.7f, 1.0f}
            );
        }


        // Guardamos el objeto en la escena.
        m_entities.push_back(std::move(enemy));

        // Incrementamos el contador para el siguiente enemigo.
        ++m_nextEnemyIndex;
    }
}


// Muestra informacion sobre los recursos utilizados.
void ResourceDemoScene::PrintMetrics() const
{
    SDL_Log("==========================================");

    SDL_Log("[Flyweight Metric] Entidades: %zu",
            m_entities.size());

    // Consultamos las texturas que administra ResourceManager.
    SDL_Log("[Flyweight Metric] Texturas: %zu",
            m_resources.GetTextureCount());

    SDL_Log("==========================================");
}


// Procesa los eventos del teclado.
void ResourceDemoScene::HandleEvent(const SDL_Event& event)
{
    // Solamente nos interesan las teclas presionadas.
    if (event.type != SDL_EVENT_KEY_DOWN)
    {
        return;
    }

    // Ignoramos repeticiones automaticas de una tecla.
    if (event.key.repeat)
    {
        return;
    }


    // Al presionar ESPACIO creamos 8 enemigos adicionales.
    if (event.key.scancode == SDL_SCANCODE_SPACE)
    {
        SpawnEnemies(8);
        PrintMetrics();
    }


    // La tecla C limpia la cache y reconstruye la escena.
    else if (event.key.scancode == SDL_SCANCODE_C)
    {
        ResetCache();
    }


    // La tecla L provoca una fuga de memoria intencional.
    // Es una prueba opcional para estudiar AddressSanitizer.
    else if (event.key.scancode == SDL_SCANCODE_L)
    {
        TriggerDeliberateLeak();
    }


    // ESCAPE solicita cerrar la escena actual.
    else if (event.key.scancode == SDL_SCANCODE_ESCAPE)
    {
        // Si esta es la unica escena, SceneManager quedara
        // vacio y el ciclo principal terminara la aplicacion.
        m_manager->PopScene();
    }
}


// Actualiza la posicion del jugador.
void ResourceDemoScene::Update(float dt)
{
    // Primero comprobamos que el jugador exista.
    if (m_player != nullptr)
    {
        // Buscamos el componente que guarda su posicion.
        auto* transform =
            m_player->GetComponent<TransformComponent>();

        if (transform != nullptr)
        {
            // Consultamos el estado actual del teclado.
            const bool* keys = SDL_GetKeyboardState(nullptr);

            // Guardamos el movimiento en ambos ejes.
            float dx = 0.0f;
            float dy = 0.0f;


            // Movimiento horizontal.
            if (keys[SDL_SCANCODE_A] ||
                keys[SDL_SCANCODE_LEFT])
            {
                dx -= 1.0f;
            }

            if (keys[SDL_SCANCODE_D] ||
                keys[SDL_SCANCODE_RIGHT])
            {
                dx += 1.0f;
            }


            // Movimiento vertical.
            if (keys[SDL_SCANCODE_W] ||
                keys[SDL_SCANCODE_UP])
            {
                dy -= 1.0f;
            }

            if (keys[SDL_SCANCODE_S] ||
                keys[SDL_SCANCODE_DOWN])
            {
                dy += 1.0f;
            }


            // Calculamos el desplazamiento.
            // Multiplicamos por dt para que el movimiento
            // dependa del tiempo y no de los FPS.
            Vector2 movement{
                dx * m_playerSpeed * dt,
                dy * m_playerSpeed * dt
            };


            // Movemos al jugador con el metodo que
            // ya existe en nuestro TransformComponent.
            transform->Translate(movement);


            // Evitamos que el jugador salga de la ventana.
            // Su tamaño visible es de 52x52 pixeles.
            if (transform->position.x < 0.0f)
                transform->position.x = 0.0f;

            if (transform->position.x > 908.0f)
                transform->position.x = 908.0f;

            if (transform->position.y < 0.0f)
                transform->position.y = 0.0f;

            if (transform->position.y > 488.0f)
                transform->position.y = 488.0f;
        }
    }


    // Actualizamos los componentes de nuestros objetos.
    Scene::Update(dt);
}


// Dibuja todos los objetos de la escena.
void ResourceDemoScene::Render(SDL_Renderer* renderer)
{
    if (renderer == nullptr)
    {
        return;
    }

    // Establecemos un color de fondo oscuro.
    SDL_SetRenderDrawColor(renderer, 10, 10, 25, 255);

    // Limpiamos el contenido del cuadro anterior.
    SDL_RenderClear(renderer);

    // Scene::Render recorre los GameObject.
    // Cada SpriteComponent dibujara su textura.
    Scene::Render(renderer);

    // No llamamos SDL_RenderPresent aqui.
    // Nuestro main.cpp ya lo hace en SDL_AppIterate.
}


// Limpia la cache de forma segura y reconstruye la escena.
void ResourceDemoScene::ResetCache()
{
    SDL_Log("[ResourceDemoScene] Reiniciando recursos...");

    // Primero eliminamos los objetos que usan las texturas.
    m_entities.clear();

    // El puntero del jugador ya no es valido.
    m_player = nullptr;

    // Ahora podemos liberar las texturas compartidas.
    m_resources.Clear();

    // Volvemos a cargar las imagenes y crear los objetos.
    Init();
}


// Prueba opcional de fuga de memoria.
//
// ATENCION: Este metodo provoca una fuga intencional.
// Solo debe utilizarse para estudiar AddressSanitizer.
void ResourceDemoScene::TriggerDeliberateLeak()
{
    int loaded = 0;

    // Cargamos 50 superficies por separado.
    for (int i = 0; i < 50; ++i)
    {
        SDL_Surface* surface =
            IMG_Load("assets/enemy.png");

        // Si falla la carga, detenemos el experimento.
        if (surface == nullptr)
        {
            SDL_Log("[Leak Test] Error: %s", SDL_GetError());
            break;
        }

        ++loaded;

        // OMITIDO INTENCIONALMENTE:
        // SDL_DestroySurface(surface);
        //
        // Al no liberar la superficie, dejamos memoria
        // reservada que ya no podemos recuperar.
    }

    SDL_Log("[Leak Test] %d superficies sin liberar.",
            loaded);

    SDL_Log("[Leak Test] Cierra la aplicacion para revisar ASan.");
}


// Se ejecuta al salir de la escena.
void ResourceDemoScene::Exit()
{
    SDL_Log("[ResourceDemoScene] Cerrando escena...");

    // Eliminamos primero las entidades.
    // Asi dejamos de utilizar los punteros a las texturas.
    m_entities.clear();

    m_player = nullptr;

    // Finalmente liberamos las texturas del administrador.
    m_resources.Clear();

    SDL_Log("[ResourceDemoScene] Recursos liberados.");
}
