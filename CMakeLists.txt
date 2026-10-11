cmake_minimum_required(VERSION 3.16)

project(proyecto01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG)

add_executable(proyecto01
    src/main.cpp

    src/Math/Vector2.cpp

    src/Engine/Component.cpp
    src/Engine/GameObject.cpp
    src/Engine/TransformComponent.cpp
    src/Engine/RectRenderComponent.cpp
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
)

target_include_directories(proyecto01 PRIVATE
    include
)

target_link_libraries(proyecto01 PRIVATE SDL3::SDL3)