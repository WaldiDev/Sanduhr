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

private:
	sf::RenderWindow* m_window;
	sf::Font m_font;
	sf::Clock m_fpsClock;
	sf::Text m_infoText;
	std::string m_info;
};

