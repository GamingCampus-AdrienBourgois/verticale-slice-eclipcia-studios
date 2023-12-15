#include "Modules/WindowModule.h"

#include <iostream>
#include <SFML/Window/Event.hpp>

#include "Engine.h"


void WindowModule::Awake()
{
	Module::Awake();

	window = new sf::RenderWindow(sf::VideoMode(1600, 800), "SFML Engine");
	// Charger la texture du fond
	SetBackgroundTexture("../Assets/fond.jpg");

}

void WindowModule::PreRender()
{
	Module::PreRender();

	window->clear(sf::Color::Black);
	// Dessiner le fond
	window->draw(backgroundSprite);

}

void WindowModule::Present()
{
	Module::Present();

	window->display();
}

void WindowModule::Destroy()
{
	Module::Destroy();

	window->close();
}

void WindowModule::SetBackgroundTexture(const std::string& _texturePath)
{
	if (backgroundTexture.loadFromFile(_texturePath))
	{
		backgroundSprite.setTexture(backgroundTexture);
		// Adapter la taille du sprite à la taille de la fenêtre
		backgroundSprite.setScale(window->getSize().x / backgroundSprite.getLocalBounds().width,
			window->getSize().y / backgroundSprite.getLocalBounds().height);
	}
	else
	{
		std::cerr << "Failed to load background texture!" << std::endl;
	}
}