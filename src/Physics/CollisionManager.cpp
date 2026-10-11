#include "Physics/CollisionManager.hpp"

#include "Engine/GameObject.hpp"
#include "Physics/ColliderComponent.hpp"

CollisionManager::CollisionManager(
    std::vector<std::unique_ptr<GameObject>> *entities
): entities(entities) {}

bool CollisionManager::CheckAABB(
    const SDL_FRect &a,
    const SDL_FRect &b
){
    return 
    a.x < b.x + b.w &&
    a.x + a.w> b.x &&
    a.y < b.y + b.h &&
    a.y + a.h > b.y;

}
void CollisionManager::CheckCollisions(){
    if(!entities) return;
    for(auto &e : *entities)
    if(e)
    if(auto *c = e->GetComponent<ColliderComponent>())
    c->is_colliding = false;

    for(size_t i = 0; i < entities->size(); i++){
        GameObject *a = (*entities)[i].get();


        if(!a || !a->IsActive()) continue;

        auto *ca = a->GetComponent<ColliderComponent>();
        if(!ca)continue;

        for(size_t j = i+1; j < entities->size(); ++j){
GameObject *b = (*entities)[j].get();

 if (!b || !b->IsActive()) continue;

            auto *cb = b->GetComponent<ColliderComponent>();
            if (!cb) continue;

            if (!CheckAABB(
                ca->GetWorldBounds(),
                cb->GetWorldBounds()
            )) continue;

            ca->is_colliding = true;
            cb->is_colliding = true;

            a->OnCollision(b);
            b->OnCollision(a);
        }
    }
}