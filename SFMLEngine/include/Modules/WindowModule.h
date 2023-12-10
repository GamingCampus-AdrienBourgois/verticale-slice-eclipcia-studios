#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Module.h"

class WindowModule final : public Module
{
public:
	sf::RenderWindow* GetWindow() const { return window; }

	void Awake() override;
	void PreRender() override;
	void Present() override;
	void Destroy() override;

private:
	sf::RenderWindow* window = nullptr;
};
