#include "Scene.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Components/RectangleShapeRenderer.h"
#include "Components/SquareCollider.h"

Scene::Scene(const std::string& _name)
{
	name = _name;
}

void Scene::Update(float _delta_time) const
{
	for (GameObject* const& game_object : gameObjects)
	{
		game_object->Update();
	}
}

void Scene::Render(sf::RenderWindow* _window) const
{
	for (GameObject* const& game_object : gameObjects)
	{
		game_object->Render(_window);
	}
}

std::string Scene::GetName() const
{
	return name;
}

GameObject* Scene::CreateGameObject(const std::string& _name)
{
	GameObject* const game_object = new GameObject();
	game_object->SetName(_name);
	gameObjects.push_back(game_object);
	return game_object;
}
