#pragma once
#include "stdafx.h"
#include "Entity.hpp"

#include "Timer.hpp"

#include "Animations/Animator.hpp"

#include "../Objects/Wall.hpp"
#include "Heart.hpp"
#include "Ghost.hpp"
#include "../Effects/Particle Emitter/Particle_Emitter.hpp"

#include "../UI/Health_Bar.hpp"

class Player : public Entity {
public:
	Player(const float& dt, const float& fdt, sf::Texture* texture);
	~Player();

	virtual void FixedUpdate();
	virtual void Update();

	void ResolveCollision(Entity* entity);
	void ResolveCollision(Ghost* entity, std::vector<Ghost*>& ghosts);
	void ResolveCollision(Heart* entity);
	void ResolveCollision(std::vector<Wall>& walls);

	bool IsAlive() const;
private:
	sf::Vector2f m_velocity;

	bool m_alive = true;

	const float m_movementSpeed = 350.0f;
	float m_torque				= 0.85f;
	const float m_gravity		= 4605.0f;
	const float m_jumpVelocity  = -1200.0f;

	bool m_grounded		= true;
	bool m_crouching	= false;
	bool m_grabbing		= false;

	bool m_hit			= true;
	bool m_movable		= true;

	bool m_wasGrounded  = false;

	unsigned m_currentHitTake = 10;

	const sf::Vector2i m_playerSize = sf::Vector2i(96, 84);
	std::unordered_map<std::string, Animator> m_Animations;


	sf::Clock m_hitTimer;

	
	HealthBar m_healthBar;

	sf::SoundBuffer m_ghostBuffer;
	sf::Sound m_ghost;

	

	void UpdateTimer();

	void Animate();

	void KeepInBorders();

	void Crouch();

	void Move();
	void UpdateVelocity();


	void InitAnimations();
	void InitBody();
	void InitCollider();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
