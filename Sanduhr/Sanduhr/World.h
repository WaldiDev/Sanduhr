#pragma once
#include "EventHandler.h"
#include "ViewHandler.h"
#include "SceneHandler.h"

class World
{
public:
	explicit World(sf::RenderWindow* window);
	~World();

	void Run();

private:
	void Update(float delta);
	void Render();

private:
	sf::RenderWindow* m_window;	
	ViewHandler* m_viewHandler;
	SceneHandler* m_sceneHandler;
	EventHandler* m_eventHandler;
};

