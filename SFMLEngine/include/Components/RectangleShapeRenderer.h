#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "ARendererComponent.h"

class RectangleShapeRenderer : public ARendererComponent
{
public:
	RectangleShapeRenderer();
	~RectangleShapeRenderer() override;

	void SetColor(const sf::Color& _color) { color = _color; }

	void Render(sf::RenderWindow* _window) override;
	void OnDebug() override;

protected:
	sf::Color color = sf::Color::White;

	sf::RectangleShape* shape = nullptr;
};

class SpriteRenderer : public RectangleShapeRenderer
{
public:
	sf::Texture texture;
	sf::Sprite Sprite;
	sf::IntRect frameRect(int w, int x, int y, int z);

	void setTexture(std::string);
	void setTextureRect(std::string);
	void Render(sf::RenderWindow* _window) override;
};

