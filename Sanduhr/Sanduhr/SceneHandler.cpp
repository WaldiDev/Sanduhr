#include "SceneHandler.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

SceneHandler::SceneHandler(sf::RenderWindow* window)
	: m_window(window)
{
	//m_renderTexture.create(300u, 1000u);
	m_image.create(300u, 1000u);

	auto offset = 0u;
	for (auto row = 0u; row < 1000; ++row)
	{
		for (auto col = 0u; col < 300; ++col)
		{
			sf::Color color;

			if (col < offset || col >= 300 - offset || row < 3 || row >= 997)		
				color = sf::Color::Blue;
			
			else
				if (row < 500)
					color = sf::Color::Yellow;

			m_image.setPixel(col, row, color);
		}
		if (row % 4 == 0)
		{
			if (row < 500)
				offset++;
			else
				offset--;
		}
	}

}

SceneHandler::~SceneHandler()
{
}

void SceneHandler::Update(float delta)
{
	sf::Image buffer;
	buffer.create(300u, 1000u);

	for (auto row = 0u; row < 1000 - 1; ++row)
	{
		for (auto col = 0u; col < 300 - 1; ++col)
		{
			sf::Color state1, state2, state3, state4;
			GetPixel(col, row, state1, state2, state3, state4);

			if (state1 == sf::Color::Yellow && state2 != sf::Color::Yellow &&		// OX -> XX
				state3 == sf::Color::Black && state4 != sf::Color::Yellow)			// XX -> OX
			{
				state1 = sf::Color::Black;
				state3 = sf::Color::Yellow;
			}
			else if (state1 != sf::Color::Yellow && state2 == sf::Color::Yellow &&	// XO -> XX
					 state3 != sf::Color::Yellow && state4 == sf::Color::Black)		// XX -> XO
			{
				state2 = sf::Color::Black;
				state4 = sf::Color::Yellow;
			}
			else if (state1 == sf::Color::Yellow && state2 != sf::Color::Yellow &&	// OX -> XX
					 state3 == sf::Color::Yellow && state4 == sf::Color::Black)		// OX -> OO
			{
				state1 = sf::Color::Black;
				state4 = sf::Color::Yellow;
			}
			else if (state1 != sf::Color::Yellow && state2 == sf::Color::Yellow &&	// XO -> XX
					 state3 == sf::Color::Black && state4 == sf::Color::Yellow)		// XO -> OO
			{
				state2 = sf::Color::Black;
				state3 = sf::Color::Yellow;
			}
			else if (state1 == sf::Color::Yellow && state2 != sf::Color::Yellow &&	// OX -> XX
					 state3 == sf::Color::Black && state4 == sf::Color::Yellow)		// XO -> OO
			{
				state1 = sf::Color::Black;
				state3 = sf::Color::Yellow;
			}
			else if (state1 != sf::Color::Yellow && state2 == sf::Color::Yellow &&	// XO -> XX
					 state3 == sf::Color::Yellow && state4 == sf::Color::Black)		// OX -> OO
			{
				state2 = sf::Color::Black;
				state4 = sf::Color::Yellow;
			}
			else if (state1 == sf::Color::Yellow && state2 == sf::Color::Yellow &&	// OO -> XO
					state3 == sf::Color::Black && state4 == sf::Color::Yellow)		// XO -> OO
			{
				state1 = sf::Color::Black;
				state3 = sf::Color::Yellow;
			}
			else if (state1 == sf::Color::Yellow && state2 == sf::Color::Yellow &&	// OO -> OX
					 state3 == sf::Color::Yellow && state4 == sf::Color::Black)		// OX -> OO
			{
				state2 = sf::Color::Black;
				state4 = sf::Color::Yellow;
			}
			else if (state1 == sf::Color::Yellow && state2 == sf::Color::Yellow &&	// OO -> XX || OO
					 state3 == sf::Color::Black && state4 == sf::Color::Black)		// XX -> OO || XX
			{
				state1 = sf::Color::Black;
				state2 = sf::Color::Black;
				state3 = sf::Color::Yellow;
				state4 = sf::Color::Yellow;
			}

			SetPixel(col, row, state1, state2, state3, state4, buffer);
		}
	}

	m_image = buffer;
}

void SceneHandler::Render()
{
	sf::Texture texture;
	texture.create(300, 1000);
	texture.update(m_image);
	sf::Sprite sprite(texture);
	sprite.setOrigin(150.f, 500.f);
	sprite.setPosition(500.f, 500.f);
	
	m_window->draw(sprite);
}

void SceneHandler::GetPixel(int col, int row, sf::Color& state1, sf::Color& state2, sf::Color& state3, sf::Color& state4) const
{
	state1 = m_image.getPixel(col + 0, row + 0);
	state2 = m_image.getPixel(col + 1, row + 0);
	state3 = m_image.getPixel(col + 0, row + 1);
	state4 = m_image.getPixel(col + 1, row + 1);
}

void SceneHandler::SetPixel(int col, int row, sf::Color state1, sf::Color state2, sf::Color state3, sf::Color state4, sf::Image& buffer) const
{
	buffer.setPixel(col + 0, row + 0, state1);
	buffer.setPixel(col + 1, row + 0, state2);
	buffer.setPixel(col + 0, row + 1, state3);
	buffer.setPixel(col + 1, row + 1, state4);
}
