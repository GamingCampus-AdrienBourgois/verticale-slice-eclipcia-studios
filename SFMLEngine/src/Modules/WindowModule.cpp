#include "Modules/WindowModule.h"

#include <imgui-SFML.h>
#include <iostream>
#include <SFML/Window/Event.hpp>

#include "Engine.h"

void WindowModule::Init()
{
	Module::Init();

	window = new sf::RenderWindow(sf::VideoMode(600, 600), "SFML Engine");
}

void WindowModule::Start()
{
	Module::Start();
}

void WindowModule::Update()
{
	Module::Update();

	sf::Event event;
	while (window->pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(*window, event);

		if (event.type == sf::Event::Closed)
		{
			Engine::GetInstance()->Quit();
		}
	}
}

void WindowModule::PreRender()
{
	Module::PreRender();

	window->clear(sf::Color::Black);
}

void WindowModule::Render()
{
	Module::Render();
}

void WindowModule::PostRender()
{
	Module::PostRender();

	window->display();
}

void WindowModule::Release()
{
	Module::Release();

	window->close();
}
