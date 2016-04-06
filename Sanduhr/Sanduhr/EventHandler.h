#pragma once


namespace sf
{
	class RenderWindow;
}

class EventHandler
{
public:
	explicit EventHandler(sf::RenderWindow* window);
	~EventHandler();

	void Update();

private:
	void OnKeyPressed(int key);

private:
	sf::RenderWindow* m_window;
};

