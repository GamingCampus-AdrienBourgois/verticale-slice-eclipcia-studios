#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include "Component.h"

class ShapeRenderer : public Component
{
public:
	ShapeRenderer();
	~ShapeRenderer() override;

	void SetColor(const sf::Color& _color) { color = _color; }
	void SetSize(float width, float height) { shape->setSize(sf::Vector2f(width, height)); }

	void Render(sf::RenderWindow* _window) override;

private:
	sf::Color color = sf::Color::White;
	sf::RectangleShape* shape = nullptr;
};
