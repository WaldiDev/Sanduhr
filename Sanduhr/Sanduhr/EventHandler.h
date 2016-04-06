#pragma once

class SceneHandler;
class ViewHandler;

namespace sf
{
	class RenderWindow;
}

class EventHandler
{
public:
	 EventHandler(sf::RenderWindow* window, SceneHandler* sceneHandler, ViewHandler* viewHandler);
	~EventHandler();

	void Update();

private:
	void OnKeyPressed(int key);
	void OnMouseMoved(int x, int y);
	void OnMousePressed(int x, int y, int button);

private:
	sf::RenderWindow* m_window;
	SceneHandler* m_sceneHandler;
	ViewHandler* m_viewHandler;
};

