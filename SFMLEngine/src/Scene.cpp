#include "Scene.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

Scene::Scene(const std::string& _name)
{
	name = _name;
}

void Scene::Awake() const
{
	for (GameObject* const& game_object : gameObjects)
	{
		game_object->Awake();
	}
}

void Scene::Start() const
{
	for (GameObject* const& game_object : gameObjects)
	{
		game_object->Start();
	}
}

void Scene::PreRender() const
{
	for (GameObject* const& game_object : gameObjects)
	{
		game_object->PreRender();
	}
}

void Scene::OnGUI() const
{
	for (GameObject* const& game_object : gameObjects)
	{
		game_object->OnGUI();
	}
}

void Scene::PostRender() const
{
	for (GameObject* const& game_object : gameObjects)
	{
		game_object->PostRender();
	}
}

void Scene::OnDebug() const
{
	for (GameObject* const& game_object : gameObjects)
	{
		game_object->OnDebug();
	}
}

void Scene::OnDebugSelected() const
{
	for (GameObject* const& game_object : gameObjects)
	{
		game_object->OnDebugSelected();
	}
}

void Scene::Present() const
{
	for (GameObject* const& game_object : gameObjects)
	{
		game_object->Present();
	}
}

void Scene::OnEnable() const
{
	for (GameObject* const& game_object : gameObjects)
	{
		game_object->OnEnable();
	}
}

void Scene::OnDisable() const
{
	for (GameObject* const& game_object : gameObjects)
	{
		game_object->OnDisable();
	}
}

void Scene::Destroy() const
{
	for (GameObject* const& game_object : gameObjects)
	{
		game_object->Destroy();
	}
}

void Scene::Finalize() const
{
	for (GameObject* const& game_object : gameObjects)
	{
		game_object->Finalize();
	}
}

void Scene::Update(const float _delta_time) const
{
	for (GameObject* const& game_object : gameObjects)
	{
		game_object->Update(_delta_time);
	}
}

void Scene::Render(sf::RenderWindow* _window) const
{
	for (GameObject* const& game_object : gameObjects)
	{
		game_object->Render(_window);
	}
}

const std::string& Scene::GetName() const
{
	return name;
}

GameObject* Scene::CreateGameObject(const std::string& _name, const int _health, const Maths::Vector2<float> _position, const Maths::Vector2<float> _size, const sf::Color _color, const Scene& _sceneName, std::string asset, float width, float height)
{
	GameObject* const game_object = new GameObject();
	game_object->SetName(_name);
	game_object->SetPosition(_position);
	game_object->SetScene(this);
	gameObjects.push_back(game_object);

	Health* objectHealth = game_object->CreateComponent<Health>();
	objectHealth->SetDefaultHealth(_health);

	//ajoute un shaperanderer
	SpriteRenderer* shapeRenderer = game_object->CreateComponent<SpriteRenderer>();
	shapeRenderer->setTexture(asset);
	shapeRenderer->Sprite.setScale(width, height);

	SquareCollider* square_collider = game_object->CreateComponent<SquareCollider>();
	square_collider->SetWidth(shapeRenderer->texture.getSize().x);
	square_collider->SetHeight(shapeRenderer->texture.getSize().y);

	return game_object;
}

GameObject* Scene::CreateGameObjectPlayer(const std::string& _name, const int _health, const Maths::Vector2<float> _position, const Maths::Vector2<float> _size, const sf::Color _color, const Scene& _sceneName, std::string asset, float width, float height)
{
	GameObject* const game_object = new GameObject();
	game_object->SetName(_name);
	game_object->SetPosition(_position);
	game_object->SetScene(this);
	gameObjects.push_back(game_object);

	Health* objectHealth = game_object->CreateComponent<Health>();
	objectHealth->SetDefaultHealth(_health);

	//ajoute un shaperanderer
	SpriteRenderer* shapeRenderer = game_object->CreateComponent<SpriteRenderer>();
	shapeRenderer->setTextureRect(asset);
	shapeRenderer->Sprite.setScale(width, height);

	SquareCollider* square_collider = game_object->CreateComponent<SquareCollider>();
	square_collider->SetWidth(shapeRenderer->texture.getSize().x);
	square_collider->SetHeight(shapeRenderer->texture.getSize().y);

	return game_object;
}

GameObject* Scene::CreateGameObject2(const std::string& _name, const int _health, const Maths::Vector2<float> _position, const Maths::Vector2<float> _size, const sf::Color _color, const Scene& _sceneName)
{
	GameObject* const game_object = new GameObject();
	game_object->SetName(_name);
	game_object->SetPosition(_position);
	game_object->SetScene(this);
	gameObjects.push_back(game_object);

	Health* objectHealth = game_object->CreateComponent<Health>();
	objectHealth->SetDefaultHealth(_health);

	SquareCollider* square_collider = game_object->CreateComponent<SquareCollider>();
	square_collider->SetWidth(_size.x);
	square_collider->SetHeight(_size.y);

	RectangleShapeRenderer* shape_renderer = game_object->CreateComponent<RectangleShapeRenderer>();
	shape_renderer->SetColor(_color);
	shape_renderer->SetSize(_size);

	return game_object;
}

GameObject* Scene::CreatePlatformObject(const std::string& _name, const Maths::Vector2<float> _position, const Maths::Vector2<float> _size, const sf::Color _color, const Scene& _sceneName)
{
	GameObject* const game_object = new GameObject();
	game_object->SetName(_name);
	game_object->SetPosition(_position);
	game_object->SetScene(this);
	gameObjects.push_back(game_object);

	SquareCollider* square_collider = game_object->CreateComponent<SquareCollider>();
	square_collider->SetWidth(_size.x);
	square_collider->SetHeight(_size.y);

	RectangleShapeRenderer* shape_renderer = game_object->CreateComponent<RectangleShapeRenderer>();
	shape_renderer->SetColor(_color);
	shape_renderer->SetSize(_size);

	return game_object;
}




void Scene::DestroyGameObject(const GameObject* _game_object)
{
	for (std::vector<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		if (*it == _game_object)
		{
			gameObjects.erase(it);
			delete _game_object;
			return;
		}
	}
}

GameObject* Scene::FindGameObject(const std::string& _name) const
{
	for (GameObject* const& game_object : gameObjects)
	{
		if (game_object->GetName() == _name)
		{
			return game_object;
		}
	}
	return nullptr;
}

const std::vector<GameObject*>& Scene::GetGameObjects() const
{
	return gameObjects;
}


void Scene::Shutdown()
{
	// Effectuez ici toutes les opérations de fermeture spécifiques à votre jeu.
	// Par exemple, libérez les ressources, fermez les connexions réseau, etc.

	std::cout << "Shutting down scene: " << name << std::endl;
	// Ajoutez d'autres opérations de fermeture ici si nécessaire.

	// Enfin, détruire tous les GameObjects de la scène.
	for (auto& gameObject : gameObjects)
	{
		gameObject->Destroy();
	}

	// Vous pouvez également ajouter d'autres opérations de fermeture ici.
}