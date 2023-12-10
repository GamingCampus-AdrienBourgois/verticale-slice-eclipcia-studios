#include "Components/RectangleShapeRenderer.h"

#include <imgui-SFML.h>
#include <imgui.h>

#include "SFML/Graphics/Shape.hpp"

RectangleShapeRenderer::RectangleShapeRenderer()
{
	shape = new sf::RectangleShape();
}

RectangleShapeRenderer::~RectangleShapeRenderer()
{
	delete shape;
	shape = nullptr;
}

void RectangleShapeRenderer::Render(sf::RenderWindow* _window)
{
	ARendererComponent::Render(_window);

	const GameObject* owner = GetOwner();

	const Maths::Vector2<float> position = owner->GetPosition();
	shape->setPosition(position.x, position.y);
	shape->setSize(static_cast<sf::Vector2f>(owner->GetScale() * size));
	shape->setRotation(owner->GetRotation());
	shape->setFillColor(color);

	_window->draw(*shape);
}

void RectangleShapeRenderer::OnDebug()
{
	ARendererComponent::OnDebug();

	const sf::Vector2f min = shape->getPosition();
	const sf::Vector2f max = min + shape->getSize();
	const ImU32 col = ImGui::GetColorU32(IM_COL32(255, 0, 0, 255));

	ImGui::GetBackgroundDrawList()->AddRect(min, max, col);
}
