#pragma once

#include <string>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>

namespace sf
{
	class RenderWindow;
}

class ViewHandler
{
public:
	explicit ViewHandler(sf::RenderWindow* window);

	void Render();
	void SetMousePos(float x, float y);
	void ZoomIn();
	void ZoomOut();

private:
	sf::RenderWindow* m_window;
	sf::Font m_font;
	sf::Clock m_fpsClock;
	sf::Text m_infoText;
	std::string m_info;
	float m_mouseX;
	float m_mouseY;
};

