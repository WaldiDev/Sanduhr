#include "SceneHandler.h"

#include <SFML/Graphics/RenderWindow.hpp>


SceneHandler::SceneHandler(sf::RenderWindow* window)
	: m_radius(10.0f)
	, m_window(window)
{
	m_texture.create(300, 1000);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(150.f, 500.f);
	m_sprite.setPosition(500.f, 500.f);
	m_sandglass.Initialize();
	m_image = m_sandglass.CreateImage();
	m_mouseRadius.setRadius(m_radius);
	m_mouseRadius.setOrigin(m_radius, m_radius);
	m_mouseRadius.setFillColor(sf::Color::Transparent);
	m_mouseRadius.setOutlineThickness(2.0f);
	m_mouseRadius.setOutlineColor(sf::Color::Red);
}

SceneHandler::~SceneHandler()
{
}

void SceneHandler::Update(float delta)
{
	m_sandglass.Update();
	m_image = m_sandglass.CreateImage();
}

void SceneHandler::Render()
{		
	m_texture.update(m_image);	
	m_window->draw(m_sprite);
	m_window->draw(m_mouseRadius);
}

void SceneHandler::SetMousePosition(float x, float y)
{
	m_mouseRadius.setPosition(x, y);
}

void SceneHandler::IncreaseRadius()
{
	m_radius += 10.f;
	m_mouseRadius.setRadius(m_radius);
	m_mouseRadius.setOrigin(m_radius, m_radius);
}

void SceneHandler::DecreaseRadius()
{
	m_radius -= 10.f;
	if (m_radius < 10.f)
	{
		m_radius = 10.0f;
	}

	m_mouseRadius.setRadius(m_radius);
	m_mouseRadius.setOrigin(m_radius, m_radius);
}

void SceneHandler::DeleteSand(float x, float y)
{
	m_sandglass.DeleteSand(x, y, m_radius);
}
