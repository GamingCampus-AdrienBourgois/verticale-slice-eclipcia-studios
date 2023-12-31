#pragma once
#include "stdafx.h"

#include "Color_Wheel.hpp"


class ColorPicker : public sf::Drawable {
public:
	ColorPicker(sf::Color& color, sf::Vector2f position);
	~ColorPicker();

	void Update(const sf::Vector2f& mousePos);
private:
	sf::RectangleShape m_body;

	sf::Color* m_color;

	ColorWheel* m_colorWheel;

	bool m_keyCheck = false; 

	bool m_wheelVisible = false;
	void InitBody(const sf::Vector2f& position);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};