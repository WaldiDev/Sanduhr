#pragma once
#include <SFML/Graphics/RenderTexture.hpp>

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

private:
	void GetPixel(int col, int row, sf::Color& state1, sf::Color& state2, sf::Color& state3, sf::Color& state4) const;
	void SetPixel(int col, int row, sf::Color state1, sf::Color state2, sf::Color state3, sf::Color state4, sf::Image& buffer) const;

private:
	sf::RenderWindow* m_window;
	//sf::RenderTexture m_renderTexture;
	sf::Image m_image;
	
};

