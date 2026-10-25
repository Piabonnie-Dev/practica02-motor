#include "Game/ProjectileComponent.hpp"

#include "Engine/GameObject.hpp"
#include "Engine/TransformComponent.hpp"


//Constructor del proyectil 
//Velocity es un Vector2 con velocidad en X y en Y.
ProjectileComponent::ProjectileComponent(Vector2 velocity)
    : velocity(velocity) {}

    //Actualizamos el movimiento utilizando el paso fisico.
void ProjectileComponent::FixedUpdate(float dt) {
    auto *t = owner->GetComponent<TransformComponent>();
    if (!t) return;

    t->Translate(velocity * dt);

    if (t->position.y < -20 || t->position.y > 560)
        owner->SetActive(false);
}

//Metodo encargado de responder a una colision. 
void ProjectileComponent::OnCollision(GameObject *other) {
    if (!other) return; 

    const auto &me = owner->GetTag();
    const auto &tag = other->GetTag();

    //Comprobamos dos condiciones:
    // 1. Nuestro proyectil pertence al jugador.
    //2. Choco con un enemigo con un bunker. 

    if (me == "PlayerBullet" &&
        (tag == "Enemy" || tag == "Bunker")) {
        owner->SetActive(false);
        other->SetActive(false);
    }
//Si es una  bala enemiga que choca con un bunker
    if (me == "EnemyBullet" && tag == "Bunker") {
        owner->SetActive(false); //Desactivamos el proyectil enemigo
        other->SetActive(false); //Desactivamos el bloque del bunker.
    }
}
