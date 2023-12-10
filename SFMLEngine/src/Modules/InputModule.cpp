#include "Modules/InputModule.h"

#include <imgui-SFML.h>
#include <SFML/Window/Event.hpp>

#include "Engine.h"
#include "ModuleManager.h"
#include "Modules/WindowModule.h"

void InputModule::Start()
{
	Module::Start();

	window = moduleManager->GetModule<WindowModule>()->GetWindow();
}

void InputModule::Update()
{
	Module::Update();

	events.clear();
	keyUp.reset();
	keyDown.reset();
	mouseDown.reset();
	mouseUp.reset();

	sf::Event event;
	while (window->pollEvent(event))
	{
		events.push_back(event);

		if (event.type == sf::Event::Closed)
		{
			Engine::GetInstance()->Quit();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			keyDown.set(event.key.code);
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			keyUp.set(event.key.code);
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			mouseDown.set(event.mouseButton.button);
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			mouseUp.set(event.mouseButton.button);
		}
	}

	const sf::Vector2i previous_mouse_position = sf::Vector2i(mousePosition);
	const sf::Vector2i new_mouse_position = sf::Mouse::getPosition(*window);

	mouseDelta = new_mouse_position - previous_mouse_position;
	mousePosition = new_mouse_position;
}

bool InputModule::GetMouseButton(const sf::Mouse::Button _button)
{
	return sf::Mouse::isButtonPressed(_button);
}

bool InputModule::GetKey(const sf::Keyboard::Key _key)
{
	return sf::Keyboard::isKeyPressed(_key);
}

bool InputModule::GetMouseButtonDown(const sf::Mouse::Button _button)
{
	return mouseDown[_button];
}

bool InputModule::GetKeyDown(const sf::Keyboard::Key _key)
{
	return keyDown[_key];
}

bool InputModule::GetMouseButtonUp(const sf::Mouse::Button _button)
{
	return mouseUp[_button];
}

bool InputModule::GetKeyUp(const sf::Keyboard::Key _key)
{
	return keyUp[_key];
}

Maths::Vector2i InputModule::mousePosition = Maths::Vector2i::Zero;
Maths::Vector2i InputModule::mouseDelta = Maths::Vector2i::Zero;

std::vector<sf::Event> InputModule::events;

std::bitset<sf::Mouse::Button::ButtonCount> InputModule::mouseDown;
std::bitset<sf::Mouse::Button::ButtonCount> InputModule::mouseUp;
std::bitset<sf::Keyboard::Key::KeyCount> InputModule::keyDown;
std::bitset<sf::Keyboard::Key::KeyCount> InputModule::keyUp;
