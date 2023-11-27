#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Module.h"

class WindowModule final : public Module
{
public:
	sf::RenderWindow* GetWindow() const { return window; }

	void Init() override;
	void Start() override;
	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;
	void Release() override;

private:
	sf::RenderWindow* window = nullptr;
};
