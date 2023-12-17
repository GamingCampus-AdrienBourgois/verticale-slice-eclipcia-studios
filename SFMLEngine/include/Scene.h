#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "GameObject.h"
#include "Components/RectangleShapeRenderer.h"
#include "Components/SquareCollider.h"
#include "Components/Health.h"

class Scene
{
public:
	explicit Scene(const std::string& _name);
	virtual ~Scene() = default;

	void Awake() const;
	void Start() const;
	void Update(float _delta_time) const;

	void PreRender() const;
	void Render(sf::RenderWindow* _window) const;
	void OnGUI() const;
	void OnDebug() const;
	void OnDebugSelected() const;
	void PostRender() const;
	void Present() const;

	void OnEnable() const;
	void OnDisable() const;

	void Destroy() const;
	void Finalize() const;
	void Shutdown();

	const std::string& GetName() const;

	GameObject* CreateGameObject(const std::string& _name, const int _health, const Maths::Vector2<float> _position, const Maths::Vector2<float> _size, const sf::Color _color, const Scene& _sceneName, std::string asset, float width, float height);
	GameObject* CreateGameObjectPlayer(const std::string& _name, const int _health, const Maths::Vector2<float> _position, const Maths::Vector2<float> _size, const sf::Color _color, const Scene& _sceneName, std::string asset, float width, float height);
	GameObject* CreateGameObject2(const std::string& _name, const int _health, const Maths::Vector2<float> _position, const Maths::Vector2<float> _size, const sf::Color _color, const Scene& _sceneName);
	GameObject* CreatePlatformObject(const std::string& _name, const Maths::Vector2<float> _position, const Maths::Vector2<float> _size, const sf::Color _color, const Scene& _sceneName);
	void DestroyGameObject(const GameObject* _game_object);
	GameObject* FindGameObject(const std::string& _name) const;
	const std::vector<GameObject*>& GetGameObjects() const;

private:
	std::string name;
	std::vector<GameObject*> gameObjects;
};
