

#pragma once

#include "Engine/Component.hpp"
#include "Math/Vector2.hpp"

//En este componente encapsulamos las propiedades de traslacion
//y escala de cualquier objeto en la escena.

class TransformComponent : public Component{


public:
Vector2 position;
Vector2 scale{ 1, 1};

TransformComponent() = default;
TransformComponent(Vector2 position, Vector2 scale);

void Translate(const Vector2 &offset);


};