# Proyecto 01 - Space Invaders

Videojuego arcade 2D desarrollado en C++20 utilizando SDL3.

Este proyecto fue realizado como parte de la materia Fundamentos de Motores de Videojuegos con C++.

## Descripción

El proyecto está basado en el juego clásico Space Invaders.

El jugador controla una nave ubicada en la parte inferior de la pantalla. El objetivo es destruir a todos los enemigos antes de perder las tres vidas disponibles o antes de que la formación enemiga alcance la posición de la nave.

Los enemigos se desplazan lateralmente en formación y descienden cada vez que alcanzan uno de los bordes de la pantalla.

Conforme disminuye la cantidad de enemigos, aumenta la velocidad de desplazamiento de la horda.

También existen proyectiles enemigos y búnkeres destructibles que sirven como protección para el jugador.

## Controles

- A / Flecha izquierda: mover la nave hacia la izquierda.
- D / Flecha derecha: mover la nave hacia la derecha.
- Espacio: disparar.
- P / Escape: pausar o reanudar la partida.
- F1: activar o desactivar la visualización de colisionadores.
- R: reiniciar la partida desde la pantalla de fin de juego.
- M: regresar al menú principal desde la pantalla de fin de juego.
- Espacio / Enter: iniciar la partida desde el menú principal.

## Condiciones de victoria y derrota

### Victoria

El jugador gana cuando elimina a todos los enemigos.

### Derrota

El jugador pierde cuando ocurre cualquiera de las siguientes condiciones:

- Se terminan sus tres vidas.
- La formación enemiga alcanza la zona de la nave.

## Puntuación

Cada enemigo destruido otorga 100 puntos.

La puntuación se muestra en el título de la ventana junto con las vidas restantes.

## Arquitectura

El proyecto utiliza el patrón GameObject-Component.

Cada entidad del juego está representada mediante un GameObject al que se agregan distintos componentes.

Entre los principales componentes se encuentran:

- TransformComponent
- RectRenderComponent
- ColliderComponent
- PlayerComponent
- ProjectileComponent

La administración de escenas se realiza mediante SceneManager.

Las escenas utilizadas son:

- TitleScene
- GameScene
- PauseScene
- GameOverScene

## Física

El proyecto separa la actualización general de la simulación física.

Update(float dt) se utiliza para lógica general del juego.

FixedUpdate(float fixed_dt) se utiliza para movimiento y simulación física utilizando un paso fijo de 60 Hz.

Las colisiones utilizan cajas AABB y son procesadas mediante CollisionManager.

Las respuestas a colisiones se realizan utilizando:

OnCollision(GameObject* other)

## Debug Draw

La tecla F1 permite activar o desactivar la visualización de los colisionadores.

- Verde: objeto sin colisión.
- Rojo: objeto en contacto con otro collider.

## Gráficos

Todos los elementos visuales están construidos utilizando primitivas geométricas de SDL3.

No se utilizan:

- Texturas externas.
- Imágenes.
- Spritesheets.
- Fuentes externas.

## Requisitos
- C++20
- SDL3
- CMake
- Compilador compatible con C++20
El proyecto fue desarrollado utilizando MSYS2 UCRT64 en Windows.

## Compilacion

desde la carepta raiz

cmake -S . -B build
cmake --build build

 ## Ejecución
En Windows utilizando MSYS2/UCRT64:
./build/proyecto01.exe

## Limpieza de compilación
Para eliminar completamente los archivos generados:
rm -rf build

Después se puede volver a configurar y compilar con:
cmake -S . -B build
cmake --build build

## Control de versiones
La entrega oficial del Proyecto 01 utiliza la etiqueta:
v1.0-checkpoint1

## Autor
Elliot Kenneth Villafaña Pasten 118006642