#include "Game/PlayerComponent.hpp"

#include <algorithm>
#include <SDL3/SDL.h>

#include "Engine/GameObject.hpp"
#include "Engine/TransformComponent.hpp"
#include "Math/Vector2.hpp"

//Constructor del componente.
//Recibe la velocidad del jugador.
PlayerComponent::PlayerComponent(float speed) : speed(speed){

}

//Owner es el GameObject al que pertenece este componente.
//Y obtenemos su TransformComponent
void PlayerComponent::FixedUpdate(float dt){
    auto *t = owner->GetComponent<TransformComponent>();
    if(!t) return; //Si no tenemos su transformcomponent no se mueve.

    const bool *keys = SDL_GetKeyboardState(nullptr); //Recibimos un puntero a los estados del teclado

    //Creamos un vector de direccion 
    Vector2 dir{
        float(keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) -
        float(keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]),
        0

    };
if(dir.length_squared())

t->Translate(dir.normalized() * (speed * dt));
//Mantiene la posicion horizontal entre 0 y 900.
t->position.x=std::clamp(t->position.x, 0.0f, 900.0f);

}
//Metodo que se ejecuta cuando el jugador colisiona
void PlayerComponent::OnCollision(GameObject *other) {
   //Primero comprobamos que ohter no sea nulo
   //Despues se verifica que sea una bala enemiga.
    if (other && other->GetTag() == "EnemyBullet") {
        other->SetActive(false); //Desactivamos la bala para que pueda eliminarse
        --lives; //Disminuyen el valor de vidas en una unidad.
    }
}

//Metodo que devuelve la cantidad de vidas restantes.
int PlayerComponent::GetLives() const {
    return lives;
}
