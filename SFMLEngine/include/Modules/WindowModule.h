#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Module.h"

class WindowModule final : public Module
{
public:
	sf::RenderWindow* GetWindow() const { return window; }

	void Awake() override;
	void PreRender() override;
	void Present() override;
	void Destroy() override;
	// Ajouter une fonction pour définir la texture du fond
	void SetBackgroundTexture(const std::string& _texturePath);
	void ToggleFullscreen();
private:
	sf::RenderWindow* window = nullptr;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	bool fullscreen = false; // Ajout de la variable fullscreen
};
