#include "Engine/TransformComponent.hpp"

TransformComponent::TransformComponent(Vector2 position, Vector2 scale)
    : position(position), scale(scale) {}

void TransformComponent::Translate(const Vector2 &offset) {
    position = position + offset;
}