#include "World.h"

#include <assert.h>
#include <SFML/Graphics/RenderWindow.hpp>

World::World(sf::RenderWindow* window)
	: m_window(window)
	, m_eventHandler(m_window)
	, m_viewHandler(m_window)
	, m_sceneHandler(m_window)
{
	assert(m_window);
}

World::~World()
{
}

void World::Run()
{
	sf::Clock clock;
	while(m_window->isOpen())
	{
		auto delta = clock.restart().asSeconds();
		Update(delta);
		Render();
	}
}

void World::Update(float delta)
{
	m_eventHandler.Update();
	m_sceneHandler.Update(delta);
}

void World::Render()
{
	m_window->clear();	
	m_sceneHandler.Render();
	m_viewHandler.Render();
	m_window->display();
}
