#pragma once

#include "Component.h"

class SquareCollider : public Component
{
public:
    SquareCollider() = default;
    ~SquareCollider() override = default;

    float width = 0.0001f;
    float height = 0.0001f;

    float GetWidth() const { return width; }
    float GetHeight() const { return height; }

    float GetLeft() const { return GetOwner()->GetPosition().x - width / 2.0f; }
    float GetRight() const { return GetOwner()->GetPosition().x + width / 2.0f; }
    float GetTop() const { return GetOwner()->GetPosition().y - height / 2.0f; }
    float GetBottom() const { return GetOwner()->GetPosition().y + height / 2.0f; }

    void SetWidth(const float _width) { width = _width; }
    void SetHeight(const float _height) { height = _height; }

    static bool IsColliding(const SquareCollider& _collider_a, const SquareCollider& _collider_b);
};
