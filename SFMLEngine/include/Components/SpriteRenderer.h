#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include "ARendererComponent.h"

class SpriteRenderer : public ARendererComponent
{
public:
	SpriteRenderer();
	~SpriteRenderer() override;

	void SetSprite(sf::Sprite* _sprite) { sprite = _sprite; }

	void Render(sf::RenderWindow* _window) override;

private:
	sf::Sprite* sprite = nullptr;
};
