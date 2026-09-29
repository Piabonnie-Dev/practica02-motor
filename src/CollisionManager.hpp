#pragma once

#include <memory>
#include <vector>

#include "GameObject.hpp"
#include "ColliderComponent.hpp"

class CollisionManager{
private:
std::vector<std::unique_ptr<GameObject>> *m_entities{nullptr};

public:
explicit CollisionManager(
    std::vector<std::unique_ptr<GameObject>> *entities) : m_entities {entities}
{}

bool CheckAABB(const SDL_FRect &a, const SDL_FRect &b) const
{
return 
a.x < b.x + b.w &&
a.x + a.w > b.x &&
a.y < b.y + b.h &&
a.y + a.h > b.y;

}

bool CheckCollision(
    const ColliderComponent &a,
    const ColliderComponent &b) const
    {
        return CheckAABB(a.GetWorldBounds(),
    b.GetWorldBounds());
    }

    void CheckCollisions(){

if(!m_entities)
return;

// Limpiar estados del frame anterior

for(auto &entity : *m_entities){
if(!entity)
continue;

if(auto *collider = entity->GetComponent<ColliderComponent>())
{
    collider->is_colliding = false;
}

}

const std::size_t count = m_entities->size();

//Comparacion triangulas i < j

for(std::size_t i=0; i<count; ++i)
{
    GameObject *entityA =
    (*m_entities)[i].get();
    if(!entityA || !entityA->IsActive())
    continue;
  auto *colliderA = entityA->GetComponent<ColliderComponent>();
  
  if(!colliderA)
  continue;

  for(std::size_t j=i +1; j< count; ++j){
   GameObject *entityB =
                    (*m_entities)[j].get();

                if (!entityB || !entityB->IsActive())
                    continue;

                auto *colliderB =
                    entityB->GetComponent<ColliderComponent>();

                if (!colliderB)
                    continue;

                if (CheckCollision(
                        *colliderA,
                        *colliderB))
                {
                    // Marcamos visualmente
                    colliderA->is_colliding = true;
                    colliderB->is_colliding = true;

                    // Avisamos a las dos entidades
                    entityA->OnCollision(entityB);
                    entityB->OnCollision(entityA);
                }

  }
}



    }


};