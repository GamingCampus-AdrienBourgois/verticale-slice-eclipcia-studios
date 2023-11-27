#include "Components/RectangleShapeRenderer.h"

#include "SFML/Graphics/Shape.hpp"

RectangleShapeRenderer::RectangleShapeRenderer()
{
	shape = new sf::RectangleShape();
}

RectangleShapeRenderer::~RectangleShapeRenderer()
{
	delete shape;
	shape = nullptr;
}

void RectangleShapeRenderer::Render(sf::RenderWindow* _window)
{
	ARendererComponent::Render(_window);

	const GameObject* owner = GetOwner();

	const Maths::Vector2<float> position = owner->GetPosition();
	shape->setPosition(position.x, position.y);
	shape->setSize(static_cast<sf::Vector2f>(owner->GetScale() * size));
	shape->setRotation(owner->GetRotation());
	shape->setFillColor(color);

	_window->draw(*shape);
}
