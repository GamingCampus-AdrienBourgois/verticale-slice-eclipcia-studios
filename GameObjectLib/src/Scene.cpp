#include "Scene.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Components/ShapeRenderer.h"
#include "Components/SquareCollider.h"

void Scene::Run(sf::RenderWindow& window)
{

}

void Scene::Update(float dt, int windowHeight)
{
	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Update(dt, windowHeight);
	}
}

void Scene::Render(sf::RenderWindow* _window)
{
	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Render(_window);
	}
}

GameObject* Scene::CreateDummyGameObject(const std::string& _name)
{
	auto gameObject = new GameObject();
	gameObject->SetName(_name);
	gameObjects.push_back(gameObject);
	return gameObject;
}

GameObject* Scene::CreateGameObject(const std::string& name, float x, float y, float width, float height, const sf::Color color)
{
	GameObject* gameObject = CreateDummyGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(x, y));

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetWidth(width);
	squareCollider->SetHeight(height);

	ShapeRenderer* shapeRenderer = gameObject->CreateComponent<ShapeRenderer>();
	shapeRenderer->SetColor(color);
	shapeRenderer->SetSize(width, height);

	return gameObject;
}

GameObject* Scene::CreateBoss(const std::string& name, float x, float y, float width, float height, const sf::Color color)
{
	// Crée un GameObject comme pour un objet ordinaire
	GameObject* boss = CreateGameObject(name, x, y, width, height, color);

	// Ajoute un collider rectangulaire au boss
	SquareCollider* collider = boss->CreateComponent<SquareCollider>();
	collider->SetWidth(width);
	collider->SetHeight(height);

	// Ajoute un ShapeRenderer pour rendre le boss visuellement
	ShapeRenderer* renderer = boss->CreateComponent<ShapeRenderer>();
	renderer->SetColor(color);
	renderer->SetSize(width, height);

	return boss;
}
