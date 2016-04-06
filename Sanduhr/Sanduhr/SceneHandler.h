#pragma once
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "Sandglass.h"

namespace sf
{
	class RenderWindow;
}

class SceneHandler
{
public:
	explicit SceneHandler(sf::RenderWindow* window);
	~SceneHandler();

	void Update(float delta);
	void Render();

	void SetMousePosition(float x, float y);
	void IncreaseRadius();
	void DecreaseRadius();
	void DeleteSand(float x, float y);

private:
	float m_radius;
	sf::RenderWindow* m_window;
	//sf::RenderTexture m_renderTexture;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::CircleShape m_mouseRadius;
	sf::Image m_image;
	Sandglass m_sandglass;
	
};

