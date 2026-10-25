
cmake_minimum_required(VERSION 3.16)

project(proyecto01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Bibliotecas necesarias.
find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_image REQUIRED CONFIG)

# Archivos que forman nuestro programa.
add_executable(proyecto01

    src/main.cpp

    src/Math/Vector2.cpp

    src/Engine/Component.cpp
    src/Engine/GameObject.cpp
    src/Engine/TransformComponent.cpp
    src/Engine/RectRenderComponent.cpp
    src/Engine/SpriteComponent.cpp
    src/Engine/ResourceManager.cpp
    src/Engine/Scene.cpp
    src/Engine/SceneManager.cpp

    src/Physics/ColliderComponent.cpp
    src/Physics/CollisionManager.cpp

    src/Game/TitleScene.cpp
    src/Game/GameScene.cpp
    src/Game/PauseScene.cpp
    src/Game/GameOverScene.cpp
    src/Game/PlayerComponent.cpp
    src/Game/ProjectileComponent.cpp

    # Nueva escena de la Practica 06.
    src/Game/ResourceDemoScene.cpp
)

# Carpeta que contiene nuestros encabezados.
target_include_directories(proyecto01 PRIVATE include)

# Enlazamos SDL3 y SDL3_image.
target_link_libraries(proyecto01 PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
)
