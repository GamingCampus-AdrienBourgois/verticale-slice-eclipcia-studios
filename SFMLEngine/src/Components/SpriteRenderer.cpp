#include "Components/SpriteRenderer.h"
SpriteRenderer::SpriteRenderer()
{
    // Constructor logic, if needed
}

SpriteRenderer::~SpriteRenderer()
{
    // Destructor logic, if needed
}

void SpriteRenderer::Render(sf::RenderWindow* _window)
{
    if (sprite)
    {
        _window->draw(*sprite);
    }
    else
    {
        // Handle the case where the sprite is not set
        // You might want to add logging or error handling here
    }
}