#pragma once
#include <SFML/System/Clock.hpp>

#include "Module.h"

class TimeModule final : public Module
{
public:
	TimeModule() = default;
	~TimeModule() = default;

public:
	void Init() override;
	void Update() override;

	float GetDeltaTime() const;
	float GetTimeSinceBeginning() const;

private:
	sf::Clock deltaClock;
	sf::Clock clock;

	float deltaTime = 0.0f;
};
