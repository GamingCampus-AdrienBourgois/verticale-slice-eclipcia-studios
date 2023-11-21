#include "Modules/TimeModule.h"

void TimeModule::Init()
{
	Module::Init();

	deltaClock.restart();
	clock.restart();
}

void TimeModule::Update()
{
	Module::Update();

	const sf::Time delta = deltaClock.restart();
	deltaTime = delta.asSeconds();
}

float TimeModule::GetDeltaTime() const
{
	return deltaTime;
}

float TimeModule::GetTimeSinceBeginning() const
{
	return clock.getElapsedTime().asSeconds();
}
