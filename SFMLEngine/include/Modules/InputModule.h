#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Module.h"

class InputModule final : public Module
{
public:
	void Start() override;
	void Update() override;

private:
	sf::RenderWindow* window = nullptr;
};
